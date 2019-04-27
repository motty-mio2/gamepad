import processing.serial.*;

Serial myPort;

string data; //受信データ

int flamer = 300; //的の表示フレーム数

float x; //的の左上のx座標
float y; //的の左上のy座標

int delta = 5; //カーソルの移動量

int pt = 0; //得点
int cnt; //得点表示の応答速度を早くする為のカウンタ

int timer = 0; //制限時間計測用変数

//カーソルの色設定
int rco = 255;
int gco = 0;
int bco = 0;

//カーソルの初期座標
float circle_X = 320;
float circle_Y = 320;
int diam; //直径の係数

void setup() {
  textSize(24);
  size(640, 640);
  background(255);
  frameRate(60);
  myPort = new Serial(this, "COM14", 9600);
  myPort.write(65);
}

void draw() {
  //プログラムの状態指定
  if(timer > 3600);
    background(96);
    text("finish!!",width/2, height/2);
    text("your score is " + pt,width/2, height/2+30);
    text("if you wanna play again, click L1 button",width/2, height/2+60);
    if(data[0]=="0"){
      timer = 0
    }
  else {
    timer += 1;
  }
 
  
  //背景設定
  background(255);
  strokeWeight(1);
  stroke(200);
  line(0, height/2, width, height/2);
  line(width/2, 0, width/2, height);


  //カーソル移動&カーソル設定
  if (data[5] == "2"){
    delta = 2;
  } else {
    delta = 5;
  }

  if (data[1] == "1"){
    circle_X += delta;
  } else if (data[1] == "2"){
    circle_X -= delta;
  }
  
  if (data[2] == "2"){
    circle_Y += delta;
  } else if (data[2] == "1"){
    circle_Y -= delta;
  }

  noFill();
  strokeWeight(5);
  stroke(rco, gco, bco);
  diam = data[4].toInt();
  ellipse(circle_X, circle_Y, 5*(diam+1), 5*(diam+1));
  
  if(data[5] == "3"){
    rco = int(random(0, 256));
    gco = int(random(0, 256));
    bco = int(random(0, 256));
  }


  //クリック判定
  if (data[5] == "1") {
    if ((y-5*(diam+1) <= circle_Y and circle_Y <= y+50+5*(diam+1))
     && (x-5*(diam+1) <= circle_X and circle_X <= x+50+5*(diam+1)){
      pt+= 10-diam; //当たったので得点増加
      click = 1;
      cnt = flamer - 1;
    }
  }


  //的の描画
  if (++cnt >= flamer) { //180回に一回四角の場所を変える
    background(204);
    x=random(0, height - 50);
    y=random(0, width - 50);
    click = 0; //この座標でのクリック履歴クリア
    cnt = 0; //更新したのでカウンタクリア
  }


  //文字表示
  background(204);
  fill(255, 255, 255);
  rect(x, y, 50, 50);
  fill(0, 0, 0);
  text(pt+" Point", 520, 620);
}

void serialEvent(Serial myPort) {
  if (myPort.available()>1) {
    data = myPort.read();
    Serial.write("0");
  }
}
