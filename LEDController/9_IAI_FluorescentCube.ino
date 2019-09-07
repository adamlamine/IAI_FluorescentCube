#include <SimplexNoise.h>
SimplexNoise sn;

auto timer = timer_create_default();

TouchPanel touchPanel;

unsigned long currentTime = millis();
unsigned long lastTime = millis();


void setup() {
  Serial.begin(115200);
  touchPanel.init();
  timer.every(500, matrixTestChange);
  ledPanel.setPixel(4, 4, 127);
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

  currentTime = millis();
  if (currentTime - lastTime >= 80)
  {
      lastTime = currentTime;
  }


}
