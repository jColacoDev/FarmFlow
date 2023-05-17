void bme680_start(){
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
    // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  Serial.println("");
  Serial.println("-- bme680 started --");
}

float dewPointFast(float celsius, float humidity){
  float a = 17.271;
  float b = 237.7;
  float temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  float Td = (b * temp) / (a - temp);
  return Td;
}
void bme680_check(){
  if (! bme.performReading()){
    Serial.println("Failed to perform reading :(");
    return;
  }
  
  bme680_temperature = bme.temperature;
  bme680_pressure = bme.pressure / 100.0;
  bme680_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  bme680_humidity = bme.humidity;
  bme680_gas = bme.gas_resistance / 1000.0;
  bme680_dewPoint = dewPointFast(bme680_temperature, bme680_humidity);
  
  Serial.print("Temperature = ");
  Serial.print(bme680_temperature);
  Serial.println(" *C");
 
  Serial.print("Humidity = ");
  Serial.print(bme680_humidity);
  Serial.println(" %");

  Serial.print("Pressure = "); 
  Serial.print(bme680_pressure); 
  Serial.println(" hPa");
 
  Serial.print("Dew Point = ");
  Serial.print(bme680_dewPoint);
  Serial.println(" *C");
 
  Serial.print("Approx. Altitude = ");
  Serial.print(bme680_altitude);
  Serial.println(" m");
 
  Serial.print("Gas = ");
  Serial.print(bme680_gas);
  Serial.println(" KOhms");
  Serial.println();
}