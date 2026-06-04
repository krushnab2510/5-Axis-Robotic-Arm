# 5-Axis Robotic Arm with Teach Pendant

![5-Axis Robotic Arm](5%20axis%20robot/2.jpeg)

A 5-Axis Robotic Arm developed using Arduino UNO and servo motors. The system features a Teach Pendant that allows users to manually control the arm, record motion sequences, and replay them automatically. The teach-and-repeat functionality enables the robot to perform repetitive tasks accurately without complex programming, making it suitable for robotics education, research, and automation projects.

---

## Overview

This project demonstrates the design and implementation of a low-cost robotic arm capable of performing object manipulation tasks such as pick-and-place operations. The arm provides five degrees of freedom (5-DOF), allowing movement in multiple axes for improved flexibility and control.

The Teach Pendant serves as a user-friendly interface through which the user can manually move each joint using potentiometers. The desired positions are recorded and stored in memory. Once a sequence is saved, the robotic arm can automatically replay the same movements repeatedly, simulating industrial robot teaching and playback methods.

---

## Features

- 5 Degrees of Freedom (5-DOF)
- Arduino UNO based control system
- Teach Pendant for manual operation
- Real-time servo control using potentiometers
- Motion recording and playback
- Teach-and-Repeat functionality
- PWM based servo control
- Emergency Stop feature
- Low-cost and educational design
- Suitable for pick-and-place operations
- Expandable for future automation applications

---

## Mechanical Specifications

| Parameter | Value |
|------------|--------|
| Base to Shoulder Height | 11 cm |
| Lower Arm Length | 12 cm |
| Upper Arm Length | 12 cm |
| Claw Length | 8 cm |
| Maximum Claw Opening | 5.5 cm |
| Total Arm Length | 40 ± 2 cm |
| Operating Angle | 145° |
| Working Space | 130 cm |
| Payload Capacity | 100 g |

---

## Servo Configuration

| Joint | Servo Model |
|---------|-------------|
| Base Rotation | MG996R |
| Shoulder Joint | MG996R |
| Elbow Joint | MG996R |
| Wrist Joint | SG90 |
| End Effector (Claw) | SG90 |

---

## Servo Specifications

### MG996R Servo (Base, Shoulder, Elbow)

| Parameter | Value |
|------------|--------|
| Operating Voltage | 4.8 V |
| Torque | 9.4 kg·cm |
| Speed | 0.19 sec/60° |
| Control Signal | PWM |

### SG90 Servo (Wrist, End Effector)

| Parameter | Value |
|------------|--------|
| Operating Voltage | 4.8 V |
| Torque | 1.8 kg·cm |
| Speed | 0.10 sec/60° |
| Control Signal | PWM |

---

## Hardware Components

- Arduino UNO
- 3 × MG996R Servo Motors
- 2 × SG90 Servo Motors
- 5 × Potentiometers
- Push Buttons
- Status LED
- Emergency Stop Button
- External 5V Power Supply
- Robotic Arm Structure
- Connecting Wires

---

## Software Requirements

- Arduino IDE
- Embedded C/C++
- Servo Library

---

## System Architecture

### Inputs
- Potentiometers for manual joint control
- Record/Playback Button
- Emergency Stop Button

### Controller
- Arduino UNO

### Outputs
- 5 Servo Motors
- Status LED

---

## Working Principle

1. The user manually controls the robotic arm joints using potentiometers located on the Teach Pendant.
2. Servo positions are continuously read and updated by the Arduino UNO.
3. When the Record button is pressed, the current positions of all joints are stored in memory as a pose.
4. Multiple poses can be recorded to create a motion sequence.
5. A playback command initiates automatic execution of the recorded sequence.
6. The robotic arm repeats the stored movements in the same order.
7. An Emergency Stop button can immediately halt all operations when required.

This method replicates the "Teach and Repeat" programming technique commonly used in industrial robotic systems.

---

## Degrees of Freedom

| Axis | Function |
|--------|----------|
| Axis 1 | Base Rotation |
| Axis 2 | Shoulder Movement |
| Axis 3 | Elbow Movement |
| Axis 4 | Wrist Movement |
| Axis 5 | Gripper Control |

---

## Applications

- Robotics Education
- Pick-and-Place Operations
- Industrial Automation Demonstrations
- Embedded Systems Learning
- Robot Programming Concepts
- Research and Prototyping
- Mechatronics Laboratories
- Academic Projects

---

## Advantages

- Simple and intuitive operation
- No coding required during teaching phase
- Low-cost implementation
- Easy to build and maintain
- Reusable motion sequences
- Good platform for learning robotics fundamentals

---

## Future Improvements

- Wireless Teach Pendant
- Bluetooth/Wi-Fi Control
- Mobile Application Interface
- Inverse Kinematics Implementation
- Computer Vision Integration
- AI-Based Object Recognition
- ROS Integration
- Higher Payload Capacity
- Closed-Loop Position Feedback
- Industrial HMI Interface

---

## Project Outcomes

- Successful implementation of a 5-DOF robotic arm.
- Accurate recording and playback of motion sequences.
- Demonstration of industrial teach-and-repeat concepts.
- Development of practical skills in embedded systems, robotics, and automation.
- Creation of a low-cost educational robotics platform.

---

## Author

**Krushna Barde**  
Third Year Electronics and Communication Engineering (ECE)  
MIT School of Engineering & Sciences, Pune

---

## License

This project is open-source and intended for educational, research, and learning purposes.
