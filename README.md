# ESP32 Temperature Monitor

A real-time temperature monitoring system built with ESP32, featuring web-based dashboard, alerts, and data logging capabilities.

## 📋 Overview

This project transforms an ESP32 microcontroller into a versatile temperature monitoring solution. It can be used for home automation, greenhouse monitoring, server room temperature tracking, or any application requiring reliable temperature sensing with remote access.

### Features

- **Real-time Temperature Monitoring**: Continuous temperature readings with configurable sampling rates
- **Web Dashboard**: Access temperature data from any device with a web browser
- **Alert System**: Configurable temperature thresholds with notification capabilities
- **Data Logging**: Store historical temperature data for trend analysis
- **Low Power Mode**: Battery-saving features for portable deployments
- **WiFi Connectivity**: Easy integration with existing networks

## 🔧 Hardware Requirements

- ESP32 development board (ESP32-WROOM, ESP32-DevKitC, etc.)
- Temperature sensor (DHT11/DHT22/DS18B20/BME280)
- Micro USB cable for power and programming
- Optional: display (OLED/LCD), LEDs, buzzer for local alerts
- Optional: battery for portable operation

## 📊 Software Architecture

The system is built using:
- Arduino framework for ESP32
- AsyncWebServer for the web interface
- ArduinoJSON for data processing
- Specific sensor libraries depending on your hardware choice

## ⚙️ Installation

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
- Required libraries (detailed below)
- ESP32 board support package

### Setting up the Arduino IDE

1. Add ESP32 board support:
   - Open Arduino IDE → Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools → Board → Board Manager and install "ESP32 by Espressif Systems"

2. Install required libraries:
   - Sketch → Include Library → Manage Libraries
   - Search and install:
     - DHT sensor library (if using DHT sensors)
     - AsyncTCP
     - ESPAsyncWebServer
     - ArduinoJSON

### Wiring

Connect your temperature sensor to the ESP32:

**For DHT22/DHT11:**
- VCC → 3.3V
- Data → GPIO 4 (configurable in code)
- GND → GND

**For DS18B20:**
- VCC → 3.3V
- Data → GPIO 4 (with 4.7k pull-up resistor)
- GND → GND

**For BME280/BMP280 (I2C):**
- VCC → 3.3V
- SDA → GPIO 21
- SCL → GPIO 22
- GND → GND

## 💻 Usage

1. Clone this repository:
   ```bash
   git clone https://github.com/Gabrielhj17/ESP32-Temperature-Monitor.git
   ```

2. Open the project in Arduino IDE or PlatformIO

3. Configure the settings in `config.h`:
   - WiFi credentials
   - Temperature thresholds
   - Sampling rate
   - Sensor type

4. Upload the code to your ESP32

5. Open Serial Monitor to view the assigned IP address

6. Access the web dashboard by entering the IP address in a browser

## 🔍 Web Interface Features

- **Real-time Display**: Current temperature with auto-refreshing
- **Historical Data**: Temperature graph over time
- **Settings Panel**: Configure alerts and preferences
- **Responsive Design**: Works on desktop and mobile browsers

## 🔄 API Endpoints

The ESP32 provides RESTful API endpoints for integration with other systems:

- `GET /api/temperature` - Returns current temperature reading
- `GET /api/history` - Returns historical temperature data
- `POST /api/settings` - Update monitoring settings
- `GET /api/status` - System status and uptime information

## 💡 Extending the Project

Ideas for expanding the functionality:
- Add humidity monitoring
- Implement MQTT for IoT platform integration
- Create mobile app notifications
- Add support for multiple sensors
- Implement data storage to SD card or cloud

## 🐛 Troubleshooting

Common issues and solutions:

- **Cannot connect to WiFi**: Verify credentials and ensure ESP32 is within WiFi range
- **Inaccurate readings**: Check sensor connections and consider calibration
- **Web interface not accessible**: Verify IP address and network configuration
- **High power consumption**: Review code for deep sleep implementation

## 📚 Resources

- [ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Arduino ESP32 Documentation](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/)
- [Temperature Sensor Datasheets](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## ✉️ Contact

Gabriel H. - [@Gabrielhj17](https://github.com/Gabrielhj17)

Project Link: [https://github.com/Gabrielhj17/ESP32-Temperature-Monitor](https://github.com/Gabrielhj17/ESP32-Temperature-Monitor)

---

**Note**: This README template should be customized with the specific details of your implementation, including accurate wiring diagrams, screenshots of your web interface, and any additional features specific to your project.
