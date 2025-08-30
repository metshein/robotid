// Muutujad, mida kasutatakse ISR-is, peavad olema 'volatile',
// sest nende väärtust muudetakse katkestuste sees.
volatile uint32_t ch1Start, ch3Start;   // salvestavad hetke, millal impulss algas
volatile uint16_t ch1Pulse, ch3Pulse;   // salvestavad mõõdetud impulsi laiuse (µs)

// Katkestuse teenindaja CH1 jaoks
void ISR_ch1() {
  static bool high = false;             // mäletab, kas praegu on kõrgtase
  uint32_t t = micros();                // hetke aeg mikrosekundites

  if (digitalRead(2)) {                 // kui pin 2 läks HIGH
    ch1Start = t;                       // salvesta algusaeg
    high = true;
  }
  else if (high) {                      // kui pin 2 läks LOW ja enne oli HIGH
    ch1Pulse = (uint16_t)(t - ch1Start);// arvuta impulsi pikkus
    high = false;
  }
}

// Sama loogika CH3 jaoks
void ISR_ch3() {
  static bool high = false;
  uint32_t t = micros();
  if (digitalRead(3)) {
    ch3Start = t;
    high = true;
  }
  else if (high) {
    ch3Pulse = (uint16_t)(t - ch3Start);
    high = false;
  }
}

void setup() {
  pinMode(2, INPUT);   // sisend CH1 signaalile
  pinMode(3, INPUT);   // sisend CH3 signaalile

  // Seome katkestused pinidega: iga tõusev/langev serv kutsub ISR välja
  attachInterrupt(digitalPinToInterrupt(2), ISR_ch1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISR_ch3, CHANGE);

  Serial.begin(115200); // seriaalmonitori jaoks
}

void loop() {
  // Loeme mõlemad pulsilaiused korraga, katkestused ajutiselt kinni,
  // et väärtused ei muutuks poole lugemise pealt.
  noInterrupts();
  uint16_t a = ch1Pulse, b = ch3Pulse;
  interrupts();

  // a ja b näitavad PWM pulsilaiust mikrosekundites (~1000–2000 µs RC jaoks)
  Serial.print("CH1="); Serial.print(a);
  Serial.print("  CH3="); Serial.println(b);

  delay(20); // ~üks RC kaader (50 Hz)
}
