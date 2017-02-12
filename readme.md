
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
  
  // optional set the timers values to zero
  // or to a high value if we want to start them disabled or closer to execution
  MyTimeCommander.set(AUTO_OFF_TIMER, 91);  // auto off not running
  MyTimeCommander.set(REPORT_TIMER, 0);     // start in zero
  
  ...
}

void loop() {
  
  if(MyTimeCommander.loopTo(REPORT_TIMER, 120)) {
    // do something each 120 seconds
  }

  // as an example, turn ON something that should auto-off later
  if (digitalRead(BUTTON_PIN)) {
    // turn on a relay or something.
    
    // reset the AUTO_OFF_TIMER to 0
    MyTimeCommander.set(AUTO_OFF_TIMER, 0);
  }
  
  // turn off the relay after 90 seconds of being ON
  if(MyTimeTracker.countTo(AUTO_OFF_TIMER, 90)) {

    // turn off the relay, this will be executed only once

  }
  
}

```

**License**

MIT
