#include <queue>
using std::queue;

auto timer = timer_create_default();

unsigned long currentTime = millis();
unsigned long ledLastTime = millis();

unsigned long audioCurrentTime = millis();
unsigned long audioLastTime = millis();

uint8_t currentRoutine = 0;

void setup() {
  Serial.begin(115200);
  // timer.every(500, matrixTestChange);
  // ledPanel.setPixel(4,4,255);
  attachInterrupt(digitalPinToInterrupt(IN_PINS[9]), refreshTouch, CHANGE);
  Serial.println("SETUP");
  // ledPanel.writeToRegister(0b001110000000000000000001);
  pinMode(2, OUTPUT);
  
  delay(4500);
  audioPlayer.playTrack(10);
  currentRoutine = 0;
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

  ledPanel.update();
  timer.tick();
  doRoutines();

  currentTime = millis();
  if (currentTime - ledLastTime >= 80)
  {   
      ledPanel.handleFades();
      ledLastTime = currentTime;
  }

  if (currentTime - audioLastTime > 1)
  {   
      effectManager.update();
      audioPlayer.update();
      audioLastTime = currentTime;
  }


}


void doRoutines(){
  switch(currentRoutine){
    
    case 0:
      {
      static bool first = true;
      if(first){
        effectManager.add(new FX_rowIterator(950,10000));
        effectManager.add(new FX_pause(0,12700));
        first = false;
      }
      if(!effectManager.isPlaying()){currentRoutine = 1;};
      }
    break;

    case 1:
    {
      int touchCount = 0;
      static bool first = true;
      if(first){
        Serial.println("STAGE 1");
        ledPanel.clear();
        audioPlayer.playTrack(1);
        first = false;
        // Effect * fp = new FX_fadePixel(970,1000);
        // fp->setParams(4,4,255);
        // effectManager.add(fp);
      }
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(touchPanel.touched(i,j)){
                touchCount++;
            }
        }
      }
      if(touchCount > 45){
        currentRoutine = 2;
      }
      if(!effectManager.isPlaying()){
        effectManager.add(new FX_touchFade(995,300));
      }
      // ledPanel.setPixel(4,4,255);
    }
    break;
    
    case 2:
      {
      int touchCount = 0;
      static bool first = true;
      static int triggerCount = 0;
      if(first){
        Serial.println("STAGE 2");
        effectManager.clear();
        ledPanel.clearFades();
        ledPanel.clear();
        first = false;
        audioPlayer.playTrack(12);
        delay(75);
        audioPlayer.playTrack(2);
        effectManager.add(new FX_blink(930,220));
      }
      
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(touchPanel.touched(i,j)){
                touchCount++;
            }
        }
      }
      if(!effectManager.isPlaying() && touchCount > 2){
        if(triggerCount < 3){
          //AUDIOEFFEKT FEHLT
          effectManager.add(new FX_blink(930,450));
          audioPlayer.playTrack(11);
        } else if(triggerCount < 5){
          effectManager.add(new FX_randomBlink(900,420));
          audioPlayer.playTrack(12);
        } else{
          currentRoutine = 3;
        }
        effectManager.add(new FX_pause(0,1500));
        triggerCount++;
      }

      if(!effectManager.isPlaying()){
        effectManager.add(new FX_randomFades(800,200));
      }
      // Serial.print("triggerCount: "); Serial.println(triggerCount);

      }
    break;

    case 3:
    static bool first = true;
    if(first){
        effectManager.clear();
        ledPanel.clearFades();
        ledPanel.clear();
        first = false;
        delay(250);
        audioPlayer.playTrack(12);
        delay(550);
        audioPlayer.playTrack(3);
      }
      int touches = 0;
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(touchPanel.touched(i,j)){
                touches++;
                ledPanel.setPixel(i,j, 0);
            }
        }
      }

      static bool pulse = false;
      static int playCounter = 0;

      if(!effectManager.isPlaying()){
        playCounter++;
        if(pulse){
          effectManager.add(new FX_PulseUp(985,7000));
        } else {
          effectManager.add(new FX_PulseDown(985,7000));
        }
        audioPlayer.playTrack(3);
        effectManager.add(new FX_randomFlicker(940,7000));
        // effectManager.add(new FX_randomFlicker(970,4000/touches));
        // effectManager.add(new FX_touchFade(990,4000/touches));
        pulse = !pulse;
      }

      if(playCounter > 12){
        currentRoutine = 1;
      }

    break;



  }
}