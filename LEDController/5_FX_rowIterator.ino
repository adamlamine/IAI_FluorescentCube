struct FX_rowIterator : Effect {

    public:
        FX_rowIterator();
        FX_rowIterator(uint16_t speed, uint16_t duration) : Effect(speed, duration){};
        void execute();


};

void FX_rowIterator::execute(){
    static int i = 0;
    static int j = 0;
    if(i > 0){
        ledPanel.setPixel(j,i-1,64);
        // ledPanel.fadeTo(i-1,j,0,255);
    }

    if(i <= 9){
        if(j <= 9){
        ledPanel.setPixel(j,i-1,255);
        // ledPanel.fadeTo(i,j,255,255);
        } else {
        j = 0;
        }
    } else {
        i = 0;
        j++;
    }

    i++;
    if(i == 9 && j == 9){
        ledPanel.clear();
    }

}