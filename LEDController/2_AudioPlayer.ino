struct AudioPlayer{

    public:
        AudioPlayer(uint8_t pin);
        uint8_t pin;
        bool pinstate = false;
        uint8_t currentTrack = 0;
        uint8_t transmissionQueue = 0;
        void playTrack(uint8_t tracknumber);
        void stop();
        void update();
};

AudioPlayer::AudioPlayer(uint8_t pin){
    this->pin = pin;
}

void AudioPlayer::playTrack(uint8_t tracknumber){
    this->currentTrack = tracknumber;
    this->transmissionQueue = tracknumber+1;
}

void AudioPlayer::stop(){
        digitalWrite(this->pin, HIGH);
}

void AudioPlayer::update(){
    if(transmissionQueue > 0){
        digitalWrite(this->pin, !this->pinstate);
        this->pinstate = !this->pinstate;
        transmissionQueue--;
    }
}

AudioPlayer audioPlayer(2);