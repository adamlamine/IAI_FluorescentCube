struct EffectManager{

    public:
        void update();
        void add(Effect* effect);
        void get(uint8_t index);
        bool isPlaying();
        bool isPlaying(Effect* e);
        void clear();

    private:
        QList<Effect*> effectList;




};

void EffectManager::update(){
    for(int i = 0; i < this->effectList.size(); i++){
        this->effectList.at(i)->update();
        if(!this->effectList.at(i)->playing()){
            effectList.clear(i);
        }
    }
}

bool EffectManager::isPlaying(Effect* e){ 
    int pos = this->effectList.indexOf(e);
    if(pos < 0){return false;}
    return this->effectList.at(pos)->playing();
}

bool EffectManager::isPlaying(){
    for(int i = 0; i < this->effectList.size(); i++){
        if(this->effectList.at(i)->playing()){
            return true;
        }
    }
    return false;
}

void EffectManager::add(Effect* effect){
    this->effectList.push_back(effect);
}

void EffectManager::clear(){
    this->effectList.clear();
}


EffectManager effectManager;