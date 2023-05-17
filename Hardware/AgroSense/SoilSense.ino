bool soil7_prepare(){
    float history_copy[HISTORY_SIZE];

  memcpy(history_copy, humidity_history, sizeof(history_copy));
  h_median = calculate_median_float(history_copy);
      Serial.print("Humidade do solo = ");
      Serial.print(h_median);
      Serial.println(" %");

  memcpy(history_copy, temperature_history, sizeof(history_copy));
  t_median = calculate_median_float(history_copy);

      Serial.print("Temperatura do solo = ");
      Serial.print(t_median);
      Serial.println(" C");

  memcpy(history_copy, ec_history, sizeof(history_copy));
  ec_median = calculate_median_float(history_copy);
      Serial.print("Condutividade eletrica = ");
      Serial.print(ec_median);
      Serial.println(" mS/cm");

  memcpy(history_copy, ph_history, sizeof(history_copy));
  ph_median = calculate_median_float(history_copy);
      Serial.print("PH do solo = ");
      Serial.print(ph_median);
      Serial.println(" ph");

  memcpy(history_copy, n_history, sizeof(history_copy));
  n_median = calculate_median_float(history_copy);
      Serial.print("Nitrogenio = ");
      Serial.print(n_median);
      Serial.println(" mg/Kg");

  memcpy(history_copy, p_history, sizeof(history_copy));
  p_median = calculate_median_float(history_copy);
      Serial.print("Fosforo = ");
      Serial.print(p_median);
      Serial.println(" mg/Kg");

  memcpy(history_copy, k_history, sizeof(history_copy));
  k_median = calculate_median_float(history_copy);
      Serial.print("Potassio = ");
      Serial.print(k_median);
      Serial.println(" mg/Kg");
      Serial.println("");
      Serial.println("");

  if(h_median==0) return false;
  return true;
}
bool soil7_check(){
  reset_all_history();
  for(byte i=0;i<HISTORY_SIZE;i++){
    if(get_soil_data()) {
      check_data_history(4,0,100,humidade_val, humidity_history);
      check_data_history(1,-10,60,temperatura_val, temperature_history);
      check_data_history(1,0,100,ce_val, ec_history);
      check_data_history(0.5,0,14,ph_val, ph_history);
      check_data_history(10,0,2000,fosforo_val, p_history);
      check_data_history(10,0,2000,nitrogenio_val, n_history);
      check_data_history(10,0,2000,potassio_val, k_history);
    }
    delay(INTERVAL_SENSOR_CHECK);
  }
  
  return soil7_prepare();
}

bool get_soil_data(){
  digitalWrite(DERE,HIGH);
  delay(200);
  int x = modbus.write(soil7_inquiry_frame, sizeof(soil7_inquiry_frame)); 
  modbus.flush();
  if(showSoilSensePrints==true){
    Serial.print(x);
    Serial.println(" Bytes enviados");     
  }
  
  digitalWrite(DERE,LOW);
  delay(200);
  
  uint32_t startTimer= millis();
   while((modbus.available()) == 0)
   { 
      delay(100);
      if(millis()-startTimer > 2000) {
       if(showSoilSensePrints==true){
         Serial.println("");
         Serial.println("modBus Answer Timeout!");
         Serial.println("");
       }      
        return false;
      }
   }
   if(showSoilSensePrints==true){
    Serial.print(modbus.available());
    Serial.println(" Bytes Recebidos");  
  }
   for(byte i=0;i<20;i++)
        {
        values[i] = modbus.read();
        if(showSoilSensePrints==true){
        Serial.print(values[i],HEX);
        }
        } 
        if(showSoilSensePrints==true){
          Serial.println();
        }

    if(!(values[0]==1 && values[1]==3)) return false;

    humidade_val = (float(values[3]<<8|values[4]))/10.00;
    temperatura_val = (float(values[5]<<8|values[6]))/10.00;
    ce_val = (float(values[7]<<8|values[8]))/1000.00;
    ph_val = (float(values[9]<<8|values[10]))/10.00;
    nitrogenio_val = float(values[11]<<8|values[12]);
    fosforo_val = float(values[13]<<8|values[14]);
    potassio_val = float(values[15]<<8|values[16]);

    return true;
  }
