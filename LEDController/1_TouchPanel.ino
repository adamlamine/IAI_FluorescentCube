struct TouchPanel{

    public:
        void updateRows();
        void updateColumns();
        uint16_t rowdata = 0b000000000;
        uint16_t columndata = 0b000000000;

    private:
        

};


void TouchPanel::updateRows(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bitWrite(data, 8-i, digitalRead(IN_PINS[i]));
  }
  this->rowdata = data;

  // Serial.print("ROWS: ");
  for(int i = 8; i >= 0; i--){
      bool b = bitRead(data, i);
      // Serial.print(b);Serial.print(" ");
  }
  // Serial.println();
}

void TouchPanel::updateColumns(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bitWrite(data, i, digitalRead(IN_PINS[i]));
  }
  this->columndata = data;

  // Serial.print("COLUMNS: ");
  for(int i = 8; i >= 0; i--){
      bool b = bitRead(data, i);
      // Serial.print(b);Serial.print(" ");
  }
  // Serial.println();
}

TouchPanel touchPanel;