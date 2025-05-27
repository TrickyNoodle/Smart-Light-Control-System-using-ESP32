# Smart Light Control System using ESP32

A wireless lighting control system leveraging the ESP32 microcontroller to manage multiple devices via a web interface.

---

## 🧠 Project Overview

This project demonstrates how to control multiple lights or devices connected to relay modules using the ESP32 microcontroller. The system provides both manual and wireless control options, making it suitable for home automation applications.

---

## ⚙️ Features

* **Wireless Control**: Manage devices remotely through a web interface hosted on the ESP32.
* **Manual Override**: Physical switches allow manual control of devices.
* **Multiple Device Support**: Control up to four devices simultaneously.
* **Real-Time Feedback**: Receive immediate status updates on the web interface.

---

## 🛠️ Components Required

* **Microcontroller**: ESP32 DevKit V1
* **Relay Modules**: 4-channel relay module
* **Power Supply**: 5V USB power adapter
* **Jumper Wires**: For connections
* **Breadboard**: Optional, for prototyping

---

## 📡 Software & Libraries

* **Arduino IDE**: Development environment for ESP32.
* **ESPAsyncWebServer**: Library to handle asynchronous web requests.
* **ESPAsyncTCP**: Required for ESPAsyncWebServer.
* **ESP32 Board Support**: Install via Arduino Board Manager.

---

## 🔌 Wiring Diagram

![oaicite:55](https://github.com/TrickyNoodle/Smart-Light-Control-System-using-ESP32/blob/main/image.png?raw=true)

*Note: Replace with an actual wiring diagram image.*

---

## 🧪 Installation & Setup

1. **Install Arduino IDE**: Download and install the Arduino IDE from [here](https://www.arduino.cc/en/software).
2. **Add ESP32 Board**:

   * Go to **File** > **Preferences**.
   * In the **Additional Boards Manager URLs** field, add:

     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   * Go to **Tools** > **Board** > **Boards Manager**, search for "ESP32", and install it.
3. **Install Libraries**:

   * Go to **Sketch** > **Include Library** > **Manage Libraries**.
   * Search for and install **ESPAsyncWebServer** and **ESPAsyncTCP**.
4. **Upload Code**:

   * Connect your ESP32 to your computer.
   * Select the correct board and port in **Tools**.
   * Open the provided `.ino` file and upload it to the ESP32.
5. **Access Web Interface**:

   * After uploading, open the Serial Monitor.
   * Note the IP address displayed.
   * Enter the IP address in a web browser to access the control interface.

---

## 🔐 License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for more details.

---

## 📸 Screenshots

![oaicite:120](https://github.com/TrickyNoodle/Smart-Light-Control-System-using-ESP32/blob/main/images/webserver1.jpeg?raw=true)
![oaicite:120](https://github.com/TrickyNoodle/Smart-Light-Control-System-using-ESP32/blob/main/images/webserver2.jpeg?raw=true)

---
