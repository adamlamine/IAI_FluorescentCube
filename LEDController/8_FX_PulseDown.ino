struct FX_PulseDown : Effect {

    public:
        void execute();
        FX_PulseDown();
        FX_PulseDown(uint16_t speed, uint16_t duration) : Effect(speed, duration){}

};

void FX_PulseDown::execute(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(ledPanel.getPixel(i,j) < 255){
                ledPanel.setPixel(i,j,(ledPanel.getPixel(i,j) + 1));
            }
        }
    }
}