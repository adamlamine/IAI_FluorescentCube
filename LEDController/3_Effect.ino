struct Effect{
    
    public:
        Effect();
        Effect(uint16_t speed, uint16_t duration);
        uint16_t speed;
        bool plays = true;
        uint16_t duration;
        bool playing();
        void stop();
        void update();
        // void execute();
        virtual void execute();
        void setParams(int, int, int){};

    private:    
        unsigned long currentTime = millis();
        unsigned long speedLastTime = millis();
        unsigned long effectStartTime = millis();
};

Effect::Effect(){

};

Effect::Effect(uint16_t speed, uint16_t duration){
    this->speed = speed;
    this->duration = duration;
}

void Effect::update(){
    this->currentTime = millis();
    if(this->currentTime - this->speedLastTime > (1000 - speed)){
        this->execute();
        this->speedLastTime = currentTime;
    }
    if((this->effectStartTime + this->duration) < this->currentTime){
        this->plays = false;
        this->duration = 0;
        this->speed = 0;
    }
}

void Effect::execute(){
    Serial.println("execute() - Effect");
    return;
}

bool Effect::playing(){
    return (bool)plays;
}

void Effect::stop(){
    this->plays = false;
}


bool operator == (const Effect &e1, const Effect &e2)
{
   if(&e1 == &e2)
     return true;
   else
     return false;
}