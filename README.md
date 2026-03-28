HUMAN FOLLOWING SMART TROLLEY WITH RFID BASED BILLING MECHANISM

Presented By: Group 11 (Hareesh.S.Nair, Devika Rajeev, Dulfukkar Ali P.B, Vydhehy T.M)  
Department: Sixth Semester, Electronics and Instrumentation Department  
Institution:FISAT (Federal Institute of Science and Technology)

(https://drive.google.com/uc?export=view&id=136iePrOVIYkmOrWj7RObF3PiagQjpRy2) (poster)

A next-generation smart shopping trolley that autonomously follows the user and features an integrated RFID scanning system for a seamless, cashier-less checkout experience. This project bridges the gap between IoT hardware and a modern web application to provide a complete smart retail solution.

 Objectives:-
- To develop a trolley which follows only a unique QR Code, scanned through a camera module.
- Design a RFID integrated semi-automatic check out system.
- To develop a robust centralized database architecture that synchronizes trolley data with the store's server for real-time billing and stock management.
- Replacing traditional billing counters using IoT to reduce the waiting time.
- Integration of SLAM using LiDAR for smooth and seamless navigation.

 Key Features & Scope:-

By successfully integrating LiDAR based SLAM for navigation and RFID/IoT for real time data synchronization, the project proves that the difficulty of manual billing system can be eliminated.

This module includes real-time image processing via the camera module to identify and track a **unique QR code** based identifier. By calculating the relative distance and angle of the target, the system dynamically adjusts the PWM signals to the BTS7960 motor drivers, ensuring a consistent following distance. This establishes a smooth and efficient shopping environment.

-  Autonomous Human Following: The trolley tracks and follows the user using a 720p webcam and QR code detection.
-  SLAM Navigation: Utilizes YD LiDAR for safe pathfinding and obstacle avoidance.
-  Real-Time RFID Scanning: Powered by an ESP32 and MFRC522 RFID module. Instantly reads product tags.
-  WhatsApp Digital Receipts: After the billing session, the E-bill is sent directly to the customer's phone number.
-  Automated Admin Notifications: Sends an automated email to the admins if the stocks in the shop are below a certain threshold.

 Methodology & Tech Stack:-

 Hardware Flow:-
1. Human Following: `QR Code` ➔ `720p Webcam` ➔ `Raspberry Pi 5` ➔ `ESP32` ➔ `BTS7960 Motor Driver` ➔ `12V DC Motor`
2. SLAM Navigation: `YD LiDAR` ➔ `Raspberry Pi 5`
3. RFID Checkout: `RFID Module` ➔ `ESP32` ➔ `Database` ➔ `User Interface` ➔ `Payment` ➔ `E-bill / Admin Alert`

Software Stack:-
- Database & UI Interface: Developed using VS Code and **PGSQL (PostgreSQL)**.
- Frontend & Backend App: Facilitates WebSocket real-time syncing and API logic.
- Hardware Integration: Python (OpenCV for Pi), C++ (Arduino IDE for ESP32)

Energy & Calculations:-

Operating Voltage of Components:
- Raspberry Pi: `5V`
- ESP32/ESP8266: `5V`
- LiDAR: `5V`
- 12V Motors (x2): `24V`

Battery Pack Calculations:
- Voltage Calculation in series: 3 x 3.7V = `11.1V`
- Maximum Voltage (full charge): 3 x 4.2V = `12.6V`
- Total Energy:
  - Total Cell Count: 3 Series x 4 Parallel = `12 Cells`
  - Total Energy: 11.1V x 10Ah = `111Wh`

 Future Plan:-
- 3D Depth Navigation: Upgrading the SLAM using a 3D depth camera for more efficient navigation through crowded areas.
- UWB Integration: Integrating the UWB module instead of the QR code for tracking.
- Voice Assisted Shopping: Enabling customers to vocally communicate with the trolley as per their needs.
- Smart UI Upgrades: Upgrading the user interface to showcase current offers and availability of stock within the shop.
- Autonomous Charging: Implementing a charging station for the trolley to return to after use or when the battery has run out.
- Rendezvous Mode: Train the trolley to assemble at a pick up point in case the person with the QR went missing.

 SDGs Addressed
- Goal 9: Industry, Innovation and Infrastructure
- Goal 11: Sustainable Cities and Communities
- Goal 12: Responsible Consumption and Production

 Project Structure

```text
├── hardware/               # ESP32, Arduino, and Pi Code
│   ├── rfid_scanner/       # ESP32 C++ code for Wi-Fi and RFID scanning
│   ├── motor_controller/   # ESP32 Open Loop PWM System for motor control
│   └── pi_follower/        # Raspberry Pi QR code follower (Python/OpenCV)
├── backend/                # Node.js Server
│   ├── controllers/        # Route logic (RFID read, database reset)
│   ├── models/             # Sequelize Database Models
│   ├── utils/              # Helper functions (Email service)
│   └── server.js           # Server entry point & Socket.io setup
├── frontend/               # React Application
│   ├── src/
│   │   ├── pages/          # Main views (e.g., Payment, Dashboard)
│   │   └── components/     # Reusable UI elements
│   └── package.json
└── scripts/                # Utility and monitoring scripts
    ├── laptop_cam_sub.py   # Zenoh video stream subscriber
    └── laptop_monitor.py   # Zenoh sensor data generator
```

Setup & Installation

1. Hardware Setup (ESP32)
1. Open the `hardware/rfid_scanner/rfid_scanner.ino` file in the Arduino IDE.
2. Install the necessary libraries: `MFRC522`, `WiFi`, `HTTPClient`.
3. Update your Wi-Fi credentials and Backend IP address in the code.
4. Flash the code to the ESP32.

 2. Backend Setup
1. Navigate to the `backend` directory.
2. Install dependencies: `npm install`
3. Configure your `.env` file with PGSQL database credentials and email settings.
4. Start the server: `npm start`

 3. Frontend Setup
1. Navigate to the `frontend` directory.
2. Install dependencies: `npm install`
3. Start the React app: `npm run dev`


