#include <Adafruit_MPR121.h>


struct TouchPanel{

    public:
        TouchPanel();
        void update();
        void init();
        uint16_t getRows();
        uint16_t getColumns();


    private:
        Adafruit_MPR121 cap1 = Adafruit_MPR121();
        Adafruit_MPR121 cap2 = Adafruit_MPR121();
        uint16_t lasttouched1 = 0;
        uint16_t currtouched1 = 0;
        uint16_t lasttouched2 = 0;
        uint16_t currtouched2 = 0;
        bool lastEven = true;
        uint16_t rowtouches = 0b000000000000;
        uint16_t coltouches = 0b000000000000;
        

};

TouchPanel::TouchPanel(){

}

void TouchPanel::init(){

    delay(5000);
    
    cap1.begin(0x5A);
    delay(500);
    cap1.calibrate();
    cap1.writeRegister(MPR121_ECR, 0x00);
    delay(500);
    cap2.begin(0x5C);
    delay(500);
    cap2.calibrate();
    cap2.writeRegister(MPR121_ECR, 0x00);
    cap1.writeRegister(MPR121_ECR, 0x8F);
    delay(50);
    
}

uint16_t TouchPanel::getRows(){
    delay(20);
    this->currtouched1 = this->cap1.getTouches(false);
    cap1.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
    cap2.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    this->rowtouches = this->currtouched1;
    return(this->currtouched1);
}

uint16_t TouchPanel::getColumns(){
    delay(20);
    this->currtouched2 = this->cap2.getTouches(true);
    cap2.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
    cap1.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    this->coltouches = this->currtouched2;
    return(this->currtouched2);
}

void TouchPanel::update() {
    for(uint16_t i = 0; i < 12; i++){
        for(uint16_t j = 0; j < 12; j++){
            bool x = bitRead(this->rowtouches, i);
            bool y = bitRead(this->rowtouches, j);
        }
    }
}
