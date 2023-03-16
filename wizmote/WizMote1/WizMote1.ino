byte SRO; // ShiftRegisterOutput
int moon; // Moon Button
void setup() {
  pinMode(14, INPUT); // Moon Button
  pinMode(13, OUTPUT); // Shiftregister PL
  digitalWrite(13, HIGH);
  pinMode(5, INPUT); // Data In
  pinMode(4, OUTPUT); // Clock
  if(digitalRead(14) == LOW) {
    moon = 1;
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
  }
  if (SRO == 0x7F) {
    Serial.println("OFF");
  }
  if (SRO == 0xEF) {
    Serial.println("1");
  }
  if (SRO == 0xDF) {
    Serial.println("2");
  }
  if (SRO == 0xFB) {
    Serial.println("3");
  }
  if (SRO == 0xF7) {
    Serial.println("4");
  }
  if (SRO == 0xFE) {
    Serial.println("-");
  }
  if (SRO == 0xFD) {
    Serial.println("+");
  }
  if(moon == 1) {
    Serial.println("MOON");
  }
  Serial.println(analogRead(0));
  delay(1000);
  ESP.deepSleep(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
