#include <ESP8266WiFi.h>
#include <espnow.h>

byte SRO; // ShiftRegisterOutput
int moon; // Moon Button
int button;
String Name = "WizMote1";  
uint8_t broadcastAddress[] = {0xC4, 0x5B, 0xBE, 0x74, 0x3B, 0xAF};
float Voltage = 0;
int trySend = 0;
typedef struct struct_message {
  String a;
  float b;
  float c;
  float d;
  float e;
  int f;
  //String g;
} struct_message;

struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 2000;  // send readings timer

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
    ESP.deepSleep(1);
  }
  else {
    //digitalWrite(D4, LOW);
    Serial.println("Delivery fail");
    delay(1000);
    trySend = trySend + 1;
    if(trySend >= 5) {
      ESP.deepSleep(1);
    }
  }
}

void setup() {
    pinMode(14, INPUT); // Moon Button
  pinMode(13, OUTPUT); // Shiftregister PL
  digitalWrite(13, HIGH);
  pinMode(5, INPUT); // Data In
  pinMode(4, OUTPUT); // Clock
  if(digitalRead(14) == LOW) {
    moon = 1;
    button = 3;
  }
  for (int i = 0; i < 8; i++) {
    if (digitalRead(5) == HIGH) {
      bitSet(SRO, i);
    }
    digitalWrite(4, HIGH); //Clock HIGH
    delay(1);
    digitalWrite(4, LOW); //Clock LOW
  }
  Serial.begin(115200);
  //delay(100);
  Serial.println();
  Serial.println(SRO, HEX);
  if (SRO == 0xBF) {
    Serial.println("ON");
    button = 1;
  }
  if (SRO == 0x7F) {
    Serial.println("OFF");
    button = 2;
  }
  if (SRO == 0xEF) {
    Serial.println("1");
    button = 4;
  }
  if (SRO == 0xDF) {
    Serial.println("2");
    button = 5;
  }
  if (SRO == 0xFB) {
    Serial.println("3");
    button = 6;
  }
  if (SRO == 0xF7) {
    Serial.println("4");
    button = 7;
  }
  if (SRO == 0xFE) {
    Serial.println("-");
    button = 8;
  }
  if (SRO == 0xFD) {
    Serial.println("+");
    button = 9;
  }
  if(moon == 1) {
    Serial.println("MOON");
  }

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}


void loop() {
  //mac = WiFi.macAddress();
  Serial.print("Name: ");
  Serial.println(Name);
  Serial.print("Millis: ");
  Serial.println(millis());
  Serial.print("ADC: ");
  Serial.println(analogRead(0));
  Serial.print("MAC Adresse: ");

  myData.a = Name;
  myData.b = button;
  myData.c = analogRead(0);
  myData.d = millis();
 // myData.e =
  //myData.g = String(mac);
 // myData.f = 
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
}
