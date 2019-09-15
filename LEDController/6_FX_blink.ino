struct FX_blink : Effect {

    public:
        FX_blink();
        FX_blink(uint16_t speed, uint16_t duration) : Effect(speed, duration){};
        void execute();

        

};

void FX_blink::execute(){
    static bool on = false;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(on){ledPanel.setPixel(i, j, 255);}else{ledPanel.setPixel(i, j, 0);}
        }
    }
    on = !on;
}