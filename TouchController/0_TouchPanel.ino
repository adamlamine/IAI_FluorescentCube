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
        

};

TouchPanel::TouchPanel(){

}

void TouchPanel::init(){
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
        this->currtouched1 = this->cap1.getTouches();
        cap1.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
        cap2.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    
        return(this->currtouched1);
}

uint16_t TouchPanel::getColumns(){
        delay(20);
        this->currtouched2 = this->cap2.getTouches();
        cap2.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
        cap1.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    
        return(this->currtouched2);
}

void TouchPanel::update() {

    if(lastEven){
        this->currtouched1 = this->cap1.getTouches();
        cap1.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
        cap2.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    
        Serial.print("A: ");
        for (int i = 8; i >= 0; i--)
        {
            bool b = bitRead(currtouched1, i);
            Serial.print(b);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        this->currtouched2 = this->cap2.getTouches();
        cap2.writeRegister(MPR121_ECR, 0x00); //CAP1 OFF
        cap1.writeRegister(MPR121_ECR, 0x8F); //CAP2 ON
    
        Serial.print("B: ");
        for (int i = 11; i >= 3; i--)
        {
            bool b = bitRead(currtouched2, i);
            Serial.print(b);
            Serial.print(" ");
        }
        Serial.println();
    }


    lastEven = !lastEven;

}
