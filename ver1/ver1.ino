#include <mio2_RoEn.h>
#include <MR_QMC5883>
#include <Wire.h>

#define DATASETS 6;

MR_QMC5883 compass;

const int xjoy = ;
const int yjoy = ;
const int tjoy = ;
const int lbt = ;
const int re1 = ;
const int re2 = ;
const int rbs = ;

const int regdev[2] = {234,456};

void setup(){
  Serial.begin(9600);
  
  //LeftSetting
  pinMode(joyt, INPUT_PULLUP);
  pinMode(xjoy, INPUT); //X
  pinMode(yjoy, INPUT); //Y
  pinMode(lbt, INPUT_PULLUP);
  
  //RightSetting
  rswitch.ESet(re1, re2);
  pinMode(rbs, INPUT);

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
}

int datas(DATASETS] = {0} //lbt,xjoy,yjoy,joyt,re,rbs
int priRE = 0;

void loop() {
  datas{0} = digitalRead(lbt) + 1;
  datas{1} = analogRead(xjoy) * datas{0};
  datas{2} = analogRead(yjoy) * datas{0};
  datas{3} = digitalRead(tjoy);
  datas{4} = rswitch.EGet();
  datas{5} = analogRead(rbs);

  if (datas{0} == 2) {
    Serial.print("◯");
  } else {
    Serial.print("×");
  }
  Serial.print(",");
  
  if (datas{1} >= 3000) {
    Serial.print("→");
  } else if (datas{1} <= 1000) {
    Serial.print("←");
  } else {
    Serial,print("n");
  }
  Serial.print(",");

  if (datas{2} >= 3000) {
    Serial.print("↑");
  } else if (datas{2} <= 1000) {
    Serial.print("↓");
  } else {
    Serial,print("n");
  }
  Serial.print(",");
  
  if (datas{3} == 1) {
    Serial.print("◯");
  } else {
    Serial.print("×");
  }
  Serial.print(",");
  
  if (priRE != datas{4}) {
    Serial.print(datas{4});
  }
  priRE = datas{4}
  Serial.print(",");
  
  if (100 < datas{6} && datas{6} < regdev{1}) {
    Serial.print("1");
  } else if (regdev{1} < datas{6} && datas{6} < regdev{2}) {
    Serial.print("2");
  } else if (regdev{2} < datas{6} && datas{6} < 4000) {
    Serial.print("3");
  } else {
    Serial.println("0");
  }
  
  Serial.println();
  
  delay(100);
}
