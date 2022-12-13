#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>


struct Statistics{
  
  Statistics();
  
  int makespan = 0;
  int throughput = 0;
  int total = 0;
  double average = 0.0;
  float utilization = 0.0;
};


struct Scheduler{
  Scheduler();
  ~Scheduler();
  
  std::vector<Process*>processes;
  std::queue<Process*>runningList;
  std::deque<Process*>readyList;

  void stateMachine(int cycle);
  void print(char flag);
  bool addProcess(std::string data, int process_count, bool flag);
  
  virtual void run(Scheduler* scheduler, Statistics* stats){};
  virtual void sort(Scheduler* scheduler){};
};

struct FCFS : Scheduler{
  FCFS();
  void sort(Scheduler* scheduler);
  void run(Scheduler* scheduler, Statistics* stats);
};

struct RoundRobin : Scheduler{
  RoundRobin();
  void sort(Scheduler* scheduler);
  void run(Scheduler* scheduler, Statistics* stats);
};

struct SJR : Scheduler{
  SJR();
  void sort(Scheduler* scheduler);
  void run(Scheduler* scheduler, Statistics* stats);
};

struct SJF : Scheduler{
  SJF();
  void sort(Scheduler* scheduler);
  void run(Scheduler* scheduler, Statistics* stats);
};

struct HRRN : Scheduler{
  HRRN();
  void sort(Scheduler* scheduler);
  void run(Scheduler* scheduler, Statistics* stats);
};


#endif
