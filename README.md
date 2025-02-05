# 🚀 Arduino RFID - Based Access Control System

This project is an **RFID-based access control system** using an **RFID reader (MFRC522)** and a **relay-controlled solenoid lock**. It allows only authorized RFID cards to unlock the system.

## 📌 Features
- **RFID Authentication**: Uses an MFRC522 RFID module to detect and read RFID card UIDs.
- **Relay-Controlled Solenoid Lock**: Unlocks when an authorized RFID card is detected.
- **Security Lock**: Keeps the solenoid locked by default.
- **Status Feedback**: Displays RFID scan results on the Serial Monitor.

## 🛠️ Components Required
- **Arduino Board** (Uno, Mega, etc.)
- **RFID Reader (MFRC522)**
- **RFID Cards**
- **Relay Module**
- **Solenoid Lock**
- **Connecting Wires**
- **12V Power Supply (for Solenoid Lock)**

## 📝 Installation & Setup

### 1️⃣ **Wiring Connections**
| Component | Arduino Pin |
|-----------|------------|
| RFID **SDA (SS)** | D10 |
| RFID **SCK** | D13 |
| RFID **MOSI** | D11 |
| RFID **MISO** | D12 |
| RFID **RST** | D9 |
| **Relay IN Pin** | D7 |
| **Solenoid Lock** | Connected to relay |

### 2️⃣ **Upload the Code**
1. Install the **MFRC522** and **SPI** libraries in Arduino IDE:
   - Open **Arduino IDE**.
   - Go to `Sketch` → `Include Library` → `Manage Libraries...`.
   - Search for **MFRC522** and **SPI**, then install them.
   
2. Open the provided **`arduinorfid.ino`** file and update the **Wi-Fi SSID and Password** if needed.

3. Select **Arduino Board** (`Tools > Board`), then choose the correct **COM Port**.

4. Click **Upload**.

### 3️⃣ **How It Works**
- The **RFID module** continuously scans for cards.
- When a card is detected, its **UID** is checked against a list of **authorized UIDs**.
- If **authorized**, the **relay activates**, unlocking the solenoid lock.
- If **unauthorized**, access is denied, and a message is displayed in the Serial Monitor.

## 🔧 Troubleshooting
- If RFID is not detected:
  - Check **wiring connections**.
  - Make sure the **MFRC522 library** is installed.
- If solenoid doesn’t unlock:
  - Verify that the **UID is in the authorized list**.
  - Ensure the **relay module is correctly powered**.

## 📜 License
This project is open-source under the **MIT License**.

## 📬 Contact
For any issues or improvements, raise an **issue** or submit a **pull request** on GitHub.

---
🔒 **Secure Your Access with RFID!** 🚀
