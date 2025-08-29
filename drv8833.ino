// DRV8833 + UNO (algne pinniskeem): AIN1=2, AIN2=3, BIN1=4, BIN2=5, nSLEEP=7
// Funktsioonid: forward, reverse, leftTurn, rightTurn, coast, brake, wake, sleepDrv

const int AIN1 = 2;
const int AIN2 = 3;
const int BIN1 = 4;
const int BIN2 = 5;
const int nSLEEP = 7;

void wake()      { digitalWrite(nSLEEP, HIGH); }  // draiver töörežiimi
void sleepDrv()  { digitalWrite(nSLEEP, LOW);  }  // draiver standby

void forward() {   // mõlemad mootorid edasi
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
}

void reverse() {   // mõlemad mootorid tagasi
  digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH);
}

void rightTurn() {  // pööre vasakule: parem mootor edasi, vasak seis
  digitalWrite(AIN1, LOW);  digitalWrite(AIN2, LOW);   // vasak seis (coast)
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);   // parem edasi
}

void leftTurn() { // pööre paremale: vasak mootor edasi, parem seis
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);   // vasak edasi
  digitalWrite(BIN1, LOW);  digitalWrite(BIN2, LOW);   // parem seis (coast)
}

void coast() {     // vabajooks – mõlemad kanalid lahti
  digitalWrite(AIN1, LOW);  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);  digitalWrite(BIN2, LOW);
}

void brake() {     // elektriline pidur – mõlemad klemmid kokku
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, HIGH);
}

void setup() {
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(nSLEEP, OUTPUT);
  wake();
  coast();
}

void loop() {
  // forward();   delay(2000);
  // coast();     delay(800);

  // reverse();   delay(2000);
  // coast();     delay(800);

  leftTurn();  delay(1200);
  coast();     delay(600);

  // rightTurn(); delay(1200);
  // coast();     delay(600);

  // brake();     delay(400);
  // coast();     delay(800);
}
