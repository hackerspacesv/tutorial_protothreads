#include <pt.h>
#include <LiquidCrystal.h>
#include <stdio.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

struct pt pt1;
struct pt pt2;
struct pt pt3;
struct pt pt4;

void formatTime(long t_tthsec, char *str_buffer) {
  int hours = (t_tthsec/36000)%24;
  int minutes = (t_tthsec/600)%60;
  int seconds = (t_tthsec/10)%60;
  int tth_seconds = t_tthsec%10;
  sprintf(str_buffer, "%02d:%02d:%02d.%01d", hours, minutes, seconds, tth_seconds);
}

void setup() {
  //parpadeo();
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);
}

void loop() {
  static long tth_sec = 0;
  static int is_running = 1;

  reloj(&pt1, tth_sec, is_running);
  boton1(&pt2, 7, tth_sec);
  boton2(&pt3, 6, is_running);
  led_sequence(&pt4, is_running);
}

char str_time[11] = "00:00:00.0";

void reloj(struct pt *pt, long &counter, int &is_running) {
  PT_BEGIN(pt);
  static long v = 0;

  Serial.begin(9600);

  
  lcd.begin(16,2);

  while(true) {
    lcd.setCursor(0,0);
    formatTime(counter, str_time);
    lcd.print(str_time);
    if(is_running) {
      counter++;
    }

    v = millis();
    PT_WAIT_WHILE(pt, ((millis()-v) < 100));
  }
  PT_END(pt);
}

void boton1(struct pt *pt,int pin, long &counter) {
  PT_BEGIN(pt);
  static long v = 0;
  static int oldVal = 0;
  static int newVal = 0;
  pinMode(pin, INPUT_PULLUP);

  while(true) {
    newVal = digitalRead(pin);
    
    if(((newVal^oldVal)==1) && newVal == 0) {
      counter = 0;

      // Ignore future readings for 100milliseconds
      v = millis();
      PT_WAIT_WHILE(pt, ((millis()-v) < 200));      
    }
    
    oldVal = newVal;
    PT_YIELD(pt);
  }
  PT_END(pt);
}

void boton2(struct pt *pt, int pin, int &is_running) {
  static long v = 0;
  static int oldVal = 0;
  static int newVal = 0;
  PT_BEGIN(pt);
  pinMode(pin, INPUT_PULLUP);

  while(true) {
    newVal = digitalRead(pin);
    if(((newVal^oldVal)==1) && newVal == 0) {
      is_running ^= 1;
      
      v = millis();
      PT_WAIT_WHILE(pt, ((millis()-v) < 200));      
    }
    
    oldVal = newVal;
    PT_YIELD(pt);
  }
  PT_END(pt);
}


void led_sequence(struct pt *pt, int &is_running) {
  PT_BEGIN(pt);
  static long v = 0;
  static int led_val = 1;
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  while(true) {
    if(led_val>4) {
      led_val = 1;
    }
    if(is_running) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    } else {
      digitalWrite(8, led_val & 1);
      digitalWrite(9, led_val & 2);
      digitalWrite(10, led_val & 4);
    }

    led_val = led_val<<1;
    
    v = millis();
    PT_WAIT_WHILE(pt, ((millis()-v) < 100));    
  }
  PT_END(pt);
}

