void hasDebugDelay(int duration) {
#ifdef DEBUG
  delay (duration);
#endif
}
void hasDebug ( void (*fonc)() ) {
#ifdef DEBUG
  Serial.begin(BAUDRATE);
  fonc ();
  //Serial.end();
#else
  Serial.end();
  fonc ();
  Serial.begin(BAUDRATE);
#endif
}

