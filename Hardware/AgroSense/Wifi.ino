
void wifi_start(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network: ");Serial.println(ssid);
  Serial.print("With IP Address: ");Serial.println(WiFi.localIP());
}

void http_1post_2Get(int flag, String httpRequestData, bool jsonRequest){
    
    HTTPClient http;
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    int httpResponseCode = 0;
    if(flag == 2){
      String serverPath = serverName + "?" + httpRequestData;
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      // Send HTTP GET request
      httpResponseCode = http.GET();

    }else if(flag == 1){
      // Specify content-type header
      if(jsonRequest) http.addHeader("Content-Type", "application/json");
      else http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      // Send HTTP POST request
      httpResponseCode = http.POST(httpRequestData);
      }
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
       }
      else {
        Serial.print("Error code: ");
      }
        Serial.println(httpResponseCode);
        Serial.println(http.getString());
    // Free resources
    http.end();  
}
