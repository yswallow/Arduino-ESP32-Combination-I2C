#include <Wire.h>

// 関数間で共有する変数
uint16_t x,y;
uint8_t command;
void setup() {
  // put your setup code here, to run once:
    
    Serial.begin(115200);
    delay(100);
    
    // 8番のデバイスとしてI2Cを開始する
    Wire.begin(8);
    
    // イベントリスナーを登録する
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop() {
  // 100ミリ秒ごとに値を記録する
    x = analogRead(A2);
    y = analogRead(A3);
    delay(100);
}

// Masterがwrite()を実行すると呼ばれる
void receiveEvent(int howMany) {
    // Masterから送られてきた値を記録する
    command = Wire.read();
}

// MasterがrequestFrom()を実行すると呼ばれる
void requestEvent(void) {
    uint8_t buf[2] = {0,0};
    // commandが0x21ならxの値を, 0x22ならyの値を返す
    switch(command){
        case(0x21):
            buf[0] = 0xFF & x>>8;
            buf[1] = 0xFF & x;

            // 配列bufの値を2つMasterに送る
            Wire.write(buf, 2);
            
            Serial.print("x: ");
            Serial.println(x);
        break;
        case(0x22):
            buf[0] = 0xFF & y>>8;
            buf[1] = 0xFF & y;
            Wire.write(buf, 2);
            Serial.print("y: ");
            Serial.println(y);
        break;
        default:
            Wire.write(buf, 2);
        break;
    }
 }
