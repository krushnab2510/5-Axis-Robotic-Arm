#include <Servo.h>
#include <EEPROM.h>

#define MAX_STEPS 102 // Changed to prevent EEPROM overflow

Servo servos[5];
int servoPins[5] = {10, 5, 3, 11, 9};
int potPins[5] = {A0, A1, A2, A3, A4};

int joint[5][MAX_STEPS];
int arrayStep = 0, arrayMax = 0;

float currentPos[5];
float targetPos[5];
int moveSteps = 50;
int moveCount = 0;
unsigned long lastMoveTime = 0;
unsigned long waitStart = 0;

bool playmode = false, stepReady = false, waiting = false;
bool moving = false;

void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT_PULLUP);  // Emergency stop
  pinMode(6, INPUT_PULLUP);  // Push button
  pinMode(13, OUTPUT);       // LED

  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
    currentPos[i] = 1700;
    servos[i].writeMicroseconds((int)currentPos[i]);
  }

  loadFromEEPROM();
  digitalWrite(13, LOW);
  Serial.println("Robot Ready.");
}

void loop() {
  handleButton();

  if (digitalRead(4) == LOW) {
    playmode = false;
    digitalWrite(13, LOW);
    return;
  }

  if (!playmode) {
    readAndMoveManual();
  } else {
    playbackStepByStep();
  }

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    if (cmd == "clear") clearEEPROM();
  }
}

void readAndMoveManual() {
  for (int i = 0; i < 5; i++) {
    int val = analogRead(potPins[i]);
    float target;
    if (i == 3) {
      // D11 limited to 1000–2000 us (100°)
      target = map(val, 0, 1023, 1000, 2000);
    } else {
      target = map(val, 0, 1023, 600, 2400);
    }
    float speedFactor = (i == 3) ? 0.1 : 1.0;  // Slow motion for D11
    currentPos[i] += (target - currentPos[i]) * speedFactor;
    servos[i].writeMicroseconds((int)currentPos[i]);
  }
}

void handleButton() {
  static int lastState = HIGH;
  static unsigned long lastPress = 0;
  static bool waitingForDouble = false;

  int state = digitalRead(6);

  if (state == LOW && lastState == HIGH) {
    unsigned long now = millis();
    if (waitingForDouble && (now - lastPress < 500)) {
      playmode = true;
      arrayStep = 0;
      stepReady = true;
      Serial.println("Play mode started");
      digitalWrite(13, HIGH); delay(100); digitalWrite(13, LOW);
      waitingForDouble = false;
    } else {
      waitingForDouble = true;
      lastPress = now;
    }
  }

  if (waitingForDouble && (millis() - lastPress >= 500)) {
    waitingForDouble = false;

    if (arrayStep < MAX_STEPS) {
      for (int i = 0; i < 5; i++) {
        int val = analogRead(potPins[i]);
        if (i == 3)
          joint[i][arrayStep] = map(val, 0, 1023, 1000, 2000);
        else
          joint[i][arrayStep] = map(val, 0, 1023, 600, 2400);
      }
      arrayStep++;
      arrayMax = arrayStep;
      saveToEEPROM();
      Serial.print("Recorded step: "); Serial.println(arrayStep);
      digitalWrite(13, HIGH); delay(100); digitalWrite(13, LOW);
    } else {
      Serial.println("Memory full.");
    }
  }

  lastState = state;
}

void playbackStepByStep() {
  if (stepReady && arrayStep < arrayMax) {
    for (int i = 0; i < 5; i++) {
      targetPos[i] = joint[i][arrayStep];
    }
    moveCount = 0;
    moving = true;
    stepReady = false;
    lastMoveTime = millis();
  }

  if (moving && millis() - lastMoveTime >= 20) {
    lastMoveTime = millis();

    if (moveCount < moveSteps) {
      for (int i = 0; i < 5; i++) {
        float delta = (targetPos[i] - currentPos[i]) / (moveSteps - moveCount);
        currentPos[i] += delta;
        servos[i].writeMicroseconds((int)currentPos[i]);
      }
      moveCount++;
    } else {
      moving = false;
      waiting = true;
      waitStart = millis();
    }
  }

  if (waiting && millis() - waitStart >= 2000) {
    waiting = false;
    arrayStep++;
    stepReady = true;
  }

  if (arrayStep >= arrayMax) {
    arrayStep = 0;
    stepReady = true;
    Serial.println("Restarting loop...");
  }
}

void saveToEEPROM() {
  int addr = 0;
  for (int i = 0; i < arrayMax; i++) {
    for (int j = 0; j < 5; j++) {
      EEPROM.put(addr, joint[j][i]);
      addr += 2;
    }
  }
  EEPROM.put(addr, arrayMax);
  Serial.println("Saved to EEPROM.");
}

void loadFromEEPROM() {
  int addr = 0;
  for (int i = 0; i < MAX_STEPS; i++) {
    for (int j = 0; j < 5; j++) {
      EEPROM.get(addr, joint[j][i]);
      addr += 2;
    }
  }
  EEPROM.get(addr, arrayMax);
  if (arrayMax > MAX_STEPS) arrayMax = 0;
  Serial.print("Loaded steps: "); Serial.println(arrayMax);
}

void clearEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) EEPROM.write(i, 0);
  arrayMax = 0;
  arrayStep = 0;
  Serial.println("EEPROM cleared.");
}