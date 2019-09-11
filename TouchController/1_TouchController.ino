TouchPanel touchPanel;
uint8_t OUT_PINS[10] = {14,15,16,17,18,19,23,4,27,13};

void setup() {
  Serial.begin(115200);
  touchPanel.init();


}

void loop() {


    sendRows(touchPanel.getRows());
    sendColumns(touchPanel.getColumns());
    for(int i = 0; i < 10; i++){
        pinMode(OUT_PINS[i], OUTPUT);
    }

    touchPanel.update();

    // Serial.print("ROWS: ");
    // for (int i = 8; i >= 0; i--)
    // {
    //     bool b = bitRead(rows_output, i);
    //     Serial.print(b);
    //     Serial.print(" ");
    // }
    // Serial.println();

    
    // Serial.print("COLUMNS: ");
    // for (int i = 8; i >= 0; i--)
    // {
    //     bool b = bitRead(columns_output, i);
    //     Serial.print(b);
    //     Serial.print(" ");
    // }
    // Serial.println();
}

void sendRows(uint16_t rows_raw){
    uint16_t rows_output = 0b000000000;
    for (int i = 8; i >= 0; i--)
    {
        bool b = bitRead(rows_raw, i);
        bitWrite(rows_output, i, b);
    }

    delay(2);
    for (int i = 8; i >= 0; i--)
    {
        digitalWrite(OUT_PINS[i], bitRead(rows_output, i));
    }
    digitalWrite(OUT_PINS[9], 1);
}

void sendColumns(uint16_t columns_raw){
    uint16_t columns_output = 0b000000000;
    for (int i = 11; i >= 3; i--)
    {
        bool b = bitRead(columns_raw, i);
        bitWrite(columns_output, i-3, b);
    }

    delay(2);
    for (int i = 8; i >= 0; i--)
    {
        digitalWrite(OUT_PINS[i], bitRead(columns_output, i));
    }
    digitalWrite(OUT_PINS[9], 0);
}