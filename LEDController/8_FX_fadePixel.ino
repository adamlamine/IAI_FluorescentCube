struct FX_fadePixel : Effect {

    public:
        void execute();
        FX_fadePixel();
        FX_fadePixel(uint16_t speed, uint16_t duration) : Effect(speed, duration){}
        uint8_t x;
        uint8_t y;
        uint8_t val;
        void setParams(uint8_t x, uint8_t y, uint8_t val);

};

void FX_fadePixel::execute(){ 
    if(ledPanel.getPixel(x,y) < val){
        ledPanel.setPixel(x,y,(ledPanel.getPixel(x,y) + 1));
    }
}

void FX_fadePixel::setParams(uint8_t x, uint8_t y, uint8_t val){
    this->x = x;
    this->y = y;
    this->val = val;
}
