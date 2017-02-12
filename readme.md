
Config Functions
-------------------------------

Functions to schedule events.

- support to wait until 18 hours, 65534 seconds. (not tested)
- trigger and stop
- trigger and reset

**Manual Installation**

[Download](https://github.com/cristianszwarc/TimeCommander/archive/master.zip) and decompress it to your libraries folder.

**Platformio Installation**

By platformio.ini:
```
...
lib_deps =
     git@github.com:cristianszwarc/TimeCommander.git
...
```

**Basic use**
```cpp
..
// define how many timers we want to track (default def is 5)
#define TIME_FUNCTIONS_MAX_LENGTH 2
#include <TimeCommander.h>

TimeCommander MyTimeCommander;

// define some names for the timers
#define AUTO_OFF_TIMER 0  // a timer to turn off something  
#define REPORT_TIMER 1    // a timer to trigger a report multiple times

void setup() {
  ...
  
  // optional set the timers values to zero or halt
  MyTimeCommander.off(AUTO_OFF_TIMER);     // sets the timer to a halt, will not trigger anything
  MyTimeCommander.set(REPORT_TIMER, 5);    // start closer to the trigger point  
  ...
}

void loop() {
  
  if(MyTimeCommander.loopTo(REPORT_TIMER, 120)) {
    // do something each 120 seconds
  }
  
  // turn off the relay after 90 seconds of being ON
  if(MyTimeCommander.countTo(AUTO_OFF_TIMER, 90)) {

    // turn off the relay, this will be executed only once

  }

  // as an example, turn ON something that should auto-off later
  if (digitalRead(BUTTON_PIN)) {
    // turn on a relay or do something.
    
    // reset the AUTO_OFF_TIMER so it will be triggered when it reaches the desired value
    MyTimeCommander.reset(AUTO_OFF_TIMER);
  }
  
}

```

**License**

MIT
