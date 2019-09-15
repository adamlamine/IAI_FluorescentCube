struct FX_touchFade : Effect {

    public:
        void execute();
        FX_touchFade();
        FX_touchFade(uint16_t speed, uint16_t duration) : Effect(speed, duration){}

};

void FX_touchFade::execute(){ 
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(touchPanel.touched(i,j) && ledPanel.getPixel(i,j) < 255){
                ledPanel.setPixel(i,j,(ledPanel.getPixel(i,j) + 1));
            } else if(!touchPanel.touched(i,j) && ledPanel.getPixel(i,j) > 0) {
                ledPanel.setPixel(i,j,(ledPanel.getPixel(i,j) - 1));
            }
        }
    }
}