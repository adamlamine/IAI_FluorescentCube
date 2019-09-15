struct FX_randomFades : Effect {

    public:
        void execute();
        FX_randomFades();
        FX_randomFades(uint16_t speed, uint16_t duration) : Effect(speed, duration){}

};

void FX_randomFades::execute(){ 
    for(int i = 0; i < 2; i++){
        ledPanel.fadeTo(floor(random(9)), floor(random(9)), floor(random(0, 255)), floor(random(240, 255)));
    }
    for(int i = 0; i < 5; i++){
        ledPanel.fadeTo(floor(random(9)), floor(random(9)), 0, floor(random(250, 255)));
    }
}