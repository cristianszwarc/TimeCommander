/*
  TimeCommander.h - Functions to schedule triggers.
  Created by Cristian D. Szwarc, January 2017.
  Released into the public domain.
*/
#ifndef TIME_FUNCTIONS
#define TIME_FUNCTIONS

#ifndef TIME_FUNCTIONS_MAX_LENGTH
#define TIME_FUNCTIONS_MAX_LENGTH 2
#endif

class TimeCommander
{
private:
  unsigned long int lastTime = 0;
  unsigned int timers[TIME_FUNCTIONS_MAX_LENGTH];  // define maximum qty of timers to track
  void keepTime();

public:
  void set(short int timerID, unsigned int seconds);
  void off(short int timerID);
  void reset(short int timerID);
  unsigned int get(short int timerID);
  unsigned int getRemaining(short int timerID, unsigned int until);
  bool countTo(short int timerID, unsigned int seconds = 1, bool reset = false);
  bool loopTo(short int timerID, unsigned int seconds = 1);};

#endif
