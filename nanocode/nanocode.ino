const boolean TEST = false;

int PHOTO_INPUT = 7;    // using pin 7 as photcell input 
int FLAME_INPUT = 8;    // using pin 8 as flame input 
int THERM_INPUT = 9;    // using pin 9 as thermistor input 
int WIFI_OUTPUT = 13;   // using pin 13 as output to wifi mod
int BUZZER_OUTPUT = 12;
  
int val1;
int val2;
int val3;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(PHOTO_INPUT, INPUT);
  pinMode(FLAME_INPUT, INPUT);
  pinMode(THERM_INPUT, INPUT);

  pinMode(WIFI_OUTPUT, OUTPUT);
  pinMode(BUZZER_OUTPUT, OUTPUT);
  
  Serial.begin(9600);
  
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WIFI_OUTPUT, LOW);
}

void loop() {
  if(!TEST){
    val1 = 0;
    val2 = 0;
    val3 = 0;
    for(int i = 0; i < 6; i++){
      val1 += digitalRead(PHOTO_INPUT);
      val2 += digitalRead(FLAME_INPUT);
      val3 += digitalRead(THERM_INPUT);
      delay(300);
    }
    val1 /= 6;
    val2 /= 6;
    val3 /= 6;
    
    Serial.println("AVG PHOTO READ: " + val1);
    Serial.println("AVG FLAME READ: " + val2);
    Serial.println("AVG THERM READ: " + val3);
  
    //CONDITIONS TO SEND TO WIFI NOT DONE
    if (val1 == 0){
      digitalWrite(WIFI_OUTPUT, LOW);
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off (LOW is the voltage level)
    }
    else if (val1 == 1){
      digitalWrite(WIFI_OUTPUT, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(BUZZER_OUTPUT, HIGH);
    }
    
  }
  else{
    val1 = digitalRead(PHOTO_INPUT);
    val2 = digitalRead(FLAME_INPUT);
    val3 = digitalRead(THERM_INPUT);
    Serial.println("PHOTO READ: " + val1);
    Serial.println("FLAME READ: " + val2);
    Serial.println("THERM READ: " + val3);
  }
    delay(1000);                       // wait for a second
}
