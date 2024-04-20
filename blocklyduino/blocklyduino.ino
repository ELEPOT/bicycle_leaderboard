//Generated Date: Wed, 17 Apr 2024 09:45:15 GMT

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#include <WiFiClientSecure.h>

boolean _E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E = false;
String _E5_80_9F_E7_9A_84_E5_8D_A1_E8_99_9F = "";
double _E8_B7_9D_E9_9B_A2 = 0;
int _E4_B8_8A_E4_B8_80_E6_AC_A1_E5_81_B5_E6_B8_AC_E5_88_B0_E7_9A_84_E6_99_82_E9_96_93 = 0;
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
String myNFC_UID="";
uint8_t myNFC_UID_array[] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t myNFC_UID_Length;

char _lwifi_ssid[] = "makerG103";
char _lwifi_pass[] = "G103maker";
void initWiFi() {

  for (int i=0;i<2;i++) {
    WiFi.begin(_lwifi_ssid, _lwifi_pass);

    delay(1000);
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.println(_lwifi_ssid);

    long int StartTime=millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if ((StartTime+5000) < millis()) break;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("STAIP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("");

      break;
    }
  }
}

const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

void HandleCard(String _E5_8D_A1_E8_99_9F) {
  if (_E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E) {
    if (_E5_8D_A1_E8_99_9F == _E5_80_9F_E7_9A_84_E5_8D_A1_E8_99_9F) {
      DrawText("寫入資料庫中...");
      sendToGoogleSheets("1",URLEncode((String() + _E5_8D_A1_E8_99_9F + "," + _E8_B7_9D_E9_9B_A2).c_str()));
      DrawText("還車成功！請離卡");
      delay(1000);
      ShowGoodbyeMessage();
      _E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E = false;
      _E8_B7_9D_E9_9B_A2 = 0;
    } else {
      DrawText("卡號錯誤！請換卡");
    }
  } else {
    DrawText("借車成功！請離卡");
    _E5_80_9F_E7_9A_84_E5_8D_A1_E8_99_9F = _E5_8D_A1_E8_99_9F;
    _E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E = true;
  }
}

String tcp_https(String type,String domain,String request,int port,int waittime) {
  String getAll="", getBody="";
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();
  if (client_tcp.connect(domain.c_str(), port)) {
    //Serial.println("Connected to "+domain+" successfully.");
    client_tcp.println(type + " " + request + " HTTP/1.1");
    client_tcp.println("Host: " + domain);
    client_tcp.println("Connection: close");
    client_tcp.println("Content-Length: 0");
    client_tcp.println();
    boolean state = false;
    long startTime = millis();
    while ((startTime + waittime) > millis()) {
      while (client_tcp.available()) {
        char c = client_tcp.read();
        if (c == '\n') {
          if (getAll.length()==0) state=true;
           getAll = "";
        }
        else if (c != '\r')
          getAll += String(c);
          if (state==true) getBody += String(c);
          startTime = millis();
        }
        if (getBody.length()!= 0) break;
      }
      client_tcp.stop();
  }
  else {
    getBody="Connected to "+domain+" failed.";
    Serial.println("Connected to "+domain+" failed.");
  }
  return getBody;
}

void ShowGoodbyeMessage() {
  String _E5_9B_9E_E8_A6_86 = (tcp_https("GET", "bike.elepot.dev", (String("/data/send/?id=")+String(_E5_8D_A1_E8_99_9F)), 443, 3000));
  _E5_9B_9E_E8_A6_86 = _E5_9B_9E_E8_A6_86.substring(4, _E5_9B_9E_E8_A6_86.length() + 1- 8);
  _E5_9B_9E_E8_A6_86.trim();
  if (_E5_9B_9E_E8_A6_86 == "Null") {
    DrawText("註冊以得知排名");
  } else {
    DrawText(String("恭喜獲得第")+String(_E5_9B_9E_E8_A6_86)+String("名"));
  }
  delay(1000);
  DrawText(String("你消耗了")+String(String((_E8_B7_9D_E9_9B_A2 * 0.013),2))+String("大卡"));
  delay(1000);
  DrawText("確認折扣請到");
  delay(1000);
  DrawText("bike.elepot.dev");
  delay(3000);
  DrawText(String("卡號")+String(_E5_8D_A1_E8_99_9F));
  delay(30000);
}

void DrawText(String text) {
  Serial.println(text);
  u8g2.firstPage();
  do {
    u8g2.clear();
    u8g2.drawUTF8(0,14,String(text).c_str());
  } while ( u8g2.nextPage() );
}

String readFromNFC_UID() {
  uint8_t success;
  String cardUID="";
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, myNFC_UID_array, &myNFC_UID_Length);
  if (success) {
    for (uint8_t i=0; i < myNFC_UID_Length; i++)
    {
      cardUID+=((String(myNFC_UID_array[i], HEX).length()==1?"0":"")+String(myNFC_UID_array[i], HEX));
    }
  }
  cardUID.toUpperCase();
  return cardUID;
}

String URLEncode(const char* msg)
{
  const char *hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg!='\0'){
      if( ('a' <= *msg && *msg <= 'z')
              || ('A' <= *msg && *msg <= 'Z')
              || ('0' <= *msg && *msg <= '9') ) {
          encodedMsg += *msg;
      } else {
          encodedMsg += '%';
          encodedMsg += hex[*msg >> 4];
          encodedMsg += hex[*msg & 15];
      }
      msg++;
  }
  return encodedMsg;
}

void  sendToGoogleSheets(const String& dateInclude,const String& data)
{
  static TLSClient sheetClient;
  const char* host="script.google.com";
  if (sheetClient.connect(host, 443)) {
      const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=insert&dateInclude="+dateInclude+"&sheetId="+sheetId+"&sheetTag="+sheetTag+"&data="+data;
      sheetClient.println("GET " + url + " HTTP/1.1");
      sheetClient.println(String()+"Host: "+host);
      sheetClient.println("Accept: */*");
      sheetClient.println("Connection: close");
      sheetClient.println();
      sheetClient.println();
      sheetClient.stop();
  }
}

void setup()
{
  nfc.begin();
  initWiFi();
  u8g2.begin();
  u8g2.setFont(u8g2_font_10x20_me);
  u8g2.enableUTF8Print();

  Serial.begin(9600);

}

void loop()
{
  myNFC_UID_Length=0;
  myNFC_UID=readFromNFC_UID();
  if ((myNFC_UID!="")) {
    myNFC_UID_Length=0;
    myNFC_UID=readFromNFC_UID();
    HandleCard(myNFC_UID);
    while ((myNFC_UID!="")) {
      myNFC_UID_Length=0;
      myNFC_UID=readFromNFC_UID();
    }
    if (_E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E) {
      DrawText("還車請感應悠遊卡");
    } else {
      DrawText("借車請感應悠遊卡");
    }
  }
  if (_E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E) {
    DrawText(String("里程： ")+String(_E8_B7_9D_E9_9B_A2)+String(" m"));
  }
}
