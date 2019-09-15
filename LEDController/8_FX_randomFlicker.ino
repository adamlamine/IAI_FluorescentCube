struct FX_randomFlicker : Effect {

    public:
        void execute();
        FX_randomFlicker();
        FX_randomFlicker(uint16_t speed, uint16_t duration) : Effect(speed, duration){};

};

void FX_randomFlicker::execute(){
    static bool on = true;
    int x[] = {4,7,8,1,3,6,2,5,0,6,3,5,1,2};
    int y[] = {3,1,7,0,5,8,6,4,2,1,8,2,0,5};
    // for(int i = 0; i < 14; i++){
    //     if(random(10) > 2){
    //         ledPanel.setPixel(x[i], y[i], 255);
    //     } else {
    //         ledPanel.setPixel(x[i], y[i], 0);
    //     }
    // }
        if(random(10) > 2){
            ledPanel.setPixel(4, 4, 255);
        } else {
            ledPanel.setPixel(4, 4, 0);
        }
}
                    