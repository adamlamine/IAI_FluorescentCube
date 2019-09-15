struct TouchPanel{

    public:
        void updateRows();
        void updateColumns();
        void resetNewTouches();
        bool newTouches();
        bool touched(uint8_t x, uint8_t y);
        uint16_t newRowTouches();
        uint16_t newColumnTouches();
        uint16_t rowdata = 0b000000000;
        uint16_t columndata = 0b000000000;
        uint16_t prevRowdata = 0b000000000;
        uint16_t prevColumndata = 0b000000000;

    private:
        

};

bool TouchPanel::touched(uint8_t x, uint8_t y){
  return bitRead(rowdata, x) && bitRead(columndata, y);
}

bool TouchPanel::newTouches(){
  if(this->newRowTouches() != 0 && this->newColumnTouches() != 0){
    return true;
  } else {
    return false;
  }
}

void TouchPanel::resetNewTouches(){
  this->prevRowdata = this->rowdata;
  this->prevColumndata = this->columndata;
}

uint16_t TouchPanel::newRowTouches(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bool oldT = bitRead(prevRowdata, i);
    bool newT = bitRead(rowdata, i);
    bool touchDetected = (!oldT) && newT;
    bitWrite(data, i, touchDetected);
  }
  return data;
}

uint16_t TouchPanel::newColumnTouches(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bool oldT = bitRead(prevColumndata, i);
    bool newT = bitRead(columndata, i);
    bool touchDetected = (!oldT) && newT;
    bitWrite(data, i, touchDetected);
  }
  return data;
}

void TouchPanel::updateRows(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bitWrite(data, 8-i, digitalRead(IN_PINS[i]));
  }
  // this->prevRowdata = this->rowdata;
  this->rowdata = data;

  // Serial.print("ROWS: ");
  // for(int i = 8; i >= 0; i--){
  //     bool b = bitRead(data, i);
  //     Serial.print(b);Serial.print(" ");
  // }
  // Serial.println();
}

void TouchPanel::updateColumns(){
  uint16_t data = 0b000000000;
  for(int i = 0; i < 9; i++){
    bitWrite(data, i, digitalRead(IN_PINS[i]));
  }
  // this->prevColumndata = this->columndata;
  this->columndata = data;

  // Serial.print("COLUMNS: ");
  // for(int i = 8; i >= 0; i--){
  //     bool b = bitRead(data, i);
  //     Serial.print(b);Serial.print(" ");
  // }
  // Serial.println();
}

TouchPanel touchPanel;