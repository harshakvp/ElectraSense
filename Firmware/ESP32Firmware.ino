/*
  Project Title: ElectraSense
  Description:
  ESP32-based single-phase electrical parameter monitoring,
  LCD display, SD card logging, and Blynk IoT integration.
*/

#define BLYNK_TEMPLATE_ID "TMPL3IjoWWyPX"
#define BLYNK_TEMPLATE_NAME "ElectraSense"
#define BLYNK_AUTH_TOKEN "Rr7MGad29p9lfysDPGc0BtnNm4CCePIi"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>

/* Wi-Fi credentials */
char ssid[] = "Harshak";
char pass[] = "harshak@2476";

/* LCD */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Pins */
#define PIN_VOLTAGE_SENSOR 35
#define PIN_CURRENT_SENSOR 34

#define BTN_PREV   32
#define BTN_NEXT   33
#define BTN_START  25
#define BTN_STOP   26

#define LED_RED    27
#define LED_GREEN  14

#define SD_CS 5

/* ADC */
#define ADC_RESOLUTION 4095.0
#define ADC_REF_VOLTAGE 3.3

/* Sampling */
#define SAMPLE_COUNT 600
#define SAMPLE_DELAY_US 250

/* Calibration factors */
float VOLTAGE_CAL = 545.0;
float CURRENT_CAL = 5.0 / 0.50;

/* Offsets */
float voltageOffset = 2048.0;
float currentOffset = 2048.0;

/* Instantaneous parameters */
float Vrms_raw = 0, Irms_raw = 0;

/* Smoothed parameters */
float Vrms = 0, Irms = 0, activePower = 0;
float apparentPower = 0, reactivePower = 0;
float powerFactor = 0, energyWh = 0;

/* Control */
bool loggingEnabled = false;
bool sdAvailable = false;
bool wifiConnected = false;
int displayPage = 0;

/* Timing */
unsigned long lastCalcTime = 0;
unsigned long lastDisplayTime = 0;
unsigned long lastLogTime = 0;
unsigned long lastEnergyUpdateTime = 0;

const unsigned long calcInterval = 500;
const unsigned long displayInterval = 500;
const unsigned long logInterval = 1000;

/* Button debounce */
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 200;

/* Blynk */
BlynkTimer timer;

/* Function declarations */
void initializeHardware();
void calibrateOffsets();
void connectWiFiAndBlynk();
void readElectricalParameters();
void updateDisplay();
void handleButtons();
void logDataToSD();
void sendDataToBlynk();
void createLogFileHeader();

void setup() {
  initializeHardware();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ElectraSense");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);

  calibrateOffsets();
  connectWiFiAndBlynk();

  timer.setInterval(1000L, sendDataToBlynk);

  lastEnergyUpdateTime = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1000);
}

void loop() {
  if (wifiConnected) {
    Blynk.run();
    timer.run();
  }

  handleButtons();

  unsigned long now = millis();

  if (now - lastCalcTime >= calcInterval) {
    lastCalcTime = now;
    readElectricalParameters();
  }

  if (now - lastDisplayTime >= displayInterval) {
    lastDisplayTime = now;
    updateDisplay();
  }

  if (loggingEnabled && sdAvailable && (now - lastLogTime >= logInterval)) {
    lastLogTime = now;
    logDataToSD();
  }
}

/* Hardware initialization */
void initializeHardware() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);

  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);

  analogReadResolution(12);

  lcd.init();
  lcd.backlight();

  sdAvailable = SD.begin(SD_CS);

  if (sdAvailable) {
    createLogFileHeader();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD Not Ready");
    delay(1500);
  }
}

/* Wi-Fi and Blynk connection */
void connectWiFiAndBlynk() {
  WiFi.begin(ssid, pass);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  unsigned long wifiStart = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 10000) {
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Please wait...  ");
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;

    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    delay(1000);
  } else {
    wifiConnected = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Offline Mode");
    delay(1000);
  }
}

/* Offset calibration */
void calibrateOffsets() {
  long vSum = 0, iSum = 0;

  for (int i = 0; i < 2000; i++) {
    vSum += analogRead(PIN_VOLTAGE_SENSOR);
    iSum += analogRead(PIN_CURRENT_SENSOR);
    delay(2);
  }

  voltageOffset = vSum / 2000.0;
  currentOffset = iSum / 2000.0;
}

/* Electrical parameter calculation */
void readElectricalParameters() {
  float sumV2 = 0, sumI2 = 0, sumP = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    float v = analogRead(PIN_VOLTAGE_SENSOR) - voltageOffset;
    float iVal = analogRead(PIN_CURRENT_SENSOR) - currentOffset;

    sumV2 += v * v;
    sumI2 += iVal * iVal;
    sumP += v * iVal;

    delayMicroseconds(SAMPLE_DELAY_US);
  }

  Vrms_raw = sqrt(sumV2 / SAMPLE_COUNT) * (ADC_REF_VOLTAGE / ADC_RESOLUTION) * VOLTAGE_CAL;
  Irms_raw = sqrt(sumI2 / SAMPLE_COUNT) * (ADC_REF_VOLTAGE / ADC_RESOLUTION) * CURRENT_CAL;

  /* Low-pass smoothing */
  Vrms = 0.8 * Vrms + 0.2 * Vrms_raw;
  Irms = 0.8 * Irms + 0.2 * Irms_raw;

  /* Small noise suppression */
  if (Irms < 0.05) Irms = 0.0;
  if (Vrms < 10.0) Vrms = 0.0;

  activePower = (sumP / SAMPLE_COUNT) *
                pow((ADC_REF_VOLTAGE / ADC_RESOLUTION), 2) *
                VOLTAGE_CAL * CURRENT_CAL;

  /* Smooth active power too */
  static float activePowerFiltered = 0;
  activePowerFiltered = 0.8 * activePowerFiltered + 0.2 * activePower;
  activePower = activePowerFiltered;

  if (Irms == 0.0) activePower = 0.0;

  apparentPower = Vrms * Irms;

  powerFactor = (apparentPower > 0.1) ? activePower / apparentPower : 0;
  if (powerFactor > 1) powerFactor = 1;
  if (powerFactor < 0) powerFactor = 0;

  float q2 = (apparentPower * apparentPower) - (activePower * activePower);
  reactivePower = (q2 > 0) ? sqrt(q2) : 0;

  unsigned long now = millis();
  energyWh += activePower * ((now - lastEnergyUpdateTime) / 3600000.0);
  lastEnergyUpdateTime = now;
}

/* LCD display */
void updateDisplay() {
  lcd.setCursor(0, 0);

  switch (displayPage) {
    case 0:
      lcd.print("Voltage        ");
      lcd.setCursor(0, 1);
      lcd.print(Vrms, 2); lcd.print(" V     ");
      break;

    case 1:
      lcd.print("Current        ");
      lcd.setCursor(0, 1);
      lcd.print(Irms, 3); lcd.print(" A     ");
      break;

    case 2:
      lcd.print("Active Power   ");
      lcd.setCursor(0, 1);
      lcd.print(activePower, 2); lcd.print(" W     ");
      break;

    case 3:
      lcd.print("Energy         ");
      lcd.setCursor(0, 1);
      lcd.print(energyWh, 2); lcd.print(" Wh    ");
      break;

    case 4:
      lcd.print("Power Factor   ");
      lcd.setCursor(0, 1);
      lcd.print(powerFactor, 3); lcd.print("       ");
      break;

    case 5:
      lcd.print("Apparent Power ");
      lcd.setCursor(0, 1);
      lcd.print(apparentPower, 2); lcd.print(" VA    ");
      break;

    case 6:
      lcd.print("Reactive Power ");
      lcd.setCursor(0, 1);
      lcd.print(reactivePower, 2); lcd.print(" VAR   ");
      break;
  }
}

/* Button handling */
void handleButtons() {
  unsigned long now = millis();
  if (now - lastButtonTime < debounceDelay) return;

  if (!digitalRead(BTN_PREV)) {
    displayPage = (displayPage - 1 + 7) % 7;
    lastButtonTime = now;
  }

  if (!digitalRead(BTN_NEXT)) {
    displayPage = (displayPage + 1) % 7;
    lastButtonTime = now;
  }

  if (!digitalRead(BTN_START)) {
    loggingEnabled = true;
    digitalWrite(LED_GREEN, HIGH);
    lastButtonTime = now;
  }

  if (!digitalRead(BTN_STOP)) {
    loggingEnabled = false;
    digitalWrite(LED_GREEN, LOW);
    lastButtonTime = now;
  }
}

/* SD log file header */
void createLogFileHeader() {
  if (!SD.exists("/log.csv")) {
    File file = SD.open("/log.csv", FILE_WRITE);
    if (file) {
      file.println("Time,Voltage,Current,Power,Apparent,Reactive,PF,Energy");
      file.close();
    }
  }
}

/* SD logging */
void logDataToSD() {
  File file = SD.open("/log.csv", FILE_APPEND);
  if (file) {
    file.print(millis()/1000.0); file.print(",");
    file.print(Vrms); file.print(",");
    file.print(Irms); file.print(",");
    file.print(activePower); file.print(",");
    file.print(apparentPower); file.print(",");
    file.print(reactivePower); file.print(",");
    file.print(powerFactor); file.print(",");
    file.println(energyWh);
    file.close();
  }
}

/* Blynk upload */
void sendDataToBlynk() {
  if (!wifiConnected || !Blynk.connected()) return;

  Blynk.virtualWrite(V0, Vrms);
  Blynk.virtualWrite(V1, Irms);
  Blynk.virtualWrite(V2, activePower);
  Blynk.virtualWrite(V3, energyWh);
  Blynk.virtualWrite(V4, powerFactor);
  Blynk.virtualWrite(V5, apparentPower);
  Blynk.virtualWrite(V6, reactivePower);
  Blynk.virtualWrite(V7, loggingEnabled ? 1 : 0);
}