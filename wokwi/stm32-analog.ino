#include <Arduino.h>
#include <DHT.h>
#include <math.h>
#define DASH Serial1
DHT dht(PA2, DHT22);
const int threshold=750;
struct GasDecision {
  unsigned phase=0, high=0, total=0; bool alarm=false, completed=false;
  void update(bool low,bool a,bool b) {
    completed=false;
    if(low){phase=0; high=a; total=1; alarm=a; return;}
    if(!phase){if(a){phase=1; high=1; total=1;}else{alarm=false; high=total=0;}}
    else {high+=a+b; total+=2; if(phase==1) phase=2; else {alarm=high>=3; completed=true; phase=0;}}
  }
};
GasDecision gas;
bool bistPassed;
bool runBIST(){
  bool pass=(800>=750)&&!(600>=750);
  pass=pass && fabsf(fmaxf(0.5f,0.8f)-0.8f)<0.001f;
  GasDecision t; t.update(false,true,false); t.update(false,true,false); t.update(false,true,true);
  pass=pass && t.completed && t.alarm && t.total==5 && t.high==4;
  GasDecision l; l.update(true,true,false); pass=pass && l.alarm && l.phase==0 && l.total==1;
  GasDecision n; n.update(true,false,false); return pass && !n.alarm;
}
float temp=NAN,hum=NAN; bool valid=false; unsigned long lastDHT=0,lastReport=0,lastValid=0;
void setup(){
  pinMode(PA0,INPUT); pinMode(PA1,INPUT); pinMode(PA4,OUTPUT); digitalWrite(PA4,LOW);
  pinMode(PB0,INPUT); pinMode(PC13,OUTPUT); digitalWrite(PC13,HIGH);
  analogReadResolution(12); DASH.setRx(PA10); DASH.setTx(PA9); DASH.begin(115200); dht.begin();
  bistPassed=runBIST();
}
void loop(){
  unsigned long now=millis();
  if(!lastDHT || now-lastDHT>=2500){lastDHT=now; float t=dht.readTemperature(),h=dht.readHumidity(); valid=isfinite(t)&&isfinite(h)&&t>=-40&&t<=80&&h>=0&&h<=100; if(valid){temp=t; hum=h; lastValid=millis();}}
  now=millis(); if(now-lastReport<1000)return; lastReport=now;
  int battery=(analogRead(PB0)*100UL+2047)/4095; bool low=battery<=40;
  int mq1=analogRead(PA0); bool second=!low && gas.phase!=0; int mq2=second?analogRead(PA1):-1;
  gas.update(low,mq1>=threshold,second && mq2>=threshold);
  float p=(now%60000UL)/1000.0f; float dust=20+0.5f*(p<=30?p:60-p);
  bool climateOK=valid && now-lastValid<=6000;
  float ratio=fmaxf(mq1/(float)threshold,dust/150.0f);
  if(second)ratio=fmaxf(ratio,mq2/(float)threshold);
  if(climateOK)ratio=fmaxf(ratio,fmaxf(temp/45.0f,hum/80.0f));
  bool alert=!bistPassed || !climateOK || gas.alarm || dust>=150 || (climateOK && (temp>=45 || hum>=80));
  DASH.print("{\"time_ms\":"); DASH.print(now);
  DASH.print(",\"mq1_adc\":"); DASH.print(mq1);
  DASH.print(",\"mq2_adc\":"); if(second)DASH.print(mq2); else DASH.print("null");
  DASH.print(",\"temperature_c\":"); if(climateOK)DASH.print(temp,1); else DASH.print("null");
  DASH.print(",\"humidity_pct\":"); if(climateOK)DASH.print(hum,1); else DASH.print("null");
  DASH.print(",\"dust_sim_ug_m3\":"); DASH.print(dust,1);
  DASH.print(",\"ehi_demo\":"); if(climateOK)DASH.print(ratio*100,1); else DASH.print("null");
  DASH.print(",\"battery_sim_pct\":"); DASH.print(battery);
  DASH.print(",\"battery_mode\":\""); DASH.print(low?"LOW":"NORMAL"); DASH.print("\"");
  DASH.print(",\"votes_high\":"); DASH.print(gas.high); DASH.print(",\"votes_total\":"); DASH.print(gas.total);
  DASH.print(",\"bist\":\""); DASH.print(bistPassed?"PASS":"FAIL"); DASH.print("\"");
  DASH.print(",\"fault\":\""); DASH.print(climateOK?"NO":"DHT_INVALID_OR_STALE"); DASH.print("\"");
  DASH.print(",\"alert\":"); DASH.print(alert?"true":"false"); DASH.println("}");
}
