struct FX_randomBlink : Effect {

    public:
        void execute();
        FX_randomBlink();
        FX_randomBlink(uint16_t speed, uint16_t duration) : Effect(speed, duration){};

};

void FX_randomBlink::execute(){
    static bool on = true;
    for(int i = 0; i < 15; i++){
        if(on){ledPanel.setPixel(floor(random(9)), floor(random(9)), 255);}else{ledPanel.clear();}
    }
    on = !on;
}
                    