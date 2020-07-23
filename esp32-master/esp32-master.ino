#include <Wire.h>

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin();
    //Wire.onReceive(receiveEvent);
}

void loop() {
    // put your main code here, to run repeatedly:
    int16_t buf[2];
    uint16_t x,y;

    // 8番のデバイスに0x21を送る
    Wire.beginTransmission(8);
    Wire.write(0x21);

    // 8番のデバイスから2バイト読み込む
    Wire.requestFrom(8,2);

    // 読み込んだデータを変数に読み出す
    buf[0] = Wire.read();
    buf[1] = Wire.read();

    // intのデータが正(正常終了)ならビット演算で16ビット非負整数にする
    if(buf[0]>=0 && buf[1]>=0) {
        x = ( (uint8_t)buf[0])<<8  | buf[1];
    }
    // 一度通信を終了する
    Wire.endTransmission();
    delay(100);

    // 同様に8番のデバイスに0x22を送り, 16ビット非負整数を読み出す
    Wire.beginTransmission(8);
    Wire.write(0x22);
    Wire.requestFrom(8,2);
    buf[0] = Wire.read();
    buf[1] = Wire.read();
    if(buf[0]>=0 && buf[1]>=0) {
        y  = ( (uint8_t)buf[0])<<8  | buf[1];
    }
    Wire.endTransmission();

    // 表示する
    Serial.print("x: ");
    Serial.print(x);
    Serial.print("\ty: ");
    Serial.println(y);

    delay(250);
}
