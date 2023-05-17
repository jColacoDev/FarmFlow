
void readSH() {
  for(byte y=0;y<SH_SIZE;y++){
    sh_values[y] = 0;
  }

  for(byte i=0;i<HISTORY_SIZE;i++){
    for(byte y=0;y<SH_SIZE;y++){
      sh_values[y] += map(analogRead(sh_pins[y]), 0, ADC_RESOLUTION, 0, 100);
    }
  }
  for(byte y=0;y<SH_SIZE;y++){
    sh_values[y] = sh_values[y] / HISTORY_SIZE;
    
    Serial.print("sh_values[");Serial.print(y);Serial.print("]: ");Serial.println(sh_values[y]);
  }
}


String generateSHData() {
  String sh_data = "\"sh\": [";
  for (int i = 0; i < SH_SIZE; i++) {
    sh_data += "{";
    sh_data += "\"id\": " + String(sh_ids[i]) + ",";
    sh_data += "\"humidity\": " + String(sh_values[i]);
    sh_data += "}";
    if (i != SH_SIZE - 1) {
      sh_data += ",";
    }
  }
  sh_data += "]";

  return sh_data;
}