struct FX_pause : Effect {

    public:
        FX_pause();
        FX_pause(uint16_t speed, uint16_t duration) : Effect(speed, duration){};

    private:
        void execute();


};

void FX_pause::execute(){

}
