/*
  TimeCommander.cpp - Functions to schedule triggers.
  Created by Cristian D. Szwarc, January 2017.
  Released into the public domain.
*/
#include "TimeCommander.h"

// set the value of a timer
void TimeCommander::set(short int timerID, unsigned int seconds)
{
  timers[timerID] = seconds;
}

// set the value of a timer to the halt/triggered flag
void TimeCommander::off(short int timerID)
{
  timers[timerID] = 65535;
}

// set the value of a timer to 0
void TimeCommander::reset(short int timerID)
{
  timers[timerID] = 0;
}

// get the value of a timer
unsigned int TimeCommander::get(short int timerID)
{
  return timers[timerID];
}

// helper: given a timer, return the remaining time until a given value
unsigned int TimeCommander::getRemaining(short int timerID, unsigned int until)
{
  int diff = until - timers[timerID];
  if (diff<0) {
    return 0;
  } else {
    return diff;
  }

}

// keep timers running, update each timer (in seconds)
void TimeCommander::keepTime()
{
  unsigned timeDiff = (millis() - lastTime);
  int timersLength = (sizeof(timers)/sizeof(*timers));
  int n = 0;

  // increment each timer 1 second N times
  while(timeDiff>=1000) {
    Serial.println();
    // increment each timer one second (be aware, they need to be consumed to not rollover)
    while(n<timersLength) {
      // timers roll over at 65534, because 65535 is a reached flag
      // do nothing if is 65535 (halt)
      if (timers[n] < 65534) {
        timers[n]++;
      } else if (timers[n] == 65534) {
        timers[n] = 0;
      }
      Serial.println(timers[n]);
      n++;
    }
    timeDiff = timeDiff - 1000;
  }

  // track time since last update
  lastTime = millis() - timeDiff;

}

// return true if a value was reached, no reset the timer unless requested
bool TimeCommander::countTo(short int timerID, unsigned int seconds, bool reset)
{
  this->keepTime();

  // max seconds 65534
  if (seconds >= 65535) {
    seconds = 65534;
  }

  // required time reached?
  if (timers[timerID] >= seconds) {
    if (reset) {
      // we want to trigger the event (return true) and start over
      timers[timerID] = 0;
      return true;
      
    } else {
      // time reached, decide if this was already triggered
      if (timers[timerID] == 65535) {
        // was already triggered
        return false;
      } else {
        // set a triggered flag and return true
        timers[timerID] = 65535;
        return true;
      }
      
    }

  } else {
    // time not reached
    return false;
  }

}

// return true if a value was reached, and reset the timer to start again
bool TimeCommander::loopTo(short int timerID, unsigned int seconds)
{
  return this->countTo(timerID, seconds, true);
}
