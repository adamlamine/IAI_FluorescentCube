auto timer = timer_create_default();

unsigned long currentTime = millis();
unsigned long lastTime = millis();

unsigned long currentTime2 = millis();
unsigned long lastTime2 = millis();

uint8_t currentRoutine = 0;

void setup() {
  Serial.begin(115200);
  // timer.every(500, matrixTestChange);
  ledPanel.setPixel(4, 4, 127);
  attachInterrupt(digitalPinToInterrupt(IN_PINS[9]), refreshTouch, CHANGE);
  Serial.println("SETUP");
  // ledPanel.writeToRegister(0b001110000000000000000001);
  pinMode(2, OUTPUT);
  
  delay(3500);
  audioPlayer.playTrack(10);
}

void refreshTouch(){
  if(digitalRead(IN_PINS[9]) == HIGH){
    touchPanel.updateRows();
  } else {
    touchPanel.updateColumns();
  }
}


bool matrixTestChange(void *){
    ledPanel.fadeTo(floor(random(9)), floor(random(9)), floor(random(0, 255)), floor(random(192, 255)));
    ledPanel.fadeTo(floor(random(9)), floor(random(9)), 0, floor(random(128, 255)));
    ledPanel.fadeTo(floor(random(9)), floor(random(9)), 0, floor(random(128, 255)));
    ledPanel.fadeTo(floor(random(9)), floor(random(9)), 0, floor(random(128, 255)));

    return true;
}


void loop() {
  doRoutines();
  ledPanel.update();
  timer.tick();

  currentTime = millis();
  if (currentTime - lastTime >= 80)
  {   
      ledPanel.handleFades();
      lastTime = currentTime;
  }

  currentTime2 = millis();
  if (currentTime2 - lastTime2 > 1)
  {   
      audioPlayer.update();
      lastTime2 = currentTime2;
  }

  ledPanel.clear();
  for(int i = 0; i < 9; i++){
    for(byte j = 0; j < 9; j++){
        bool x = bitRead(touchPanel.rowdata, i);
        bool y = bitRead(touchPanel.columndata, j);
        if(x && y){
          ledPanel.setPixel(i,j,255);
        }
    }
  }

}


void doRoutines(){

}