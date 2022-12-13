#include "algorithms.h"
#include "process.h"
#include <stdlib.h>
#include <sstream>


FCFS::FCFS(){}


/*==========FCFS FUNCTIONS===========*/

void FCFS::sort(Scheduler* s, std::vector<Process*>processes){
  std::vector<Process*>p_cpy = processes;
  //queue<Process*>rl = &s->readyList;
  
  Process* proc_to_push = p_cpy[0]; 
  Process* temp;
  int pos = 0;
  
  for(int i = 0; i < p_cpy.size(); ++i){
    for(int j = 0; j < p_cpy.size(); ++j){
      if(p_cpy[j]->start_time < proc_to_push->start_time){
	proc_to_push = p_cpy[j];
	pos = j;
      }
    }
    s->readyList.push(proc_to_push);
    temp = p_cpy.back();
    p_cpy[p_cpy.size()-1] = proc_to_push;
    p_cpy[pos] = temp;
    p_cpy.pop_back();
    
    if(p_cpy.size() == 1){
      s->readyList.push(p_cpy[0]);
      break;
    }
  }
}

void FCFS::run(Statistics* stats){}

/*==================================*/
