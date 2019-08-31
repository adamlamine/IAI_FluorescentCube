struct TouchPanel{

    public:
        TouchPanel();
        void update();
        void init();


    private:
        Adafruit_MPR121 cap1 = Adafruit_MPR121();
        Adafruit_MPR121 cap2 = Adafruit_MPR121();
        uint16_t lasttouched1 = 0;
        uint16_t currtouched1 = 0;
        uint16_t lasttouched2 = 0;
        uint16_t currtouched2 = 0;

};

TouchPanel::TouchPanel(){

}

void TouchPanel::init(){
    if (!cap1.begin(0x5A)) {
        Serial.println("MPR121 A not found, check wiring?");
    } else {
        Serial.println("MPR121 A found!");
    }

    // if (!cap2.begin(0x5C)) {
    //     Serial.println("MPR121 B not found, check wiring?");
    // } else {
    //     Serial.println("MPR121 B found!");
    // }

    cap1.setThreshholds(9, 4);
    // cap2.setThreshholds(10, 5);
}

void TouchPanel::update() {

    this->currtouched1 = this->cap1.touched();
    // this->currtouched2 = this->cap2.touched();

    ledPanel.clear();
    for (int i = 2; i >= 0; i--)
    {
        for(int j = 5; j >= 3; j--)
        {
            int k = j - 3;
            if(bitRead(currtouched1, j) && bitRead(currtouched1, i))
            {   
                ledPanel.drawRect((i*3), (k*3), (i*3+3), (k*3+3), 255);
            }
        }
    }

    for (int i = 5; i >= 0; i--)
    {
        bool b = bitRead(currtouched1, i);
        Serial.print(b);
    }
    Serial.println();


    //For A----------------------------------------------------------
    // for (uint8_t i=0; i<12; i++) {
    //     if ((this->currtouched1 & _BV(i)) && !(this->lasttouched1 & _BV(i)) ) {
    //         Serial.print(i); Serial.println(" touched of A");
    //     }

    //     if (!(this->currtouched1 & _BV(i)) && (this->lasttouched1 & _BV(i)) ) {
    //         Serial.print(i); Serial.println(" released o A");
    //     }


    //     //For B----------------------------------------------------------
    //     if ((this->currtouched2 & _BV(i)) && !(this->lasttouched2 & _BV(i)) ) {
    //         Serial.print(i); Serial.println(" touched of B");
    //     }

    //     if (!(this->currtouched2 & _BV(i)) && (this->lasttouched2 & _BV(i)) ) {
    //         Serial.print(i); Serial.println(" released of B");
    //     }


    // }

    this->lasttouched1 = this->currtouched1;
    // this->lasttouched2 = this->currtouched2;
}
