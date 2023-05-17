   void bubble_sort(float arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                float temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

float calculate_median_float(float array[]) {
  for (int i = 0; i < HISTORY_SIZE - 1; i++) {
    for (int j = i + 1; j < HISTORY_SIZE; j++) {
      if (array[j] < array[i]) {
        float temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
  if (HISTORY_SIZE % 2 == 0) {
    return (array[HISTORY_SIZE/2 - 1] + array[HISTORY_SIZE/2]) / 2.0;
  } else {
    return array[HISTORY_SIZE/2];
  }
}

void check_data_history(
  float treshold,
  float min,
  float max,
  float value,
  float *history
){
  float history_copy[HISTORY_SIZE];
  memcpy(history_copy, history, sizeof(history_copy));
  float median = calculate_median_float(history_copy);

  if(value > min && value < max){
      for (int i = 0; i < HISTORY_SIZE - 1; i++) {
        history[i] = history[i+1];
      }
      history[HISTORY_SIZE-1] = value;

      if(showDataHistoryPrints==true){
        if(value > median-treshold && value < median+treshold){
          Serial.print(" -- use value: ");
          Serial.println(value);
        }else{
          Serial.print(" -- don't use value: ");
          Serial.println(value);
        }
      }
  }else{
    if(showDataHistoryPrints==true){
          Serial.print("-- don't use value: ");
          Serial.println(value);
    }
  }
}

void reset_history(float *history){
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history[i] = 0.0;
    }
}
void reset_all_history(){
    reset_history(humidity_history);
    reset_history(temperature_history);
    reset_history(ec_history);
    reset_history(ph_history);
    reset_history(n_history);
    reset_history(p_history);
    reset_history(k_history);
}
