#pragma once
#ifndef processH
#define processH

#include <string>
#include <ctime>
#include <iostream>
#include <list>
#include <map>

using std::map;
using std::list;
using std::string;
using std::cout;
using std::endl;

namespace process{
	//#1
	struct heap{ int i = 1; };			//Template for heap struct.
	struct stack{ int i = 1; };			//Template for stack struct.
	struct symbolTable{ int i = 1; };	//Template for symbolTable struct.
	struct subroutine{ int i = 1; };	//Template for subroutine struct.
	struct library{ int i = 1; };		//Template for  struct.
	struct instruction{ int i = 1; };	//Template for instruction struct.

	class Process{
		public:
			int pid; 					//Process ID or PID: Numeric identifier for the process
			string pname = "error";		//Process Name: (Hopefully) easier-to-understand identifier for the process (i.e. subtraction.exe)
			time_t startTime; 			//Epoch time when the process was started. time_t is from the <ctime> library.
			struct tm timestamp;		//Used to hold the time data structure used by <ctime> that's more human-readable.
			int core; 					//Indicates which core the process is running on. (i.e. Core 1, Core 2.)
			int coreUtil;				//Indicates the utilization of the core. Is a percentage, range is 0 to 100.
			int lineCount = -1;			//The process' number lines of code.
			int currLine;				//Which line of code the CPU is currently executing.

			void incrementLine(){ //Function for incrementing current line and the instruction pointer.
				currLine++; 	//Increment the integer counter for line
				instructions++; //Go the next instruction in the memory.
			}; 			

			//Process constructors.
			Process(int instructionCount, int heapSize = 100000, int stackSize = 10000){
				time(&startTime); //Log when the process was started
				localtime_s(&timestamp, &startTime); //Turn epoch time to calendar time

				lineCount = instructionCount; //Set the line count

				//Allocate memory for the instructions/main program
				instructions = (instruction* )malloc(sizeof(instruction) * instructionCount);
				if(instructions == NULL) cout << "Error allocating memory for instructions" << endl; 
					
				//Allocate memory for the heap
				pHeap = (heap* )malloc(sizeof(heap) * heapSize);
				if(pHeap == NULL) cout << "Error allocating memory for the heap" << endl; 

				//Allocate memory for the stack
				pStack = (stack* )malloc(sizeof(stack) * stackSize);
				if(pStack == NULL) cout << "Error allocating memory for stack" << endl;
			}	

			Process(string name, int lines, int id){
				time(&startTime); //Log when the process was started
				localtime_s(&timestamp, &startTime); //Turn epoch time to calendar time
				pname = name;
				pid = id;
				lineCount = lines;
				currLine = 1;
			}

			Process(string name, int id){
				time(&startTime); //Log when the process was started
				localtime_s(&timestamp, &startTime); //Turn epoch time to calendar time
				pname = name;
				pid = id;
				lineCount = rand() % (200 - 50 + 1) + 50; //picks a random linecount between 50 and 200
				currLine = 1;
			}

			Process(){}; //default Constructor

		private:
			heap* pHeap;				//Pointer for the heap
			stack* pStack;				//Pointer for the stack
			symbolTable* pSymbolTable;	//Pointer for the symbol table
			subroutine* pSubRoutine;	//Pointer for the subroutine
			library* libraries;			//Pointer for the libraries
			instruction* instructions; 	//Pointer for the lines of code/instructions of the process.
	};
}

#endif