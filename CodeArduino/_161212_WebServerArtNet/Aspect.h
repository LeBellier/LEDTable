#ifndef ASPECT_H
#define ASPECT_H

// Prototypage Aspect
void hasDebugDelay(int duration);
void hasDebug(void (*fonc)());

// Déclaration
void hasDebugDelay(int duration) {
#ifdef DEBUG_INIT
  delay (duration);
#endif
}
void hasDebug(void (*fonc)()) {
#ifdef DEBUG_INIT
  Serial.begin(BAUDRATE);
  fonc ();
  //Serial.end();
#else
  Serial.end();
  fonc();
  Serial.begin(BAUDRATE);
#endif
}
#endif
