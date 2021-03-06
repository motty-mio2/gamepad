#include <mio2_RoEn.h>
//#include <MR_QMC5883>
#include <Wire.h>

#define DATASETS 6

RoEn rswitch;
int dataRE;
int pdataRE;
//MR_QMC5883 compass;

const int xjoy = 14;
const int yjoy = 15;
const int tjoy = 25;
const int lbt = 26;
const int re1 = 16;
const int re2 = 17;
const int rbs = 0;

const int regdev[4] = {50,900,1800,2500}; //100-1500-2000-3000

void setup(){
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

int datas[DATASETS] = {0}; //lbt,xjoy,yjoy,joyt,re,rbs

void loop() {
  datas[0] = digitalRead(lbt);// + 1;
  datas[1] = analogRead(xjoy) ;//* datas[0];
  datas[2] = analogRead(yjoy) ;//* datas[0];
  datas[3] = digitalRead(tjoy);
  datas[4] = rswitch.EGet();
  datas[5] = analogRead(rbs);

  for (int i = 0; i < 6; i++) {
    Serial.print(datas[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(500);
}
