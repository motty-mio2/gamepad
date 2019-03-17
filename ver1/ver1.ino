#include <mio2_RoEn.h>
//#include <MR_QMC5883>
#include <Wire.h>

#define DATASETS 6
int datas[DATASETS] = {0}; //lbt,xjoy,yjoy,joyt,re,rbs
int delta = 1;
unsigned long circ;

RoEn rswitch;
int pdataRE;

//MR_QMC5883 compass;

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
  rswitch.ESet(re1, re2);
  pinMode(rbs, INPUT);
  pinMode(2, OUTPUT);

  /*
  //QMC5883L
  while (!compass.begin()) {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }

  Serial.println("Initialize QMC5883");
  compass.setRange(QMC5883_RANGE_2GA);
  compass.setMeasurementMode(QMC5883_CONTINOUS);
  compass.setDataRate(QMC5883_DATARATE_50HZ);
  compass.setSamples(QMC5883_SAMPLES_8);

  //MPU6050
  while () {

  }
  */
}

void loop() {
  
  datas[0] = digitalRead(lbt);// + 1;
  datas[1] = analogRead(xjoy);// * datas[0];
  datas[2] = analogRead(yjoy);// * datas[0];
  datas[3] = digitalRead(tjoy);
  datas[4] = rswitch.EGet();
  datas[5] = analogRead(rbs);

  if (millis() > circ + 490) {
    circ = millis();
    if (datas[0] == 0) {
      Serial.print("◯");
      delta = 20;
    } else {
      Serial.print("×");
      delta = 1;
    }
    Serial.print(",");
  
    if (datas[1] * delta >= joydev[1]) {
      Serial.print("W");
    } else if (datas[1] * delta <= joydev[0]) {
      Serial.print("S");
    } else {
      Serial.print("n");
    }
    Serial.print(",");
    
    if (datas[2] * delta >= joydev[1]) {
      Serial.print("A");
    } else if (datas[2] * delta <= joydev[0]) {
      Serial.print("D");
    } else {
      Serial.print("n");
    }
    Serial.print(",");
  
    if (datas[3] == 0) {
      Serial.print("◯");
    } else {
      Serial.print("×");
    }
    Serial.print(",");
  
    //if (pdataRE != datas[4]) {
      Serial.print(datas[4]);
    //}
    //pdataRE = datas[4];
    Serial.print(",");
  
    if (datas[5] < regdev[0]) {
      Serial.print("1");
    } else if (regdev[0] < datas[5] && datas[5] < regdev[1]) {
      Serial.print("2");
    } else if (regdev[1] < datas[5] && datas[5] < regdev[2]) {
      Serial.print("3");
    } else {
      Serial.print("0");
    }
    Serial.println();
    }
}
