#include <ST7032.h>
#include <Wire.h>
#include <mio2_RoEn.h>

#define DATASETS 6
int datas[DATASETS] = {0, 0, 0, 0, 0, 0};  // lbt,xjoy,yjoy,joyt,re,rbs
int senD[DATASETS] = {0, 0, 0, 0, 0, 0};

unsigned long circ;

RoEn rswitch;
int pdataRE;

ST7032 lcd;

const int xjoy = 14;
const int yjoy = 15;
const int tjoy = 25;
const int lbt = 26;
const int re1 = 16;
const int re2 = 17;
const int rbs = 0;

// const int display = ;
// const int nax = ;

const int joydev[2][2] = {{30, 250}, {1000, 3000}};  // 0-80-300 //0-2200-4496
const int regdev[3] = {900, 1800, 2500};             // 200-1500-2000-3000

void setup() {
  circ = millis();
  Serial.begin(9600);

  // LeftSetting
  pinMode(tjoy, INPUT_PULLUP);
  pinMode(xjoy, INPUT);  // X
  pinMode(yjoy, INPUT);  // Y
  pinMode(lbt, INPUT_PULLUP);

  // RightSetting
  rswitch.ESet(re2, re1);
  pinMode(rbs, INPUT);
  pinMode(2, OUTPUT);

  // LCD表示領域設定(8桁, 2行)
  lcd.begin(8, 2);

  // コントラスト設定(0〜63)
  lcd.setContrast(30);
}

void loop() {
  datas[0] = digitalRead(lbt);
  datas[1] = analogRead(xjoy);
  datas[2] = analogRead(yjoy);
  datas[3] = digitalRead(tjoy);
  datas[4] = rswitch.EGet();
  datas[5] = analogRead(rbs);

  String L1, L2;

  if (datas[3] == 0) {
    L1 = "O";
    senD[0] = 1;
  } else {
    L1 = "X";
    senD[0] = 0;
  }

  if (datas[0] == 0) {
    L2 = "O";
    senD[1] = 1;
  } else {
    L2 = "X";
    senD[1] = 0;
  }

  if (datas[1] <= joydev[datas[0]][0]) {
    L1.concat("A   ");
    senD[2] = 1;
  } else if (datas[1] >= joydev[datas[0]][1]) {
    L1.concat(" D  ");
    senD[2] = 2;
  } else {
    L1.concat("    ");
    senD[2] = 0;
  }

  if (datas[2] <= joydev[datas[0]][0]) {
    L2.concat("W   ");
    senD[3] = 2;
  } else if (datas[2] >= joydev[datas[0]][1]) {
    L2.concat(" S  ");
    senD[3] = 1;
  } else {
    L2.concat("    ");
    senD[3] = 0;
  }

  L1.concat(datas[4]);
  senD[4] = datas[4];
  /*if (pdataRE != datas[4]) {
        Serial.print(datas[4]);
    //}
    //pdataRE = datas[4];
*/

  if (datas[5] < regdev[0]) {
    L1.concat("X");
    L2.concat("OX");
    senD[5] = 1;
  } else if (regdev[0] < datas[5] && datas[5] < regdev[1]) {
    // Serial.print("2");
    L1.concat("X");
    L2.concat("XO");
    senD[5] = 2;
  } else if (regdev[1] < datas[5] && datas[5] < regdev[2]) {
    // Serial.print("3");]
    L1.concat("O");
    L2.concat("XX");
    senD[5] = 3;
  } else {
    // Serial.print("0");
    L1.concat("X");
    L2.concat("XX");
    senD[5] = 0;
  }
  //        Serial.println();
  // LCD表示(1行目)
  lcd.setCursor(0, 0);
  lcd.print(L1);
  // LCD表示(2行目)
  lcd.setCursor(0, 1);
  lcd.print(L2);

  // if ((millis() > circ + 90) && Serial.available() > 0) {
  if (Serial.available() > 0) {
    // circ = millis();
    for (int i = 0; i < DATASETS; i++) {
      int goD = senD[i];
      Serial.write(goD);
    }
    Serial.read();
  }
  delay(10);
}
