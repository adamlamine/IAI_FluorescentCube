#include <timer.h>
auto timer = timer_create_default();

LEDPanel ledPanel(32, 33, 25, 26);


void setup() {
  Serial.begin(9600);
  timer.every(10, matrixTestChange);
}

bool matrixTestChange(void *){

    static bool iteration = false;
    static int i = 0;
    

    if(!iteration){
      i++;
      if(i > 155){
        iteration = true;
      }
    } else {
      i--;
      if(i < 1){
        iteration = false;
      }
    }


    byte newInput[9][9] ={{i,0,0,0,i,i,i,i,i},
                          {i,0,0,0,i,0,0,0,0},
                          {i,0,0,0,i,0,0,0,0},
                          {i,0,0,0,i,0,0,0,0},
                          {i,i,i,i,i,i,i,i,i},
                          {0,0,0,0,i,0,0,0,i},
                          {0,0,0,0,i,0,0,0,i},
                          {0,0,0,0,i,0,0,0,i},
                          {i,i,i,i,i,0,0,0,i}};
    
    for(int j = 0; j < 9; j++){
        for(int k = 0; k < 9; k++){
          ledPanel.data[j][k] = newInput[j][k];
        }
    }

    return true;
}




void loop() {

  ledPanel.update();
  timer.tick();
}
