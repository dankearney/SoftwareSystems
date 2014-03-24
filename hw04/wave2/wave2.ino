/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
   
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;
int counter = 0;
volatile boolean on = false;

long lastDebounceTimeSwitch = 0; 
long lastDebounceTimeMode = 0;
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int playing = 0;
int waves[3][100] = {
  {146, 153, 160, 167, 173, 180, 187, 193, 199, 205, 211, 216, 221, 226, 231, 235, 239, 242, 245, 248, 250, 252, 253, 254, 255, 255, 255, 254, 253, 251, 249, 247, 244, 240, 237, 233, 228, 224, 219, 213, 208, 202, 196, 190, 183, 177, 170, 163, 156, 149, 143, 136, 129, 122, 115, 109, 102, 96, 90, 84, 79, 73, 68, 64, 59, 55, 52, 48, 45, 43, 41, 39, 38, 37, 37, 37, 38, 39, 40, 42, 44, 47, 50, 53, 57, 61, 66, 71, 76, 81, 87, 93, 99, 105, 112, 119, 125, 132, 139, 146},
  {146, 160, 173, 187, 199, 211, 221, 231, 239, 245, 250, 253, 255, 255, 253, 249, 244, 237, 228, 219, 208, 196, 183, 170, 156, 143, 129, 115, 102, 90, 79, 68, 59, 52, 45, 41, 38, 37, 38, 40, 44, 50, 57, 66, 76, 87, 99, 112, 125, 139, 153, 167, 180, 193, 205, 216, 226, 235, 242, 248, 252, 254, 255, 254, 251, 247, 240, 233, 224, 213, 202, 190, 177, 163, 149, 136, 122, 109, 96, 84, 73, 64, 55, 48, 43, 39, 37, 37, 39, 42, 47, 53, 61, 71, 81, 93, 105, 119, 132, 146},
  {146, 167, 187, 205, 221, 235, 245, 252, 255, 254, 249, 240, 228, 213, 196, 177, 156, 136, 115, 96, 79, 64, 52, 43, 38, 37, 40, 47, 57, 71, 87, 105, 125, 146, 167, 187, 205, 221, 235, 245, 252, 255, 254, 249, 240, 228, 213, 196, 177, 156, 136, 115, 96, 79, 64, 52, 43, 38, 37, 40, 47, 57, 71, 87, 105, 125, 146, 167, 187, 205, 221, 235, 245, 252, 255, 254, 249, 240, 228, 213, 196, 177, 156, 136, 115, 96, 79, 64, 52, 43, 38, 37, 40, 47, 57, 71, 87, 105, 125, 146},
};

static const unsigned char BitReverseTable256[] = 
{
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  
  pinMode(ledPin, OUTPUT);

  attachInterrupt(0, togglePlay, FALLING);
  attachInterrupt(1, switchSound, FALLING);
  
  pinMode(13, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(10, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(8, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(6, OUTPUT);  
  
  cli();
  
  TCCR2A = 0;  // set entire TCCR2A register to 0
  TCCR2B = 0;  // same for TCCR2B
  TCNT2  = 0;  //initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = (16*1000000) / (8000*8) - 1;
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler  
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts
}

void switchSound() {
  if ((lastDebounceTimeMode - millis()) > debounceDelay) {
    playing = (playing + 1) % sizeof(waves);
  }
}

void togglePlay() {
  if ((lastDebounceTimeSwitch - millis()) > debounceDelay) {
    on = !on;
    digitalWrite(ledPin, on ? HIGH : LOW);
    attachInterrupt(0, togglePlay, on ? RISING : FALLING);
    lastDebounceTimeSwitch = millis();
  }
}

ISR(TIMER2_COMPA_vect){
  counter =  (counter + 1) % sizeof(waves[playing]);
}

void writeByte(int x) {
  PORTB = BitReverseTable256[x];
}

void loop() {
  if (on) 
    writeByte(waves[playing][counter]);
}
