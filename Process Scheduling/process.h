#ifndef PROCESS_H
#define PROCESS_H

#include "stdlib.h"
#include <string>

struct Process{

  Process();

  enum states{
    NOT_STARTED,
    STARTED,
    RUNNING,
    WAITING,
    ENDED
  };

  std::string ID;
  int state = 0;
  int start_time = 0;
  int end_time = 0;
  int duration = 0;
  int wait_time = 0;

  void changeState(int state);
  void debugPrint();
};

#endif
