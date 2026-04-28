int pots[] = {34, 35, 32};
int btns[] = {25, 26, 27};
int lastVals[] = {-1, -1, -1};
int leds[] = {18, 19, 21};
bool btnslast[] = {true, true, true};
unsigned long lastPress[3] = {0,0,0};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    pinMode(btns[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    int val = analogRead(pots[i]);
    int vol = map(val, 0, 4095, 0, 100);
    int buttonState = digitalRead(btns[i]);
    if (buttonState == LOW && millis() - lastPress[i] > 150){
      if (btnslast[i] == true){
        btnslast[i] = false;
        digitalWrite(leds[i], LOW);
        Serial.println(String(i) + ":mute");
      }else {
        btnslast[i] = true;
        digitalWrite(leds[i], HIGH);
        Serial.println(String(i) + ":unmute");
      }
      lastPress[i] = millis();
    }else{

    } 

    if (abs(vol - lastVals[i]) >= 2) {
      lastVals[i] = vol;
      

      // Format: index:value
      Serial.print(i);
      Serial.print(":");
      Serial.println((int)vol);
    }
  }

  delay(50);
}