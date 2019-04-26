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

const int joydev[2] = {1000,3000}; //
const int regdev[3] = {900,1800,2500}; //200-1500-2000-3000

void setup(){
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
    datas[0] = digitalRead(lbt);// + 1;
    datas[1] = analogRead(xjoy);// * datas[0];
    datas[2] = analogRead(yjoy);// * datas[0];
    datas[3] = digitalRead(tjoy);
    datas[4] = rswitch.EGet();
    datas[5] = analogRead(rbs);

    String L1, L2;
//    if (millis() > circ + 490) {
//        circ = millis();
        if (datas[3] == 0) {
            L1 = "O";
        } else {
            L1 = "X";
        }

        if (datas[0] == 0) {
            L2 = "O";
            if (datas[2] >= 4000) {
                L2.concat("A   ");
        } else if (datas[2] <= 3800) {
            L2.concat(" D  ");
        } else {
            L2.concat("    ");
        }
        } else {
            L2 = "X";

        if (datas[2] >= joydev[1]) {
            L2.concat("A   ");
        } else if (datas[2] <= joydev[0]) {
            L2.concat(" D  ");
        } else {
            L2.concat("    ");
        }
        }

        L1.concat(" ");
        L2.concat(" ");

        if (datas[1] >= joydev[1]) {
            L1.concat("W   ");
        } else if (datas[1] <= joydev[0]) {
            L1.concat(" S  ");
        } else {
            L1.concat("    ");
        }


        L1.concat(datas[4]);
        /*if (pdataRE != datas[4]) {
            Serial.print(datas[4]);
        //}
        //pdataRE = datas[4];
        */

        if (datas[5] < regdev[0]) {
            //Serial.print("1");
            L1.concat("X");
            L2.concat("OX");
        } else if (regdev[0] < datas[5] && datas[5] < regdev[1]) {
            //Serial.print("2");
            L1.concat("X");
            L2.concat("XO");
        } else if (regdev[1] < datas[5] && datas[5] < regdev[2]) {
            //Serial.print("3");]
            L1.concat("O");
            L2.concat("XX");
        } else {
            //Serial.print("0");
            L1.concat("X");
            L2.concat("XX");
        }
//        Serial.println();

        // LCD表示(1行目)
        lcd.setCursor(0, 0);
        lcd.print(L1);

        // LCD表示(2行目)
        lcd.setCursor(0, 1);
        lcd.print(L2);
    //}
}
