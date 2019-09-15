struct FX_PulseUp : Effect {

    public:
        void execute();
        FX_PulseUp();
        FX_PulseUp(uint16_t speed, uint16_t duration) : Effect(speed, duration){}

};

void FX_PulseUp::execute(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(ledPanel.getPixel(i,j) > 0){
                ledPanel.setPixel(i,j,(ledPanel.getPixel(i,j) - 1));
            }
        }
    }
}