/*デイジーチェン接続 
Arduino11番ピン（MOSI）- 6番ピン(SDI) L6470(一台目) 3番ピン(SDO) - (SDI)L6470(二台目)(SDO) - 12番ピン（MISO) Arduino
SCK 共通
SS - CS共通
*/
#include <SPI.h>
#include <MsTimer2.h>
#include <stdio.h>

/*
// ピン定義。
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_BUSY 9
#define PIN_BUSY2 8
*/

#define PIN_SPI_MOSI 51
#define PIN_SPI_MISO 50
#define PIN_SPI_SCK 52
#define PIN_SPI_SS 53
#define PIN_BUSY 49
#define PIN_BUSY2 48
#define PIN_BUSY3 47
#define PIN_BUSY4 46

// COMMAND
String COMMAND_COLOR = "COLOR";//実装済み

// Parameter
String PARAMETER_N = "N";
String PARAMETER_S = "S";
String PARAMETER_F = "F";
String PARAMETER_B = "B";
String PARAMETER_C = "C";
String PARAMETER_M = "M";
String PARAMETER_Y = "Y";

String inString = "";
char inChar;
int IndexOfPARAMETER;

int NumberOfColor ;
int NumberOfPump ;
int Color_worktime ;
int Color_worktime_c ;
int Color_worktime_m ;
int Color_worktime_y ;
int Color_worktime_k ;
int Pump_worktime;
int Pallet_angle;
int i;

String MotorDirection;


void setup()
{

  while (!Serial) {
    ; // シリアルポート接続待ち. Needed for native USB
  }
  Serial.begin(9600);

  delay(1000);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT_PULLUP);
  pinMode(PIN_BUSY2, INPUT_PULLUP);
  pinMode(PIN_BUSY3, INPUT_PULLUP);
  pinMode(PIN_BUSY4, INPUT_PULLUP);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  digitalWrite(PIN_SPI_SS, HIGH);
  
     L6470_resetdevice(); //1台目のL6470リセット
     L6470_resetdevice2(); //2台目のL6470リセット
     L6470_resetdevice3(); //3台目のL6470リセット
     L6470_resetdevice4();
     L6470_setup();  //1台目のL6470を設定 
     L6470_setup2();  //2台目のL6470を設定 
     L6470_setup3();  //3台目のL6470を設定 
     L6470_setup4();
     L6470_getstatus(); //1台目のフラグ解放
     L6470_getstatus2();//2台目のフラグ解放
     L6470_getstatus3();//3台目のフラグ解放
     L6470_getstatus4();


 MsTimer2::set(25, fulash);//シリアルモニター用のタイマー割り込み
 MsTimer2::start();
  
delay(2000);
  
/*
//1台目正転
L6470_move(0,100);//1台目を正転方向に800ステップ　(現在1/4マイクロステップ設定なので、フルステップの200ステップ分になる)
L6470_softstop();//1台目回転停止
L6470_busydelay(1000);//1台目の動作終了から１秒待つ

//２台目正転
L6470_move2(0,300);//2台目を正転方向に800ステップ　()
L6470_softstop2();//2台目回転停止
L6470_busydelay2(1000);//2台目の動作終了から１秒待つ

//３台目正転
L6470_move3(0,600);//3台目を正転方向に800ステップ　()
L6470_softstop3();//3台目回転停止
L6470_busydelay3(1000);//3台目の動作終了から１秒待つ
*/

/*
//同時正転
for(int i=0;i<3;i++){
L6470_move(1,800);
L6470_move2(1,800);
L6470_busydelay(300);
}
delay(2000);

//同時逆転
for(int i=0;i<3;i++){
L6470_move(0,800);
L6470_move2(0,800);
L6470_busydelay(300);
}
delay(3000);

//同時　順次　正逆転
L6470_move(1,800);
L6470_move2(1,800);
L6470_move(0,800);
L6470_move2(0,800);
L6470_move(1,800);
L6470_move2(1,800);
delay(3000);

//交互に順次動作
for(int i=0;i<4;i++){
L6470_move(0,200);
L6470_busydelay(0);
L6470_move2(0,200);
L6470_busydelay2(0);
}
delay(3000);

//１テンポ遅れて順次動作
L6470_move(0,200);
L6470_busydelay(0);
for(int i=0;i<3;i++){
L6470_move2(0,200);
L6470_move(0,200);
}
L6470_move2(0,200);
L6470_busydelay2(0);
delay(3000);

//連続回転
L6470_run(1,0x1234);//69step/sの速度で正転
delay(5000);
L6470_run2(1,0x5678);//332step/sの速度で正転
delay(6000);

//回転停止
 L6470_softstop();//1台目回転停止
 L6470_softstop2();//2台目回転停止
delay(5000);

//指定座標に移動
 L6470_goto(0x4321);//座標0x004321に最短でいける回転方向で移動[B]
 L6470_goto2(0x8765);//座標0x008765に最短でいける回転方向で移動[B]
 L6470_busydelay(0);//　　　　　　↓
 L6470_busydelay2(3000);//２台とも動作が完了してから３秒待つ
 
 //原点座標に移動
 L6470_gohome();//座標原点0x000000に移動[B]
 L6470_gohome2();
 
 //原点につき次第　消磁
 L6470_hardhiz();
 L6470_hardhiz2();
*/

}

void loop(){
  while (Serial.available() > 0) { //シリアルバッファーを確認
      inString = ""; //初期化
      inString = Serial.readStringUntil(10); //改行まで文字列を読み込み
      Serial.println(inString);
      //コマンド分岐 COLOR
      if (inString.startsWith(COMMAND_COLOR) ) { //inStringがCOLORで始まるのを確認
        Serial.print("COLOR ");
        //COLOR C1234 M1234 Y1234 F 
        //0123456789012345678901234
        IndexOfPARAMETER = inString.indexOf(PARAMETER_C, 5);//5文字目以降でCを探す
        if ( 6 == IndexOfPARAMETER ) { //9文字目にCがあれば
          Color_worktime_c = inString.substring(7, 11).toInt(); //動作時間を10to14をサブストリングに分離、INT形式にして格納
          Serial.print("C");
          Serial.print(Color_worktime_c);
          Serial.println(" ");
          Color_worktime_m = inString.substring(13, 17).toInt(); //動作時間を10to14をサブストリングに分離、INT形式にして格納
          Serial.print("M");
          Serial.print(Color_worktime_m);
          Serial.println(" ");
          Color_worktime_y = inString.substring(19, 23).toInt(); //動作時間を10to14をサブストリングに分離、INT形式にして格納
          Serial.print("Y");
          Serial.print(Color_worktime_y);
          Serial.println(" ");
          Color_worktime_k = inString.substring(25, 29).toInt(); //動作時間を10to14をサブストリングに分離、INT形式にして格納
          Serial.print("K");
          Serial.print(Color_worktime_k);
          Serial.println(" ");        
          //実行
          MotorDirection = inString.substring(30);
          Serial.print(MotorDirection);
          Serial.println(" "); 
          Serial.println(PARAMETER_F);
          //if ( PARAMETER_M == MotorDirection ) {
            // L6470_move(0,Color_worktime);  //正転方向にColor_worktimeステップする
            L6470_move(0,Color_worktime_c);
            L6470_move2(0,Color_worktime_m);
            L6470_move3(0,Color_worktime_y);
            L6470_move4(0,Color_worktime_k);
            Serial.print("Go forward.");
          /*
          } else if  ( PARAMETER_B == MotorDirection ) {
            // L6470_move(1,Color_worktime);  //逆転方向にColor_worktimeステップする
            L6470_move(1,Color_worktime_c);
            L6470_move2(1,Color_worktime_m);
            L6470_move3(1,Color_worktime_y);
            Serial.print("Go backword.");
          } else {
            Serial.print("Wrong derection command.");
          }
          */
        inString = ""; //初期化
        
        }
      }
  }

  
}

void L6470_setup(){
L6470_setparam_acc(0x30); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_dec(0x30); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_maxspeed(0x2a); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed(0x1200); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold(0x28); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun(0x28); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc(0x28); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec(0x28); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

L6470_setparam_stepmood(0x02); //ステップモードdefault 0x07 (1+3+1+3bit)
}

void L6470_setup2(){
L6470_setparam_acc2(0x30); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_dec2(0x30); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_maxspeed2(0x2a); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed2(0x1200); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd2(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold2(0x28); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun2(0x28); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc2(0x28); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec2(0x28); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

L6470_setparam_stepmood2(0x02); //ステップモードdefault 0x07 (1+3+1+3bit)
}

void L6470_setup3(){
L6470_setparam_acc3(0x30); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_dec3(0x30); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_maxspeed3(0x2a); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed3(0x1200); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd3(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold3(0x28); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun3(0x28); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc3(0x28); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec3(0x28); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

L6470_setparam_stepmood3(0x02); //ステップモードdefault 0x07 (1+3+1+3bit)
}

void L6470_setup4(){
L6470_setparam_acc4(0x30); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_dec4(0x30); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_maxspeed4(0x2a); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed4(0x1200); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd4(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold4(0x28); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun4(0x28); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc4(0x28); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec4(0x28); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

L6470_setparam_stepmood4(0x02); //ステップモードdefault 0x07 (1+3+1+3bit)
}



void fulash(){
  

long a=L6470_getparam_abspos();
long b=L6470_getparam_speed();
long c=L6470_getparam_abspos2();
long d=L6470_getparam_speed2();
char str[15];
snprintf(str,sizeof(str),"1pos=0x%6.6X ",a);
Serial.print(str);
snprintf(str,sizeof(str),"1spd=0x%5.5X ",b);
Serial.print(str);
snprintf(str,sizeof(str),"2pos=0x%6.6X ",c);
Serial.print(str);
snprintf(str,sizeof(str),"2spd=0x%5.5X ",d);
Serial.println(str);
  
 /* Serial.print("0x");
  Serial.print( L6470_getparam_abspos(),HEX);
  Serial.print(" 0x");
  Serial.print( L6470_getparam_speed(),HEX);
  Serial.print(" 0x");
  Serial.print( L6470_getparam_abspos2(),HEX);
  Serial.print(" 0x");
  Serial.println( L6470_getparam_speed2(),HEX);
  */
}
