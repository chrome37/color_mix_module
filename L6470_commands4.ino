/*L6470 2台目コントロール　コマンド
 引数-----------------------
 dia   1:正転 0:逆転,
 spd  (20bit)(0.015*spd[step/s])
 pos  (22bit)
 n_step (22bit)
 act   1:絶対座標をマーク  0:絶対座標リセット
 mssec ミリ秒
 val 各レジスタに書き込む値
 ---------------------------
 L6470_run4(dia,spd);//指定方向に連続回転 [n]
 L6470_stepclock4(dia);//指定方向にstepピンのクロックで回転[n]
 L6470_move4(dia,n_step);//指定方向に指定数ステップする[B]
 L6470_goto4(pos);//指定座標に最短でいける回転方向で移動[B]
 L6470_gotodia4(dia,pos);//回転方向を指定して指定座標に移動[B]
 L6470_gountil4(act,dia,spd);//指定した回転方向に指定した速度で回転し、スイッチのONで急停止と座標処理[B]
 L6470_relesesw4(act,dia);//スイッチがOFFに戻るまで最低速度で回転し、停止と座標処理[B]
 L6470_gohome4();//座標原点に移動[B]
 L6470_gomark4();//マーク座標に移動[B]
 L6470_resetpos4();//絶対座標リセット[n]
 L6470_resetdevice4();//L6470リセット[n]
 L6470_softstop4();//回転停止、保持トルクあり[B]
 L6470_hardstop4();//回転急停止、保持トルクあり[n]
 L6470_softhiz4();//回転停止、保持トルクなし[B]
 L6470_hardhiz4();//回転急停止、保持トルクなし[n]
 L6470_getstatus4();//statusレジスタの値を返す[n]（L6470_getparam_status();と同じ）

 L6470_busydelay4(msec);　//busyフラグがHIGHになってから、指定ミリ秒待つ。

 [n]:busy信号なし、もしくは瞬間的。　
 [B]:busy信号あり。(オープンドレインのトランジスタがONになること)

 レジスタ書き込みコマンド
 L6470_setparam_abspos4(val); //[R, WS]現在座標default 0x000000 (22bit)
 L6470_setparam_elpos4(val); //[R, WS]コイル励磁の電気的位置default 0x000 (2+7bit)
 L6470_setparam_mark4(val); //[R, WR]マーク座標default 0x000000 (22bit)
 //ありませんL6470_spped3 //[R] 現在速度read onry  (20bit)
 L6470_setparam_acc4(val); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
 L6470_setparam_dec4(val); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
 L6470_setparam_maxspeed4(val); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
 L6470_setparam_minspeed4(val); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
 L6470_setparam_fsspd4(val); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
 L6470_setparam_kvalhold4(val); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
 L6470_setparam_kvalrun4(val); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
 L6470_setparam_kvalacc4(val); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
 L6470_setparam_kvaldec4(val); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
 L6470_setparam_intspd4(val); //[R, WH]逆起電力補償切替点速度default 0x0408 (14bit) (0.238*val[step/s])
 L6470_setparam_stslp4(val); //[R, WH]逆起電力補償低速時勾配default 0x19 (8bit) (0.000015*val[% s/step])
 L6470_setparam_fnslpacc4(val); //[R, WH]逆起電力補償高速時加速勾配default 0x29 (8bit) (0.000015*val[% s/step])
 L6470_setparam_fnslpdec4(val); //[R, WH]逆起電力補償高速時減速勾配default 0x29 (8bit) (0.000015*val[% s/step])
 L6470_setparam_ktherm4(val); //[R, WR]不明default 0x0 (4bit) (0.03125*val+1)
 //ありませんL6470_adcout3 //[R] read onry (5bit) ADCによる逆起電力補償の大きさかな？
 L6470_setparam_ocdth4(val); //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
 L6470_setparam_stallth4(val); //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
 L6470_setparam_stepmood4(val); //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
 L6470_setparam_alareen4(val); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
 L6470_setparam_config4(val); //[R, WH]各種設定default 0x2e88 (3+3+2+1+1+1+1+1+3bit)
 //L6470_status //[R]状態read onry (16bit)

 [R]:読み取り専用
 [WR]:いつでも書き換え可
 [WH]:書き込みは出力がハイインピーダンスの時のみ可
 [WS]:書き換えはモータが停止している時のみ可


 レジスタ読み込みコマンド(返り値　long型)
 L6470_getparam_abspos4();
 L6470_getparam_elpos4();
 L6470_getparam_mark4();
 L6470_getparam_speed4();
 L6470_getparam_acc4();
 L6470_getparam_dec4();
 L6470_getparam_maxspeed4();
 L6470_getparam_minspeed4();
 L6470_getparam_fsspd4();
 L6470_getparam_kvalhold4();
 L6470_getparam_kvalrun4();
 L6470_getparam_kvalacc4();
 L6470_getparam_kvaldec4();
 L6470_getparam_intspd4();
 L6470_getparam_stslp4();
 L6470_getparam_fnslpacc4();
 L6470_getparam_fnslpdec4();
 L6470_getparam_ktherm4();
 L6470_getparam_adcout4();
 L6470_getparam_ocdth4();
 L6470_getparam_stallth4();
 L6470_getparam_stepmood4();
 L6470_getparam_alareen4();
 L6470_getparam_config4();
 L6470_getparam_status4();
 */

//layer4--------------------------------------------------------
//3台目用
void L6470_setparam_abspos4(long val){L6470_transfer4(0x01,3,val);}
void L6470_setparam_elpos4(long val){L6470_transfer4(0x02,2,val);}
void L6470_setparam_mark4(long val){L6470_transfer4(0x03,3,val);}
void L6470_setparam_acc4(long val){L6470_transfer4(0x05,2,val);}
void L6470_setparam_dec4(long val){L6470_transfer4(0x06,2,val);}
void L6470_setparam_maxspeed4(long val){L6470_transfer4(0x07,2,val);}
void L6470_setparam_minspeed4(long val){L6470_transfer4(0x08,2,val);}
void L6470_setparam_fsspd4(long val){L6470_transfer4(0x15,2,val);}
void L6470_setparam_kvalhold4(long val){L6470_transfer4(0x09,1,val);}
void L6470_setparam_kvalrun4(long val){L6470_transfer4(0x0a,1,val);}
void L6470_setparam_kvalacc4(long val){L6470_transfer4(0x0b,1,val);}
void L6470_setparam_kvaldec4(long val){L6470_transfer4(0x0c,1,val);}
void L6470_setparam_intspd4(long val){L6470_transfer4(0x0d,2,val);}
void L6470_setparam_stslp4(long val){L6470_transfer4(0x0e,1,val);}
void L6470_setparam_fnslpacc4(long val){L6470_transfer4(0x0f,1,val);}
void L6470_setparam_fnslpdec4(long val){L6470_transfer4(0x10,1,val);}
void L6470_setparam_ktherm4(long val){L6470_transfer4(0x11,1,val);}
void L6470_setparam_ocdth4(long val){L6470_transfer4(0x13,1,val);}
void L6470_setparam_stallth4(long val){L6470_transfer4(0x14,1,val);}
void L6470_setparam_stepmood4(long val){L6470_transfer4(0x16,1,val);}
void L6470_setparam_alareen4(long val){L6470_transfer4(0x17,1,val);}
void L6470_setparam_config4(long val){L6470_transfer4(0x18,2,val);}


//２台目用
long L6470_getparam_abspos4(){return L6470_getparam4(0x01,3);}
long L6470_getparam_elpos4(){return L6470_getparam4(0x02,2);}
long L6470_getparam_mark4(){return L6470_getparam4(0x03,3);}
long L6470_getparam_speed4(){return L6470_getparam4(0x04,3);}
long L6470_getparam_acc4(){return L6470_getparam4(0x05,2);}
long L6470_getparam_dec4(){return L6470_getparam4(0x06,2);}
long L6470_getparam_maxspeed4(){return L6470_getparam4(0x07,2);}
long L6470_getparam_minspeed4(){return L6470_getparam4(0x08,2);}
long L6470_getparam_fsspd4(){return L6470_getparam4(0x15,2);}
long L6470_getparam_kvalhold4(){return L6470_getparam4(0x09,1);}
long L6470_getparam_kvalrun4(){return L6470_getparam4(0x0a,1);}
long L6470_getparam_kvalacc4(){return L6470_getparam4(0x0b,1);}
long L6470_getparam_kvaldec4(){return L6470_getparam4(0x0c,1);}
long L6470_getparam_intspd4(){return L6470_getparam4(0x0d,2);}
long L6470_getparam_stslp4(){return L6470_getparam4(0x0e,1);}
long L6470_getparam_fnslpacc4(){return L6470_getparam4(0x0f,1);}
long L6470_getparam_fnslpdec4(){return L6470_getparam4(0x10,1);}
long L6470_getparam_ktherm4(){return L6470_getparam4(0x11,1);}
long L6470_getparam_adcout4(){return L6470_getparam4(0x12,1);}
long L6470_getparam_ocdth4(){return L6470_getparam4(0x13,1);}
long L6470_getparam_stallth4(){return L6470_getparam4(0x14,1);}
long L6470_getparam_stepmood4(){return L6470_getparam4(0x16,1);}
long L6470_getparam_alareen4(){return L6470_getparam4(0x17,1);}
long L6470_getparam_config4(){return L6470_getparam4(0x18,2);}
long L6470_getparam_status4(){return L6470_getparam4(0x19,2);}


//layer2--------------------------------------------------------
//3台目用
void L6470_run4(int dia,long spd){
  if(dia==1)
    L6470_transfer4(0x51,3,spd);
  else
    L6470_transfer4(0x50,3,spd);
}
void L6470_stepclock4(int dia){
  if(dia==1)
    L6470_transfer4(0x59,0,0);
  else
    L6470_transfer4(0x58,0,0);
}
void L6470_move4(int dia,long n_step){
  if(dia==1)
    L6470_transfer4(0x41,3,n_step);
  else
    L6470_transfer4(0x40,3,n_step);
}
void L6470_goto4(long pos){
  L6470_transfer4(0x60,3,pos);
}
void L6470_gotodia4(int dia,int pos){
  if(dia==1)
    L6470_transfer4(0x69,3,pos);
  else
    L6470_transfer4(0x68,3,pos);
}
void L6470_gountil4(int act,int dia,long spd){
  if(act==1)
    if(dia==1)
      L6470_transfer4(0x8b,3,spd);
    else
      L6470_transfer4(0x8a,3,spd);
  else
    if(dia==1)
      L6470_transfer4(0x83,3,spd);
    else
      L6470_transfer4(0x82,3,spd);
}
void L6470_relesesw4(int act,int dia){
  if(act==1)
    if(dia==1)
      L6470_transfer4(0x9b,0,0);
    else
      L6470_transfer4(0x9a,0,0);
  else
    if(dia==1)
      L6470_transfer4(0x93,0,0);
    else
      L6470_transfer4(0x92,0,0);
}
void L6470_gohome4(){
  L6470_transfer4(0x70,0,0);
}
void L6470_gomark4(){
  L6470_transfer4(0x78,0,0);
}
void L6470_resetpos4(){
  L6470_transfer4(0xd8,0,0);
}
void L6470_resetdevice4(){
  L6470_send4(0x00);//nop命令
  L6470_send4(0x00);
  L6470_send4(0x00);
  L6470_send4(0x00);
  L6470_send4(0xc0);
}
void L6470_softstop4(){
  L6470_transfer4(0xb0,0,0);
}
void L6470_hardstop4(){
  L6470_transfer4(0xb8,0,0);
}
void L6470_softhiz4(){
  L6470_transfer4(0xa0,0,0);
}
void L6470_hardhiz4(){
  L6470_transfer4(0xa8,0,0);
}

long L6470_getstatus4(){
  long val=0;
  L6470_send4(0xd0);
  for(int i=0;i<=1;i++){
    val = val << 8;
    digitalWrite(PIN_SPI_SS, LOW); // ~SSイネーブル。
    val = val | SPI.transfer(0x00); // アドレスもしくはデータ送信。
    SPI.transfer(0x00); // アドレスもしくはデータ送信。
    digitalWrite(PIN_SPI_SS, HIGH); // ~SSディスエーブル
  }
  return val;
}

//-----
void L6470_transfer4(int add,int bytes,long val){//2台目に送信
  int data[3];
  //while(!busy_flag4()){} //BESYが解除されるまで待機
  while(!digitalRead(PIN_BUSY3)){}//BESYピン出力が解除されるまで待機
  L6470_send4(add);
  for(int i=0;i<=bytes-1;i++){
    data[i] = val & 0xff;
    val = val >> 8;
  }
  if(bytes==3){
    L6470_send4(data[2]);
  }
  if(bytes>=2){
    L6470_send4(data[1]);
  }
  if(bytes>=1){
    L6470_send4(data[0]);
  }
}


void L6470_send4(unsigned char add_or_val){//2台目に送信
  digitalWrite(PIN_SPI_SS, LOW); // ~SSイネーブル。
  SPI.transfer(0); // 0送信。
  SPI.transfer(add_or_val); // アドレスもしくはデータ送信。
  SPI.transfer(0); // 0送信。
  SPI.transfer(0); // 0送信。
  SPI.transfer(0); // 0送信。
  digitalWrite(PIN_SPI_SS, HIGH); // ~SSディスエーブル。
}

void L6470_busydelay4(long time){
//while(!busy_flag4()){}
  while(!digitalRead(PIN_BUSY3)){}//BESYピン出力が解除されるまで待機
  delay(time);
}

long L6470_getparam4(int add,int bytes){//2台目に送信
  long val=0;
  int send_add = add | 0x20;
  L6470_send4(send_add);
  for(int i=0;i<=bytes-1;i++){
    val = val << 8;
    digitalWrite(PIN_SPI_SS, LOW); // ~SSイネーブル。
    SPI.transfer(0x00); // アドレスもしくはデータ送信。
    val = val | SPI.transfer(0x00); // アドレスもしくはデータ送信。
    SPI.transfer(0x00); // アドレスもしくはデータ送信。
    SPI.transfer(0x00); // アドレスもしくはデータ送信。
    SPI.transfer(0x00); // アドレスもしくはデータ送信。
    digitalWrite(PIN_SPI_SS, HIGH); // ~SSディスエーブル
  }
  return val;
}

int busy_flag4(){
int sta=L6470_getparam_status4();
sta = sta >> 1;
sta = sta & 0x0001;
return sta;
}
