# 🤖 Sumo Car Robot Project

## Overview
This project presents a fully functional **Sumo Robot**, built to compete in robot sumo competitions where autonomous or remote-controlled robots attempt to push each other out of a circular ring. Our design combines **mechanical precision**, **advanced electronics**, and **wireless control** for agile and intelligent performance.

The robot features a custom 3D-printed chassis, obstacle detection using IR sensors, and wireless Bluetooth control via a PlayStation controller — all powered by an **ESP32 microcontroller**.

---

## 🚀 Features

- **Microcontroller**: ESP32 for wireless communication and logic handling.
- **Wireless Control**: Bluetooth-enabled PlayStation controller for remote control.
- **Motion Control**: Two high-torque DC motors with L298 motor driver.
- **Obstacle Detection**: IR sensors for opponent and edge detection.
- **Chassis**: Custom 3D-printed design, optimized for strength and low weight.
- **Battery Powered**: Supports 3S or 4S LiPo battery for high-performance mobility.
- **Modular Assembly**: Designed with individual parts for easy maintenance and upgrades.

---

## 🧩 Components

### Hardware
| Component              | Description |
|------------------------|-------------|
| **ESP32**              | Main microcontroller with Bluetooth capability |
| **DC Motors**          | High-torque motors for drive and push mechanisms |
| **L298 Motor Driver**  | Controls speed and direction of DC motors |
| **IR Sensors**         | Used for obstacle and edge detection |
| **3D-Printed Parts**   | Designed in SolidWorks and printed for precision |
| **PlayStation Controller** | Wireless control interface |
| **Battery**            | 3S/4S LiPo for powering all components |

### Software
- **Programming Environment**: Arduino IDE
- **Wireless Protocol**: Bluetooth for controller input
- **Code Functionality**: Handles motor control, sensor reading, and communication

---

## 🛠️ Mechanical Design

The mechanical structure was fully designed using **SolidWorks** and consists of several custom parts:

| File Name                | Purpose |
|--------------------------|---------|
| `Base.SLDPRT`            | Main platform for electronics and motors |
| `Battery Case.SLDPRT`    | Holds the battery securely |
| `Coupling.SLDPRT`        | Connects motors to wheels |
| `65mm-wheel-1.snapshot.1.zip` | Wheel design for printing or machining |
| `endramp.SLDPRT`         | Ramp to push opponents efficiently |
| `lastcover.SLDPRT`       | Protective top cover for electronics |
| `Cover.SLDPRT`           | Outer body shell |
| `teamproject.SLDASM`     | Complete robot assembly file |
| `ZGA37RG Motor v2.step`  | CAD model of the motor used |

All parts can be opened, modified, and exported using **SolidWorks** or other compatible CAD software.

---

## 🔧 How to Use

### Hardware Setup
1. Assemble the 3D-printed parts and mechanical components using the provided CAD files.
2. Connect the ESP32 to:
   - L298 motor driver (for motor control)
   - IR sensors (for detection)
3. Install the battery securely in the chassis.

### Software Setup
1. Open Arduino IDE and load the ESP32 code.
2. Pair the ESP32 with a PlayStation controller via Bluetooth.
3. Upload the code to the board.

### Power On & Compete
1. Power the robot using a fully charged LiPo battery (3S or 4S recommended).
2. Test motor functions and sensor detection.
3. Enter the ring and control the robot using the wireless controller.

---

## 🤝 Contributing
Feel free to fork the repository, make improvements, and submit pull requests. Suggestions and feedback are welcome!

---

## 📁 Repository Structure
```plaintext
📁 CAD_Files/
 ┣ Base.SLDPRT
 ┣ Battery Case.SLDPRT
 ┣ Coupling.SLDPRT
 ┣ 65mm-wheel-1.snapshot.1.zip
 ┣ endramp.SLDPRT
 ┣ lastcover.SLDPRT
 ┣ Cover.SLDPRT
 ┣ ZGA37RG Motor v2.step
 ┗ teamproject.SLDASM

📁 Code/
 ┗ sumo_robot.ino

📄 README.md
