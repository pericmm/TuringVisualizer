#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
#include <utility>

#include "strip.h"
#include "macros.h"
#include "TUI-file-picker/filePicker.hpp"


std::map<std::string, std::map<char, std::string>> program;

void arrowHandler(Strip& strip){
	getchar();
	switch(getchar()){
   		case 66:
			strip.nextStep(program);
   			break;
   		case 67:
			strip.screenRight();
   			break;
   		case 68:
			strip.screenLeft();
   			break;
   		default:
			std::cout<<"\x1b[2K";
   			system ("/bin/stty cooked");
   			exit(EXIT_FAILURE);
   	}
}

void eventHandler(Strip& strip){
	system("/bin/stty raw");
   	switch(getchar()){
   		case NEXT:
			strip.nextStep(program);
			std::cout<<"\x1b[2K\b";
   			system("/bin/stty cooked");
   			break;
   		case RIGHT:
			strip.screenRight();
			std::cout<<"\x1b[2K";
   			system("/bin/stty cooked");
   			break;
   		case LEFT:
			strip.screenLeft();
			std::cout<<"\x1b[2K";
   			system("/bin/stty cooked");
   			break;
		case 27:
			arrowHandler(strip);
			std::cout<<"\x1b[2K";
			system("/bin/stty cooked");
   			break;
   		default:
			std::cout<<"\x1b[2K";
   			system ("/bin/stty cooked");
   			exit(EXIT_FAILURE);
   	}
}


void loadVariables(Strip& strip, std::string input){
	for(char c:input){
		strip.insertBack(c);
	}
}
void loadProgram(Strip& strip, std::string inputFile){
	std::string line;
	std::ifstream ReadFile(inputFile);
	while (true){ 
		getline(ReadFile,line);
		if(line[0]!='#' && !line.empty()) break;
	}
	loadVariables(strip, line);
	while(getline(ReadFile,line)){
		if(line[0]=='#' || line.empty()) continue;
		int n=line.find('|');
		program[line.substr(0,n)].insert(std::make_pair((char)line[n+1], line.substr(n+3,line.size()-1)));
	}
  	ReadFile.close();
}


int main(int argc, char* argv[]){
	Strip strip;
	loadProgram(strip, filePicker("Examples"));
	while(1){
		std::cout<<"\x1b[2J"<<"\x1b[H"; //erase screen, return cursor to begining
		strip.print();
		std::cout<<strip.q<<'|'<<strip.headProgram->c<<'|'<<program[strip.q][strip.headProgram->c]<<std::endl;

		if(strip.q == TERMINAL)
			exit(EXIT_SUCCESS);
   		eventHandler(strip);

		
   	}
}


