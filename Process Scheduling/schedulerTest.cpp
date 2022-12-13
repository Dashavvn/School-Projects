#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <getopt.h>
#include "scheduler.h"


using namespace std;

void parseFile(string in_file, Scheduler* scheduler){

  string line;
  ifstream file; 

  //  printf(">>>Opening file: %s\n", in_file.c_str()); 
  file.open(in_file);
  if(file.fail()){
    printf("ERROR: Invalid file path.\n");
    return;
  }

  while(getline(file, line))
    scheduler->addProcess(line, 0, 0);

  file.close();
}

int main(int argc, char* argv[]){

  Scheduler* scheduler = new Scheduler(); 
  Statistics* stats = new Statistics();

  int numRandom = 0;
  int index = 0;

  //const char* s_opt = "fRhsSr:";
  static struct option long_opt[] = {
    {"fcfs", no_argument, NULL, 'f'},
    {"rr", no_argument, NULL, 'R'},
    {"hrrn", no_argument, NULL, 'h'},
    {"sjf", no_argument, NULL, 's'},
    {"sjr", no_argument, NULL, 'S'},
    {"r", required_argument, NULL, 'r'},
    {NULL,no_argument,NULL,0}
  };


  if(argc == 5 || argc == 3){
    parseFile(argv[argc-1],scheduler);
  }

  int opt;

  if(argc > 2){
    while((opt = getopt_long_only(argc,argv,"",long_opt,&index)) != -1){
      Scheduler* currOp;

      switch(opt)
      {
	case 'f': // -fcfs
	  //call fcfs
	  currOp = new FCFS();
	  currOp->run(scheduler, stats);
	  scheduler->print('s');
	  break;

	case 'R': // -rr
	  //call roundrobin
	  currOp = new RoundRobin();
	  currOp->run(scheduler, stats);
	  scheduler->print('s');
	  break;

	case 'h': // -hrrn
	  //call hrrn
	  currOp = new HRRN();
	  currOp->run(scheduler, stats);
	  scheduler->print('s');
	  break;

	case 'S': // -sjr
	  //call sjr
	  currOp = new SJR();
	  currOp->run(scheduler, stats);
	  scheduler->print('s');
	  break;

	case 's': // -sjf
	  //call sjf
	  currOp = new SJF();
	  currOp->run(scheduler,stats);
	  scheduler->print('s');
	  break;

	case 'r':   //-r [#]
	  if(!isdigit(*optarg)){
	    cout << "-r must be follow by a valid integer." << endl;
	    break;
	  }
	  else if(argc < 4)
	  {
	    cout << "Not enough command line arguments. You are missing the algorithm flag." << endl;
	    cout << endl;
	    break;
	  }	 
	  else{	
	    numRandom = atoi(optarg);
	    //call create random processes
	    scheduler->addProcess("", numRandom, 1);
	    break;
	  }
	case '?': //Invalid argument
	  cout << "Valid input flags are -fcfs, -hrrn, -sjr, -sjf, -rr, and -r [num]" << endl;
	  break;

	default:
	  break;
      }
    }
  }
  else 
    cout << "You must be atleast 3 command line arguments.  There must be an algorithm and either the random process flag or a file of processes to read in." << endl;
}

