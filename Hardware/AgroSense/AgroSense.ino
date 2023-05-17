////// ------------ ///////////// ------------ ///////------------ /////// Constants
#define ADC_RESOLUTION 4095
#define SEALEVELPRESSURE_HPA (1013.25)
////// ------------ ///////////// Modbus
#define MODBUS_RX 18
#define MODBUS_TX 19
#define DERE 4
////// ------------ ///////////// Soil7 Constants
#define HISTORY_SIZE 9
////// ------------ ///////////// Program interval Constants
#define INTERVAL_DATA_SEND 900000
#define INTERVAL_DATA_CHECK 60000
#define INTERVAL_SENSOR_CHECK 500
////// ------------ ///////////// Program debug prints Constants
#define showDataHistoryPrints false
#define showSoilSensePrints false

////// ------------ ///////////// ------------ ///////------------ /////// global
#include <Wire.h>
// #include <SoftwareSerial.h>
// SoftwareSerial modbus(MODBUS_RX,MODBUS_TX);
#include <HardwareSerial.h>
HardwareSerial modbus(2);  // Use hardware serial port 2
////// ------------ ///////////// ------------ ///////------------ /////// Wifi
#include <WiFi.h>
#include <HTTPClient.h>
////// ------------ ///////////// ------------ ///////------------ /////// BME680
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
Adafruit_BME680 bme; // I2C
////// ------------ ///////////// Soil7 Constants
const byte soil7_inquiry_frame[] = {0x01,0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
////// ------------ ///////////// Wifi Constants
const char* ssid     = "xxx";
const char* password = "xxx";
String serverName = "xxx";
String apiKeyValue = "xxx";
////// ------------ ///////////// ------------ ///////------------ /////// Variables
////// ------------ ///////////// Soil7 vars
byte values[19];
float humidity_history[HISTORY_SIZE] = {0.0};
float humidade_val = 0.00;
float temperature_history[HISTORY_SIZE] = {0.0};
float temperatura_val = 0.00;
float ec_history[HISTORY_SIZE] = {0.0};
float ce_val = 0.00;
float ph_history[HISTORY_SIZE] = {0.0};
float ph_val = 0.00;
float n_history[HISTORY_SIZE] = {0};
float nitrogenio_val = 0;
float p_history[HISTORY_SIZE] = {0};
float fosforo_val = 0;
float k_history[HISTORY_SIZE] = {0};
float potassio_val = 0;
float h_median = 0; 
float t_median = 0; 
float ec_median = 0;
float ph_median = 0;
float n_median = 0; 
float p_median = 0; 
float k_median = 0; 
////// ------------ ///////////// time vars
float bme680_temperature = 0;
float bme680_pressure = 0;
float bme680_altitude = 0;
float bme680_humidity = 0;
float bme680_gas = 0;
float bme680_dewPoint = 0;
////// ------------ ///////////// soil humidity (SH) vars
#define SH_SIZE 3
int sh_values[SH_SIZE] = {0};
int sh_pins[SH_SIZE] = {34, 35, 39}; // ADC pins
int sensor_id = 1; // Sensor ID for the overall data packet
int sh_ids[SH_SIZE] = {0, 1, 2}; // IDs for the sh sensors

////// ------------ ///////////// time vars
unsigned long previousDataCheckTime = 0; 
unsigned long previousDataSendTime = 0; 

////// ------------ ///////////// tabs Functions declarations
void bme680_start();
bool soil7_check();
void bme680_check();
void readSH();
String generateSHData();
////// ------------ ///////////// ------------ ///////////// Functions
String generateHttpRequestData() {
  String httpRequestData = "{ \
    \"id\": " + String(sensor_id) + ", \
    \"soil7\": { \
      \"id\": 1, \
      \"humidity\": " + String(h_median, 2) + ", \
      \"temperature\": " + String(t_median, 2) + ", \
      \"ec\": " + String(ec_median, 2) + ", \
      \"ph\": " + String(ph_median, 2) + ", \
      \"n\": " + String(n_median, 2) + ", \
      \"p\": " + String(p_median, 2) + ", \
      \"k\": " + String(k_median, 2) + " \
    }, \
    " + generateSHData() + ", \
    \"bme_680\": { \
      \"id\": 1, \
      \"humidity\": " + String(bme680_humidity, 2) + ", \
      \"temperature\": " + String(bme680_temperature, 2) + ", \
      \"pressure\": " + String(bme680_pressure, 2) + ", \
      \"dewPoint\": " + String(bme680_dewPoint) + ", \
      \"altitude\": " + String(bme680_altitude, 2) + ", \
      \"gas\": " + String(bme680_gas, 2) + " \
    } \
  }";

  return httpRequestData;
}
void send_data(){

      if(WiFi.status()== WL_CONNECTED){
        Serial.println("WiFi Connected!");
      // Prepare the GET, POST request
        String httpRequestData = generateHttpRequestData();
        // String currentdate= currentDate();
        // String httpRequestData = "api_key=" + apiKeyValue + "&" +loraPacket + "&reading_time=" +currentdate;
        
        http_1post_2Get(1, httpRequestData, true);
      }
      else {
        Serial.println("WiFi Disconnected");
        wifi_start();
        //gravar dados no SD
      }
}

////// ------------ ///////
////// ------------ ///////

void setup() {
  Serial.begin(9600);
  // modbus.begin(4800);
  modbus.begin(4800, SERIAL_8N1, MODBUS_RX, MODBUS_TX);
  pinMode(DERE, OUTPUT);
  wifi_start();
  bme680_start();
}
////// ------------ ///////
void loop() {
  if(millis() - previousDataSendTime >= INTERVAL_DATA_SEND) {
    bme680_check();
    if(soil7_check()){
      send_data();
      previousDataSendTime = millis();
    }else delay(200);
  }

  if(millis() - previousDataCheckTime >= INTERVAL_DATA_CHECK) {
    bme680_check();
    soil7_check();
    readSH();

    previousDataCheckTime = millis();
  }
}
