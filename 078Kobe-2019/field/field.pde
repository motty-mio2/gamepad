import processing.serial.*;

Serial myPort;

int[] data = new int[6];

int flamer = 300; //的の表示フレーム数

float x; //的の左上のx座標
float y; //的の左上のy座標

int delta = 5; //カーソルの移動量

int pt = 0; //得点
int maxpt = 0;
int cnt; //得点表示の応答速度を早くする為のカウンタ

int timer = 0; //制限時間計測用変数

//カーソルの色設定
int rco = 255;
int gco = 0;
int bco = 0;

//カーソルの初期座標
float circle_X = 320;
float circle_Y = 320;
int diam = 0; //直径の係数

void setup() {
  for(int i = 0; i < 6; i++){
    data[i] = 0;
  }
  textSize(24);
  size(640, 640);
  background(255);
  frameRate(60);
  myPort = new Serial(this, "COM6", 9600);
  myPort.write(65);
}

void draw() {
  timer++;
  if(timer >= 3600){
    background(90);
      text("finish", width/2, height/2);
      text("Your Score is "+pt, width/2, height/2+30);
      if(pt>maxpt) {
        maxpt = pt;
      }
    if(data[0] == 1){
      timer = 0;
      pt = 0;
    }

  } else {
    //背景設定
  background(255);
  strokeWeight(1);
  stroke(200);
  line(0, height/2, width, height/2);
  line(width/2, 0, width/2, height);


  //カーソル移動&カーソル設定
  if (data[5] == 2) {
    delta = 2;
  } else {
    delta = 5;
  }

  if (data[3] == 2) {
    circle_X += delta;
  } else if (data[3] == 1) {
    circle_X -= delta;
  }
  if (circle_X > width){
    circle_X -= 640;
  } else if (0>circle_X){
    circle_X += 640;
  }

  if (data[2] == 1) {
    circle_Y += delta;
  } else if (data[2] == 2) {
    circle_Y-= delta;
  }
  if (circle_Y > width){
    circle_Y -= 640;
  } else if (0>circle_Y){
    circle_Y += 640;
  }



  if (data[5] == 3) {
    rco = int(random(0, 256));
    gco = int(random(0, 256));
    bco = int(random(0, 256));
  }


  //クリック判定
  if (data[5] == 1) {
    if ((y-5*(diam+1)/2 <= circle_Y && circle_Y <= y+50)
    && (x-5*(diam+1) <= circle_X && circle_X <= x+50+5*(diam+1)/2)) {
      pt+= 10-diam; //当たったので得点増加
      cnt = flamer - 1;
    }
  }

  //的の描画
  if (++cnt >= flamer) { //180回に一回四角の場所を変える
    background(204);
    x=random(0, height - 50);
    y=random(0, width - 50);
    cnt = 0; //更新したのでカウンタクリア
  }

  //文字表示
  background(204);
  fill(255, 255, 255);
  rect(x, y, 50, 50);
  fill(0, 0, 0);
  text("now "+ timer/60 +" / 60",480,560);
  text(pt+" Point", 480, 590);
  text("highest "+maxpt, 480, 620);


  noFill();
  strokeWeight(5);
  stroke(rco, gco, bco);
  ellipse(circle_X, circle_Y, 5*(diam+1), 5*(diam+1));
  }
  diam = data[4];
}

void serialEvent(Serial myPort) {
  if (myPort.available() > 5) {
    data[0] = myPort.read(); //esc
    println(data[0]);
    data[1] = myPort.read(); //tbt
    println(data[1]);
    data[2] = myPort.read(); //x
    println(data[2]);
    data[3] = myPort.read(); //y
    println(data[3]);
    data[4] = myPort.read(); //RE
    println(data[4]);
    data[5] = myPort.read(); //rbt
    println(data[5]);
    println();
    myPort.write(65);
    //println();
  }
}
