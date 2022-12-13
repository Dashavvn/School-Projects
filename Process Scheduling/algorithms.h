#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "scheduler.h"
#include <vector>
struct Scheduler;
struct Statistics;

struct Algorithms{

  Algorithms(){}; 
  virtual void sort(Scheduler* scheduler, std::vector<Process*>processes){ printf("GOOOODDSSS\n");};
  virtual void run(Statistics* stats){};

};

struct FCFS : Algorithms{
  FCFS();
  void sort(Scheduler* scheduler, std::vector<Process*>processes);
  void run(Statistics* stats);
};


#endif
