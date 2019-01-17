#include <mio2_RoEn.h>
#include <Wire.h>

RoEn rswitch;
int dataRE;
int pdataRE;

int Xst; //X
int Yst; //Y
int Tst; //ボタン

int lb_b; //左裏
int rl_b; //左クリック
int rr_b; //右クリック

void setup() {
  Serial.begin(9600);
  //ロータリーエンコーダ
  rswitch.ESet(26, 25);


  //ジョイスティック
  pinMode(2, INPUT); //X
  pinMode(35, INPUT); //Y
  pinMode(34, INPUT_PULLUP); //クリック

  //各種ボタン
  pinMode(27, INPUT_PULLUP); //左裏クリック
  pinMode(23, INPUT_PULLUP); //左クリック
  pinMode(4, INPUT_PULLUP); //右クリック
}

void loop() {
  dataRE = rswitch.EGet();
  if (pdataRE != dataRE) {
    Serial.println(dataRE);
  }
  pdataRE = dataRE;

  Xst = analogRead(2);
  Yst = analogRead(35);
  Tst = analogRead(34);
  if (Xst <= 1) {
    Serial.print("←");
  } else if (Xst >= 200) {
    Serial.print("→");
  } else {
    Serial.print("〇");
  }
  Serial.print(",");
  if (Yst <= 1) {
    Serial.print("↓");
  } else if (Yst >= 200) {
    Serial.print("↑");
  } else {
    Serial.print("◇");
  }
  Serial.print(",");
  if (Tst != 0) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  lb_b = analogRead(27);
  rl_b = analogRead(23);
  rr_b = analogRead(4);
  if (lb_b >= 4000) {
    Serial.print("ON");
  } else {
    Serial.print("OFF");
  }
  Serial.print(",");
  if (rl_b >= 4000) {
    Serial.print("ON");
  } else {
    Serial.print("OFF");
  }
  Serial.print(",");
  if (rr_b >= 4000) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.println("");

  delay(500);
}
