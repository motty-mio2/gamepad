#include <mio2_RoEn.h>
#include <ST7032.h>
#include <Wire.h>

#define DATASETS 6
int datas[DATASETS] = {0}; //lbt,xjoy,yjoy,joyt,re,rbs

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

//const int display = ;
//const int nax = ;

const int joydev[2][2] = {{30, 250},{1000, 3000}}; // 0-80-300 //0-2200-4496
const int regdev[3] = {900, 1800, 2500}; //200-1500-2000-3000

void setup() {
  circ = millis();
  Serial.begin(9600);

  //LeftSetting
  pinMode(tjoy, INPUT_PULLUP);
  pinMode(xjoy, INPUT); //X
  pinMode(yjoy, INPUT); //Y
  pinMode(lbt, INPUT_PULLUP);

  //RightSetting
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

  String L1, L2, senD;

  if (datas[3] == 0) {
    L1 = "O";
    senD = "1";
  } else {
    L1 = "X";
    senD = "0";
  }

  if (datas[0] == 0) {
    L2 = "O";
    senD.concat("1");
  } else {
    L2 = "X";
    senD.concat("0");
  }

  if (datas[1] >= joydev[datas[0]][1]){
    L1.concat("A   ");
    senD.concat("1");
  }else if (datas[1] <= joydev[datas[0]][1]){
    L1.concat(" D  ");
    senD.concat("2");
  } else{
    L1.concat("    ");
    senD.concat("0");
  }

  if (datas[2] >= joydev[datas[0]][0]) {
    L2.concat("A   ");
    senD.concat("2");
  } else if (datas[2] <= joydev[datas[0]][1]) {
    L2.concat(" D  ");
    senD.concat("1");
  } else {
    L2.concat("    ");
    senD.concat("0");
  }

  L1.concat(datas[4]);
  senD.concat(datas[4]);
  /*if (pdataRE != datas[4]) {
          Serial.print(datas[4]);
      //}
      //pdataRE = datas[4];
  */

  if (datas[5] < regdev[0])
  {
    //Serial.print("1");
    L1.concat("X");
    L2.concat("OX");
    senD.concat("1");
  }
  else if (regdev[0] < datas[5] && datas[5] < regdev[1])
  {
    //Serial.print("2");
    L1.concat("X");
    L2.concat("XO");
    senD.concat("2");
  }
  else if (regdev[1] < datas[5] && datas[5] < regdev[2])
  {
    //Serial.print("3");]
    L1.concat("O");
    L2.concat("XX");
    senD.concat("3");
  }
  else
  {
    //Serial.print("0");
    L1.concat("X");
    L2.concat("XX");
    senD.concat("0");
  }
  //        Serial.println();

  if (millis() > circ + 490)
  {
    circ = millis();
    // LCD表示(1行目)
    lcd.setCursor(0, 0);
    lcd.print(L1);
    // LCD表示(2行目)
    lcd.setCursor(0, 1);
    lcd.print(L2);

    Serial.println(senD);
  }
}
