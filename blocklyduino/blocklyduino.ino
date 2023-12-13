//Generated Date: Wed, 13 Dec 2023 14:07:50 GMT

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
boolean _E4_B8_8A_E4_B8_80_E6_AC_A1_E5_81_B5_E6_B8_AC_E5_88_B0_E7_A3_81_E9_90_B5 = false;
double _E8_B7_9D_E9_9B_A2 = 0;
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
String myNFC_UID="";
uint8_t myNFC_UID_array[] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t myNFC_UID_Length;

char _lwifi_ssid[] = "mist3";
char _lwifi_pass[] = "juli0223";
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

void DrawText(String text) {
  Serial.println(text);
  u8g2.firstPage();
  do {
    u8g2.clear();
    u8g2.drawUTF8(0,14,String(text).c_str());
  } while ( u8g2.nextPage() );
}

void interrupt_2(){
  if (_E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E) {
    _E8_B7_9D_E9_9B_A2 = _E8_B7_9D_E9_9B_A2 + 1.2;
    Serial.println((String("Distance (m): ")+String(_E8_B7_9D_E9_9B_A2)));
    _E4_B8_8A_E4_B8_80_E6_AC_A1_E5_81_B5_E6_B8_AC_E5_88_B0_E7_A3_81_E9_90_B5 = true;
  }
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
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
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
  u8g2.begin();
  u8g2.setFont(u8g2_font_10x20_me);
  u8g2.enableUTF8Print();
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  sheetId="1ANhQHgFkB4Ce9WfsSZ4gT-u6YW7g4n33WO7UtMNWouI";
  sheetTag=URLEncode("Database");
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  DrawText("借車請感應悠遊卡");
  Serial.begin(9600);

  attachInterrupt(2,interrupt_2,FALLING);
}

void loop()
{
  myNFC_UID_Length=0;
  myNFC_UID=readFromNFC_UID();
  if ((myNFC_UID!="")) {
    String _E5_8D_A1_E8_99_9F = myNFC_UID;
    Serial.println(_E5_8D_A1_E8_99_9F);
    if (_E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E) {
      if (_E5_8D_A1_E8_99_9F == _E5_80_9F_E7_9A_84_E5_8D_A1_E8_99_9F) {
        DrawText("");
        sendToGoogleSheets("1",URLEncode((String() + _E5_8D_A1_E8_99_9F + "," + _E8_B7_9D_E9_9B_A2).c_str()));
        _E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E = false;
        _E8_B7_9D_E9_9B_A2 = 0;
      } else {
        Serial.println("Wrong Card Number!");
      }
    } else {
      Serial.println("User borrowed bike!");
      _E5_80_9F_E7_9A_84_E5_8D_A1_E8_99_9F = _E5_8D_A1_E8_99_9F;
      _E6_AD_A3_E5_9C_A8_E8_A2_AB_E9_A8_8E = true;
    }
    Serial.println("Waiting til card leaves...");
    myNFC_UID_Length=0;
    myNFC_UID=readFromNFC_UID();
    while ((myNFC_UID!="")) {
      myNFC_UID_Length=0;
      myNFC_UID=readFromNFC_UID();
    }
    Serial.println("Card leaved!");
  }
}
