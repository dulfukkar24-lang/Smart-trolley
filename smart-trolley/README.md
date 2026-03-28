# 🛒 Human-Following Smart Trolley with RFID Checkout

A next-generation smart shopping trolley that autonomously follows the user and features an integrated RFID scanning system for a seamless, cashier-less checkout experience. This project bridges the gap between IoT hardware and a modern web application to provide a complete smart retail solution.

![Project Banner](https://via.placeholder.com/1000x300?text=Human+Following+Smart+Trolley)

## ✨ Key Features

- **🚶‍♂️ Autonomous Human Following**: The trolley tracks and follows the user, providing a completely hands-free shopping experience.
- **📡 Real-Time RFID Scanning**: Powered by an ESP32 and MFRC522 RFID module. Instantly reads product tags and gives visual/audio feedback (LED & Buzzer).
- **⚡ Live Cart Updates**: Scanned items are immediately pushed to the React frontend in real-time using WebSockets (`Socket.io`).
- **📱 WhatsApp Digital Receipts**: Customers receive instant, smartly formatted digital invoices directly to their WhatsApp.
- **📧 Automated Admin Notifications**: Sends an automated email containing the structured sales record to the shop owner for reliable bookkeeping.
- **🔄 Developer Friendly (1-Click Reset)**: Instantly reset cart history, stock levels, and RFID tag statuses during testing and presentations.

---

## 🛠️ Tech Stack

### Hardware & IoT
- **Microcontroller**: ESP32 (Wi-Fi enabled)
- **RFID Module**: MFRC522 Reader 
- **Feedback Components**: Buzzer, LEDs
- *Human Following Hardware* (e.g., Raspberry Pi, Ultrasonic/IR Sensors, Motor Drivers)

### Software & Web App
- **Frontend**: React.js, Socket.io-client
- **Backend**: Node.js, Express.js
- **Database**: SQL Database (via Sequelize ORM)
- **Real-Time Comm**: Socket.io
- **Email Service**: Nodemailer

---

## 📂 Project Structure

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

---

## 🚀 How It Works

1. **Scan**: The user drops an item into the trolley. The internal ESP32 reads the RFID tag and sends a POST request to the backend.
2. **Process**: The backend (`rfidController.js`) validates the tag against the Sequelize database and retrieves the product info.
3. **Broadcast**: Using Socket.io, the backend immediately broadcasts the item data to the frontend display.
4. **Checkout**: The user completes the payment on the app.
5. **Receipts**: 
   - A WhatsApp link is generated to send a digital receipt to the user.
   - The `emailService.js` automatically emails a copy of the bill to the store administrator.

---

## 💻 Setup & Installation

### 1. Hardware Setup (ESP32)
1. Open the `hardware/rfid_scanner.ino` file in the Arduino IDE.
2. Install the necessary libraries: `MFRC522`, `WiFi`, `HTTPClient`.
3. Update your Wi-Fi credentials and Backend IP address in the code:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   String serverName = "http://YOUR_LOCAL_IP:5000/api/rfid/read";
   ```
4. Flash the code to the ESP32.

### 2. Backend Setup
1. Navigate to the `backend` directory.
2. Install dependencies: `npm install`
3. Configure your `.env` file with database credentials and email settings.
4. Start the server: `npm start`

### 3. Frontend Setup
1. Navigate to the `frontend` directory.
2. Install dependencies: `npm install`
3. Start the React app: `npm run dev`

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.

## 📝 License

This project is licensed under the MIT License.
