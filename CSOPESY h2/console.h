#pragma once
#ifndef consoleH
#define consoleH

#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>

#include "process.h" //This is for the process class

using std::left;
using std::right;
using std::setw;
using std::map;
using std::list;
using std::string;
using std::cout;
using std::endl;
using process::Process;

namespace console{
	class Console{
		public:
			Process process;			//The process associated with this console.
			bool exit = false;
			bool mainConsole = false; 	//just a flag that this is the main console. 	
			Console* handoff = NULL; 	//something that tells the main program what console to switch to

			virtual void drawHeader(){
				char time[30];
				strftime(time, sizeof(time), "%m/%d/%Y, %I:%M:%S %p", &process.timestamp);
				cout << "    __   __   __   __   __   __   __" << endl;
				cout << "---|__|-|__|-|__|-|__|-|__|-|__|-|__|---" << endl;
				cout << process.pname << endl;
				cout << "Time created: " << time << endl;
				cout << "You are in the console for " << process.pname << endl;
				cout << "====================================================================" << endl;
				cout << left << setw(30) << "Total lines of code: " << setw(15) << right << process.lineCount << endl;
				cout << left << setw(30) << "Current line: " << setw(15) << right << process.currLine << endl <<endl;

			};

			virtual void printProcesses(){cout << "Type \"help\" or \"?\" for a list of commands." << endl << endl;};
			
			virtual void handleInput(string s);

			Console(){ //For creating main console
				process = NULL;
			}; 		

			Console(Process p){ //For consoles for processes
				process = p;
			}; 		

			void clear(){
				system("cls");
				drawHeader();
				printProcesses();
			}
		private:
			void cmdHelp(){
				cout << "For more information on a specific command, type it out (i.e. type only 'screen' and enter)" << endl;
				cout << left << setw(15) << "clear" << setw(10) << "" << "Clear the screen while leaving the header." << endl;
				cout << left << setw(15) << "exit" << setw(10) << "" << "Exit the program." << endl;
			}
	};

	class MainConsole : public Console{
		public:
			list<Console> consoleList; //for iterating over the consoles
			map<int, Console*> consoleMap; //not really used yet since the current queries uses the name

			void handleInput(string s);
			void printProcesses();

			void drawHeader(){
				cout << "    ______   ______   ______   ______   ______   ______   ______" << endl;
				cout << "---|______|-|______|-|______|-|______|-|______|-|______|-|______|---" << endl;
				cout << "   ______   ______     ___   _______  ________   ______  ____  ____" << endl;
				cout << " .' ___  |.' ____ \\  .'   `.|_   __ \\|_   __  |.' ____ \\|_  _||_  _|" << endl;
				cout << "/ .'   \\_|| (___ \\_|/  .-.  \\ | |__) | | |_ \\_|| (___ \\_| \\ \\  / /" << endl;
				cout << "| |        _.____`. | |   | | |  ___/  |  _| _  _.____`.   \\ \\/ /" << endl;
				cout << "\\ `.___.'\\| \\____) |\\  `-'  /_| |_    _| |__/ || \\____) |  _|  |_" << endl;
				cout << " `.____ .' \\______.' `.___.'|_____|  |________| \\______.' |______|" << endl << endl;
				cout << "Hello, welcome, to CSOPESY command line!" << endl;
				cout << "Created by: Asnan, Pilea, De la Torre" << endl << endl << endl;
			};

			MainConsole(){
				//add main to the consolemap but hide it from the list
				consoleMap.insert({0, this});

				mainConsole = true;
				addNewProcess("mov");

				addNewProcess("load.exe");

				drawHeader();
				printProcesses();
			}
		private:
			void cmdHelp(){
				cout << "For more information on a specific command, type it out (i.e. type only 'screen' and enter)" << endl;
				cout << setw(15) << "clear" << setw(10) << "" << "Clear the screen while leaving the header." << endl;
				cout << setw(15) << "exit" << setw(10) << "" << "Exit the program." << endl;
				cout << setw(15) << "initialize" << setw(10) << "" << "Does nothing for now" << endl;
				cout << setw(15) << "screen" << setw(10) << "" << "Start or open a console for a process." << endl;
				cout << setw(15) << "scheduler-test" << setw(10) << "" << "Does nothing for now" << endl;
				cout << setw(15) << "scheduler-stop" << setw(10) << "" << "Does nothing for now" << endl;
				cout << setw(15) << "report-util" << setw(10) << "" << "Does nothing for now" << endl;
			}

			void cmdScreenHelp(){
				cout << "usage: screen [-s | -r] <process name>" << endl;
				cout << "Options:" << endl;
				cout << "\t" << "-s" << "\t\t\t" << "Start a new process with the process name." << endl;
				cout << "\t" << "-r" << "\t\t\t" << "Redraw/resume session of a process" << endl;
			}
			Console* addNewProcess(string name){ //func for adding a new process
				
				//THIS KEY SYSTEM WILL BREAK IF THE LIST GETS SMALLER IN RUNTIME, GET THE MAX() + 1 INSTEAD
				int newPID = consoleList.size() + 1;
				
				consoleList.push_back(Console(Process(name, newPID))); //add a new console to the start of the console list with the associated process
				consoleMap.insert({newPID, &consoleList.back()}); 

				return &consoleList.back(); //return the created console
			}
			Console* searchList(string name){ //used to search through the console list
				for(Console &c : consoleList){
					if(c.process.pname == name) return &c; //If it finds a matching process name, return the address of the console
				}
				cout << "[SearchList] could not find process name \"" << name << "\"" << endl;
				return NULL;
			}
	};

	void MainConsole::printProcesses(){
		char time[30];
		
		cout << left << setw(4) << "PID";
		cout << left << "\t" << setw(15) << "Name";
		cout << left << "\t" << setw(30) << "Time started";
		cout << left << "\t" << setw(15) << "Current Line";
		cout << left << "\t" << setw(15) << "Total Lines";
		cout << left << "\t" << setw(17) << "Progress" << endl;

		for(Console c : consoleList){
			strftime(time, sizeof(time), "%m/%d/%Y, %I:%M:%S %p", &c.process.timestamp);

			cout << left << setw(4) << c.process.pid;
			cout << left << "\t" << setw(15) << c.process.pname;
			cout << left << "\t" << setw(30) << time;
			cout << left << "\t" << setw(15) << c.process.currLine;
			cout << left << "\t" << setw(15) << c.process.lineCount;
			cout << right << "\t" << setw(3) << (c.process.currLine) / (c.process.lineCount);
			cout << left << "% [#---------]" << endl;
		}
		cout << endl;

		cout << "Type \"help\" or \"?\" for a list of commands." << endl << endl;
	}

	//HANDLING INPUT FOR THE BASE CONSOLE CLASS
	void Console::handleInput(string s){
		string placeholder = " command recognized. Doing something.";
		string invalid = "\" is not a recognized command";

		char* tokenizer = strtok(&s[0], " ");
		list<string> tokens;

		while(tokenizer != NULL){
			tokens.push_back(tokenizer);
			tokenizer = strtok(NULL, " "); // increment the tokenizer
		}
		
		if(tokens.front() == "help" || tokens.front() == "?"){
			cmdHelp();
		}
		else if(tokens.front() == "exit"){
			exit = true;
		}
		else if(tokens.front() == "clear"){
			system("cls");
			drawHeader();
			printProcesses();
		}		
		else{
			cout << "\"" << tokens.front() << invalid << endl;
		}
	}

	//HANDLING INPUT FOR THE MAIN CONSOLE
	void MainConsole::handleInput(string s){
		string placeholder = " command recognized. Doing something.";
		string invalid = "\" is not a recognized command";

		char* tokenizer = strtok(&s[0], " ");
		list<string> tokens;

		while(tokenizer != NULL){
			tokens.push_back(tokenizer);
			tokenizer = strtok(NULL, " "); // increment the tokenizer
		}
		
		if(tokens.front() == "help" || tokens.front() == "?"){
			cmdHelp();
		}
		else if(tokens.front() == "exit"){
			exit = true;
		}
		else if(tokens.front() == "clear"){
			clear();
		}
		else if(tokens.front() == "initialize"){
			cout << s << placeholder << endl;
		}
		else if(tokens.front() == "screen"){
			//check for the flags
			tokens.pop_front(); //iterate to the next token, which is the flag (-s and -r)

			if(tokens.front() == "-s" || tokens.front() == "-r"){
				if(tokens.front() == "-s"){
					tokens.pop_front(); //iterate to the process name;
					if(!tokens.empty()){ //check if the string is null
						handoff = addNewProcess(tokens.front());
						cout << handoff;
						clear();
					}
					else 
						cmdScreenHelp();
				}
				else{
					tokens.pop_front(); //iterate to the process name;
					if(!tokens.empty()){ //check if the string is null
						handoff = searchList(tokens.front());
						if(handoff)	clear(); //If it finds something, clear the screen. If not, keep the screen.
					}
					else 
						cmdScreenHelp();
				}
			}
			else
				cmdScreenHelp();
		}
		else if(tokens.front() == "scheduler-test"){
			cout << s << placeholder << endl;
		}
		else if(tokens.front() == "scheduler-stop"){
			cout << s << placeholder << endl;
		}
		else if(tokens.front() == "report-util"){
			cout << s << placeholder << endl;
		}
		else{
			cout << "\"" << tokens.front() << invalid << endl;
		}
		
	}
}

#endif