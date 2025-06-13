/*
Created by the group: Asnan, Pilea, De la Torre
This c++ file is a show-of-concept for console designs.
 


*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>

#include "process.h" //This is for the process class
#include "console.h" //For the console class

using std::cout;
using std::cin;
using process::Process;
using console::Console;
using console::MainConsole;

int main(){
	MainConsole mainConsole;
	Console* console = &mainConsole; //holds the current active console, initialized to main Menu as it's the root
	Console* temp = NULL;
	
	string input; //input variable
	string path = ">root/>";

	while(!(console->exit)){
		if(console->mainConsole)
			cout << path;
		else
			cout << path << console->process.pname << "/>";

		std::getline(cin, input);
		console->handleInput(input);
		if(console->handoff != NULL){
			temp = console->handoff;
			console->handoff = NULL; //switch the handoff back to null
			console = temp; //switch the current console to the handoff value
			console->clear();
		}
		else if(console->exit && !(console->mainConsole)){
			console->exit = false; //set that console's exit to false or it never let us back in
			console = &mainConsole; //set us back to main console
			console->clear();
		}
	}	

	//trash collection
	//go through the list of consoles and dealloc
	//delete list

	//go through the list and dealloc
	//delete list
	//go through the map and dealloc
	//delete map

	return 0;
}
