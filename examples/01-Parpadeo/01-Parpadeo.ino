#include <pt.h>

struct pt hilo1;
struct pt hilo2;
struct pt hilo3;

void setup() {
  PT_INIT(&hilo1);
  PT_INIT(&hilo2);
  PT_INIT(&hilo3);
}

void loop() {
  parpadeo(&hilo1);
  parpadeo(&hilo2);
  parpadeo(&hilo3);
}

void parpadeo(struct pt *pt) {
  PT_BEGIN(pt);
  // void setup() {
  static long t = 0;
  pinMode(10, OUTPUT);
  // }
  
  do {
  // void loop() {
    digitalWrite(10, HIGH);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<1000);
    
    digitalWrite(10, LOW);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<1000);
  // }
  } while(true);
  PT_END(pt);
}

void parpadeo2(struct pt *pt) {
  PT_BEGIN(pt);
  // void setup() {
  static long t = 0;
  pinMode(9, OUTPUT);
  // }
  
  do {
  // void loop() {
    digitalWrite(9, HIGH);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<500);
    
    digitalWrite(9, LOW);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<500);
  // }
  } while(true);
  PT_END(pt);
}

void parpadeo3(struct pt *pt) {
  PT_BEGIN(pt);
  // void setup() {
  static long t = 0;
  pinMode(8, OUTPUT);
  // }
  
  do {
  // void loop() {
    digitalWrite(8, HIGH);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<250);
    
    digitalWrite(8, LOW);
    t = millis();
    PT_WAIT_WHILE(pt, (millis()-t)<250);
  // }
  } while(true);
  PT_END(pt);
}

