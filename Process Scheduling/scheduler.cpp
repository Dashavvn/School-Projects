#include "scheduler.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

int start_time = 0;
double end_time = 0;
int finished = 0;
double time_used = 0.0;

Statistics::Statistics(){}
Scheduler::Scheduler(){}

FCFS::FCFS(){}
SJR::SJR(){}
SJF::SJF(){}
HRRN::HRRN(){}
RoundRobin::RoundRobin(){}

Scheduler::~Scheduler(){}

void HRRN::sort(Scheduler* s){

  if(s->readyList.empty()){
    for(int i = 0; i < s->processes.size(); ++i){
      s->readyList.push_front(s->processes[i]);
    }
  }
  else if(s->runningList.size() > 2){
    queue<Process*>temp = s->runningList;
    queue<Process*>temp2 = s->runningList;

    Process* currRunning = s->runningList.front();
    double hrrn = 0;
    double hrrn2 = 0;
    temp2.push(temp2.front());
    temp2.pop(); 

    for(int i = 2; i < temp.size(); ++i){

      if(temp.front()->duration > 0 && temp2.front()->duration > 0){
	hrrn = ((temp.front()->wait_time + temp.front()->duration)/(temp.front()->duration));
	hrrn2 = ((temp2.front()->wait_time + temp2.front()->duration)/(temp2.front()->duration));
	if(hrrn < hrrn2){
	  temp.front()->state = 3;
	  temp.push(temp.front());
	  temp.pop();
	}
	temp2.push(temp2.front());
	temp2.pop();
      }
    }

    while(temp.front() != currRunning){
      if(temp.front()->state != 4)
	temp.front()->state = 3;
      temp.push(temp.front());
      temp.pop();
    }

    temp.front()->state == 2;
    s->runningList = temp;
  }
}

void HRRN::run(Scheduler* s, Statistics* stats){

  sort(s);
  s->print('p');

  int cycle = 0;
  while(!s->readyList.empty()){
    sort(s);
    s->stateMachine(cycle);
    cycle += 1;
  }
  end_time = cycle;
}


void SJF::sort(Scheduler* s){

  Process* temp;
  for(int i = 0; i < s->processes.size(); ++i){
    for(int j = 0; j < s->processes.size(); ++j){
      if(s->processes[i]->duration > s->processes[j]->duration){
	temp = s->processes[j];
	s->processes[j] = s->processes[i];
	s->processes[i] = temp;
      }
    }
  }

  for(int i = 0; i < s->processes.size(); ++i){
    s->readyList.push_front(s->processes[i]);
  }
}

void SJF::run(Scheduler* s, Statistics* stats){

  sort(s);
  s->print('p');

  int cycle = 0;
  while(!s->readyList.empty()){
    s->stateMachine(cycle);
    cycle += 1;
  }
  end_time = cycle;
}


/*SHORTEST JOB REMAINING FUNCTIONS*/

void SJR::sort(Scheduler* s){

  if(s->readyList.empty()){
    for(int i = 0; i < s->processes.size(); ++i)
      s->readyList.push_back(s->processes[i]);
  }
  else if(s->runningList.size() > 1){
    queue<Process*>temp = s->runningList;
    queue<Process*>temp2 = s->runningList;

    temp2.push(temp2.front());
    temp2.pop(); 

    for(int i = 0; i < temp.size(); ++i){
      if(temp.front()->duration > temp2.front()->duration){
	temp.front()->state = 3;
	temp.push(temp.front());
	temp.pop();
      }
      temp2.push(temp2.front());
      temp2.pop();
    }
    temp.front()->state == 2;
    s->runningList = temp;
  }
}

void SJR::run(Scheduler* s, Statistics* stats){
  sort(s);
  s->print('p');

  int cycle = 0;
  while(!s->readyList.empty()){
    sort(s);
    s->stateMachine(cycle);

    cycle += 1;

  }
  end_time = cycle; 
}

/*======================================*/


/*========ROUND ROBIN FUNCTIONS=======*/

void RoundRobin::sort(Scheduler* s){
  if(s->readyList.empty()){
    for(int i = 0; i < s->processes.size(); ++i)
      s->readyList.push_back(s->processes[i]);
  }
  else if(!s->runningList.empty()){
    if(s->runningList.front()->state == 2)
      s->runningList.front()->state = 3;
    if(s->runningList.front()->duration == 0){
      s->runningList.front()->state = 4;
      s->runningList.pop();
    }
    else{
      s->runningList.push(s->runningList.front());
      s->runningList.pop();
    }
  }
}

void RoundRobin::run(Scheduler* s, Statistics* stats){

  sort(s);
  s->print('p');

  int cycle = 0;
  int quantum = 5;
  while(!s->readyList.empty()){ 

    if(quantum <= 0){
      //cout << "Sorting" << endl;
      sort(s); 
      quantum = 5;
    }

    s->stateMachine(cycle); 

    cycle += 1;
    quantum -= 1;

    //if(cycle == 100)
    //  break;
  }
  end_time = cycle;

}

/*====================================*/


/*==========FCFS FUNCTIONS===========*/

void FCFS::sort(Scheduler* s){

  Process* temp;
  for(int i = 0; i < s->processes.size(); ++i){
    for(int j = 0; j < s->processes.size(); ++j){
      if(s->processes[i]->start_time > s->processes[j]->start_time){
	temp = s->processes[j];
	s->processes[j] = s->processes[i];
	s->processes[i] = temp;
      }
    }
  }

  for(int i = 0; i < s->processes.size(); ++i){
    s->readyList.push_front(s->processes[i]);
  }
}

void FCFS::run(Scheduler* s, Statistics* stats){

  sort(s);
  s->print('p');

  int cycle = 0;
  while(!s->readyList.empty()){
    s->stateMachine(cycle);
    cycle += 1;
  }
  end_time = cycle;
}

/*==================================*/


/*========SCHEDULER FUNCTIONS========*/

void Scheduler::stateMachine(int cycle){

  //Ready list
  for(int i = 0; i < readyList.size(); ++i){

    if(readyList[i]->state == 1){
      if(runningList.front() != readyList[i])
	readyList[i]->state = 3; //waiting
      else
	readyList[i]->state = 2; //running
    }
    else if(readyList[i]->state == 3){
      readyList[i]->wait_time += 1;
    }
    else if(readyList[i]->state == 4){
      readyList[i]->end_time = cycle;
      readyList.erase(readyList.begin()+i);
      finished += 1;
    }

    if(readyList[i]->start_time == cycle){
      if(runningList.empty())
	start_time = cycle;
      readyList[i]->state = 1; //started
      runningList.push(readyList[i]);
    }
  }

  //Running list
  if(!runningList.empty()){
    Process* curr = runningList.front();
    if(curr->state != 1){
      curr->state = 2;

      //TODO fix issue of process with duration 1 being taken off the cpu after it runs
      curr->duration -= 1;
      if(curr->duration < 0){
	curr->state = 4; //ended
	runningList.pop();
	if(runningList.front() != NULL){
	  runningList.front()->state = 2;
	  runningList.front()->duration -= 1;
	}
      }
    }
  }

  printf("%d\t", cycle); 
  print('c');
}

void Scheduler::print(char flag){
  /*
     PRINT FLAGS:
     'p' : print processes in process list
     'c' : print current cycle time info
     's' : print statistics
   */

  switch((int)flag){
    case 'p':
      {
      printf("Process ID \t Start Time \t Duration\n");
      for(int i = processes.size()-1; i >= 0; --i){
	printf("%s: \t\t [%d] \t\t [%d]\n", 
	    processes[i]->ID.c_str(), 
	    processes[i]->start_time, 
	    processes[i]->duration); 
      }
      printf("\n");
      break;
      }

    case 'c':
      {
      int state;
      int chr;
      bool cpu_used = false;
      for(int i = processes.size()-1; i >= 0; --i){
	state = processes[i]->state;
	if(state == 0) //not started
	  chr = '.';
	else if(state == 1)
	  chr = 'S'; //started
	else if(state == 2){
	  chr = 'X'; //running
	  cpu_used = true;
	}
	else if(state == 3)
	  chr = '|'; //waiting
	else if(state == 4)
	  chr = ' '; //ended 
	printf("%c\t", chr);
      }
      if(cpu_used)
	time_used += 1.0;
      printf("\n");
      break;
      }
    
    case 's':
      {
      int makespan = end_time - start_time;
      int completion_time = 0;
      double util = (time_used/end_time);
      double throughput = (double)processes.size() / (double)makespan;
      
      double wait_time = 0.0;

      for(int i = 0; i < processes.size(); ++i){
	wait_time += processes[i]->wait_time;
	completion_time += processes[i]->end_time - processes[i]->start_time;
      }
      wait_time = wait_time / processes.size();

      cout << "======== Program Statistics ========\n" << endl;
      cout << "Makespan: "<< makespan << endl;
      cout << "Average wait time: " << wait_time << endl;
      cout << "Completion time: " << completion_time << endl;
      cout << "Throughput: " << throughput << endl;
      cout << "Cpu utilization: " << util << endl;
      break; 
      }
  }
}

bool Scheduler::addProcess(string data, int p_count, bool random){

  Process* newProc;

  if(!random){
    int pos = 0;
    string buffer[3];

    istringstream line(data);
    string seg;

    while(line >> seg){
      buffer[pos] = seg;
      ++pos;
    }

    if(pos < 3 || pos > 3){
      printf("ERROR: Process should have 3 attributes. Current count: %d. [ID] [start time] [duration].\n", pos);
      return false;
    } 

    newProc = new Process();

    newProc->ID = buffer[0];
    newProc->start_time = stoi(buffer[1]);
    newProc->duration = stoi(buffer[2]);

    processes.push_back(newProc);
    return true;
  }
  else{
    for(int i = 0; i < p_count; ++i){
      int start_time = 0;
      int duration = 0;

      while(start_time <= 0 || duration <= 0){
	if(start_time <= 0)
	  start_time = rand() % 20;
	if(duration <= 0)
	  duration = rand() % 15;
      }

      newProc = new Process();
      string name = ("rand" + to_string(i)); 

      newProc->ID = name;
      newProc->start_time = start_time;
      newProc->duration = duration;

      processes.push_back(newProc);
    }
  }
}
