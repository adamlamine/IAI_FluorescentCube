struct LEDPanel{

    public:
        LEDPanel(int dataPin, int latchPin, int clockPin, int groundPin);
        byte data[9][9] =    {{0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0}};
        void update();
        setRow(int row, byte values[9]);
        setPixel(int row, int column, byte value);


    private:
        int dataPin; //GELBES KABEL
        int latchPin; //VIOLETTES KABEL
        int clockPin; //BLAUES KABEL
        int groundPin; //WEISSES KABEL        
        void writeToRegister(unsigned long int pattern);
        void writePixel(int line, int column); 
        void writeLine(int line, unsigned long int data);

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

void LEDPanel::writePixel(int line, int column){
    unsigned long int lineBits = 0b111111111 ^ 0b000000001 << (8 - line);
    unsigned long int spaltenBits = 0b000000000 ^ 0b000000001 << (8 - column);
    unsigned long int combined = (spaltenBits << 15) + (lineBits << 6);
    this->writeToRegister(combined);
}

void LEDPanel::writeLine(int line, unsigned long int data){
    unsigned long int lineBits = data ^ 0b111111111;
    unsigned long int spaltenBits = 0b000000000 ^ 0b000000001 << (8 - line);
    unsigned long int combined = (spaltenBits << 15) + (lineBits << 6);
    this->writeToRegister(combined);
}

void LEDPanel::update(){
    static int PWM = 0;

    for(int j = 0; j < 9; j++){
        unsigned int lineBits = 0b000000000;
        for(int k = 0; k < 9; k++){
            if(this->data[j][k] > PWM){
                bitWrite(lineBits, k, 1);
            }
        }
        this->writeLine(j, lineBits);
    }

    PWM++;
    if(PWM > 128){
        PWM = 0;
    }

    digitalWrite(this->groundPin, LOW);
}

void LEDPanel::setPixel(int row, int column, byte value){

}

void LEDPanel::setRow(int row, byte values[9]){
    
}