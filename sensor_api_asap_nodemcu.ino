#include "CTBot.h"
CTBot myBot;

String ssid = "kamukocak";     // Sesuikan dengan nama wifi anda
String pass = "1sampai10"; // sesuaikan password wifi
String token = "5897286690:AAEic4swqJTsZ0UELMtXe2Csi3y7TyOTEBs"; // token bot telegram yang telah dibuat

#define Api 12 //GPIO12 (D6)
#define Gas 14 //GPIO14 (D5)

void setup() {
  pinMode(Api, INPUT);
  pinMode(Gas, INPUT);
  Serial.begin(115200);
  myBot.wifiConnect(ssid, pass);

  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\n Terhubung");
  else
    Serial.println("\n Tidak Terhubung");
}
  
void loop() {
  int bacasensorapi = digitalRead(Api);
  int bacasensorgas = digitalRead(Gas);
  Serial.print("Api : ");
  Serial.print(bacasensorapi);
  Serial.print("   Asap : ");
  Serial.println(bacasensorgas);
  if(bacasensorgas==1) //terdeteksi asap
  {
    String kirim;
    kirim ="Warning!, Terjadi Indikasi Asap Kebakaran. Silahkan Selamatin Barang dan Evakuasi Diri Anda!";
    myBot.sendMessage(1032588009, kirim); 
    delay(1500); 
  }
  if(bacasensorapi==0) //terdeteksi api
  {
    String kirim;
    kirim ="Warning!, Terjadi Indikasi Api Kebakaran. Silahkan Selamatin Barang dan Evakuasi Diri Anda!";
    myBot.sendMessage(1032588009, kirim); 
    delay(1500); 
  }
  delay(1500);
}

