# Beetle MK-1 — Autonomous/RC Competition Vehicle

A four-wheel skid-steer, Bluetooth-controlled robotic vehicle built for **ROBO356 – Design and Development Project 1**, tasked with climbing a ramp, retrieving a small object, and returning to the start line — faster and more reliably than competing teams' designs.

**Result: 1st place** among all groups in the final time-trial competition.

Built by **Team Beetle Mark 1**: Budhvin Hewage, Thomas Lizo, Han-Hsien Chung, Jae-han Jun.

## Overview

The competition set a fixed footprint (10"×16"), a fixed drive-wheel size, and a $60/person budget, with three goals: climb a ramp, grip a small cup, and bring it back across the start line. Team design decisions were driven by three engineering constraints — friction, torque, and velocity — validated with hand calculations before construction (see `Final Report.pdf` for the full torque analysis).

## Design Highlights

- **Chassis:** 4-wheel configuration with skid steering — chosen over a steered-axle design for build/programming simplicity and better ramp stability than a 3-wheel alternative.
- **Wheels:** Rubber drive wheels up front for ramp traction, omni wheels at the rear for low-friction turning.
- **Microcontroller:** Arduino Uno R3, chosen for team familiarity and community support over a PIC-based alternative.
- **Motor driver:** Iterated through three choices — an initial driver lacked an H-bridge and couldn't reverse polarity; a second choice couldn't supply sufficient voltage; the final Osepp Motor & Servo driver resolved both issues.
- **Sensing:** HC-SR04 ultrasonic sensor for object/obstacle detection.
- **Control:** HC-06 Bluetooth module for remote operator control, with dual programmed speed settings — full speed for transit, a reduced speed for precision approach to the ramp and cup.
- **Power:** 12V battery stepped down to 5V via a DROK converter to protect the microcontroller and logic components.

## What Went Wrong (and what we'd change)

- **Motor driver compatibility** was the single biggest setback — the original driver choice was discovered non-functional only weeks before the final demo, forcing a scramble to source and reprogram around a replacement.
- **Vibration from the rear omni wheels** loosened electrical connections and set screws over time, worked around in the short term with soldering, heat-shrink, and electrical tape rather than a proper fix. A spring-suspension mount (used in similar mecanum-wheel robots) was identified as the real fix, but there wasn't time to implement it.
- **Actual round-trip time (70s) significantly exceeded the theoretical calculation (~50s)**, attributed to ramp deceleration, cup pickup time, and wheel slip not captured in the original math.
- **Biggest lesson:** validate components against their actual datasheet specs *before* integrating them — the original motor driver's rated voltage didn't match what it actually delivered, and catching that earlier would have avoided a month of delay.

## Repo Contents

- `final_project.ino` — main control firmware (Bluetooth command handling, motor control, ultrasonic sensing)
- `Full_Code.ino`, `Motion_Test.ino`, `Seperate_Gripper_Test.ino`, `Ultrasonic_Sensor_Test.ino` — earlier subsystem test sketches
- `AFMotor.h` — motor driver library header
- `Electrical Wiring Diagram.png` — full electrical schematic
- `Final Report.pdf` — complete project report: design rationale, torque/speed calculations, results, and recommendations
