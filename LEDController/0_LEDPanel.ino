#include <timer.h>
#include <Ticker.h>
#include <QList.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

struct Fade{
    public:
        byte row;
        byte column;
        byte value;
        byte speed;
        unsigned long currentTime = millis();
        unsigned long lastTime = millis();
};

struct LEDPanel{

    public:
        LEDPanel(int dataPin, int latchPin, int clockPin, int groundPin);
        void update();
        void setRow(byte row, byte *values);
        void setColumn(byte column, byte *values);
        void setPixel(byte row, byte column, byte value);
        byte getPixel(byte row, byte column);
        void fadeTo(byte row, byte column, byte value, byte speed);
        void clearFades();
        void clearFade(byte row, byte column);
        void clear();
        void drawRect(byte startColumn, byte startRow, byte endColumn, byte endRow, byte value);
        QList<Fade> getFadeList();

    private:
        int dataPin; //GELBES KABEL
        int latchPin; //VIOLETTES KABEL
        int clockPin; //BLAUES KABEL
        int groundPin; //WEISSES KABEL        
        void writeToRegister(unsigned long int pattern);
        void writePixel(byte row, byte column); 
        void writeRow(byte row, unsigned long int data);
        Timer<10, micros> timer;
        unsigned long currentTime = millis();
        unsigned long lastTime = millis();
        QList<Fade> fadeList;
        void handleFades();
        
        byte data[9][9] =    
        {{0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}};
};

LEDPanel::LEDPanel(int dataPin, int latchPin, int clockPin, int groundPin){
    digitalWrite(groundPin, HIGH);
    this->dataPin = dataPin;
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    this->groundPin = groundPin;
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);  
    pinMode(groundPin, OUTPUT);
}

void LEDPanel::writeToRegister(unsigned long int pattern){
    digitalWrite(this->latchPin, LOW);
    shiftOut(this->dataPin, this->clockPin, LSBFIRST, (pattern));
    shiftOut(this->dataPin, this->clockPin, LSBFIRST, (pattern >> 8));
    shiftOut(this->dataPin, this->clockPin, LSBFIRST, (pattern >> 16));
    digitalWrite(this->latchPin, HIGH);
}

void LEDPanel::writePixel(byte row, byte column){
    unsigned long int rowBits = 0b111111111 ^ 0b000000001 << (8 - row);
    unsigned long int spaltenBits = 0b000000000 ^ 0b000000001 << (8 - column);
    unsigned long int combined = (spaltenBits << 15) + (rowBits << 6);
    this->writeToRegister(combined);
}

void LEDPanel::writeRow(byte row, unsigned long int data){
    unsigned long int rowBits = data ^ 0b111111111;
    unsigned long int spaltenBits = 0b000000000 ^ 0b000000001 << (8 - row);
    unsigned long int combined = (spaltenBits << 15) + (rowBits << 6);
    this->writeToRegister(combined);
}

void LEDPanel::update(){
    static byte PWM = 0;

    for(int j = 0; j < 9; j++){
        unsigned int rowBits = 0b000000000;
        for(int k = 0; k < 9; k++){
            if(this->data[j][k] > PWM){
                bitWrite(rowBits, k, 1);
            }
        }
        this->writeRow(j, rowBits);
    }

    PWM++;
    if(PWM >= 255){
        PWM = 0;
    }

    digitalWrite(this->groundPin, LOW);
    this->timer.tick();
    this->handleFades();
}

void LEDPanel::setPixel(byte row, byte column, byte value){
    this->data[row][column] = value;
}

void LEDPanel::setRow(byte row, byte *values){
    for(int i = 0; i < 9; i++){
        this->data[row][i] = values[i];
    }
}

void LEDPanel::setColumn(byte column, byte *values){
    for(int i = 0; i < 9; i++){
        this->data[i][column] = values[i];
    }
}

void LEDPanel::fadeTo(byte row, byte column, byte value, byte speed){
    clearFade(row, column);
    Fade f;
    f.row = row;
    f.column = column;
    f.value = value;
    f.speed = speed;
    this->fadeList.push_back(f);

}

void LEDPanel::handleFades(){
    for(int i = 0; i < this->fadeList.size(); i++){
        
        Fade currentFade = this->fadeList.at(i);
        byte row = currentFade.row;
        byte column = currentFade.column;
        byte value = currentFade.value;
        byte speed = currentFade.speed;
        

        this->currentTime = millis();
        if (this->currentTime - fadeList.at(i).lastTime >= 256-speed)
        {
            
            fadeList.at(i).lastTime = this->currentTime;

            if(this->data[row][column] > value ){
                this->data[row][column]--;
            } else if(this->data[row][column] < value){
                this->data[row][column]++;
            } else {
                this->fadeList.clear(i);
                //Serial.println("cleared");
            }
        }
    }
}

void LEDPanel::clearFades(){
    this->fadeList.clear();
}

void LEDPanel::clearFade(byte row, byte column){
    for(int i = 0; i < this->fadeList.size(); i++){
        if(row == fadeList.at(i).row && column == fadeList.at(i).column ){
            this->fadeList.clear(i);
        }
    }
}

void LEDPanel::clear(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            this->data[i][j] = 0;
        }
    }
}

void LEDPanel::drawRect(byte startColumn, byte startRow, byte endColumn, byte endRow, byte value){
    for(int i = startColumn; i < endColumn; i++){
        for(int j = startRow; j < endRow; j++){
            this->data[i][j] = value;
        } 
    }
}

byte LEDPanel::getPixel(byte column, byte row){
    return this->data[column][row];
}

QList<Fade> LEDPanel::getFadeList(){
    return this->fadeList;
}



LEDPanel ledPanel(32, 33, 25, 26);