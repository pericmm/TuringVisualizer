#ifndef __STRIP_H__
#define __STRIP_H__
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include "macros.h"



struct Node{
	char c;
	Node* left;
	Node* right;
};

struct Strip{
	Node* headScreen = NULL;
	Node* headProgram = NULL;
	std::string q=START;

	Strip() {}

	void insertFront(char c){
		Node* newNode = new Node();
		newNode->c = c;
		newNode->left = NULL;
		newNode->right = headScreen;
		headScreen = newNode;
	}
	void insertBack(char c){
		Node* newNode = new Node();
		newNode->c = c;
		newNode->right = NULL;
		if (headScreen == NULL) {
			newNode->left = NULL;
			headScreen = newNode;
			headProgram = newNode;
			return;
		}
		Node* temp = headProgram;
		while (temp->right != NULL) {
			temp = temp->right;
		}
		newNode->left = temp;
		temp->right = newNode;
	} 
	void print(){
		Node* iterator=headScreen;
		for(int i=0; i<SCREEN_SIZE/2; i++){
			if(iterator != NULL){
				if(iterator == headProgram){
					std::cout<<"\033[1;31m";
					std::cout<<'\b'<<'[';
					std::cout<<iterator->c<<']';
					std::cout<<"\033[0m";
				}else {
					std::cout<<iterator->c<<'|';
				}
				iterator=iterator->right;
			}
			else{
				std::cout<<EMPTY<<'|';
			}
		}
		std::cout<<'\b'<<std::endl;
	}
	void screenLeft(){
		if(headScreen->left == NULL)
			insertFront(EMPTY);
		else
			headScreen = headScreen->left;
	}
	void screenRight(){
		if(headScreen->right == NULL)
			insertBack(EMPTY);
		
		headScreen=headScreen->right;
	}
	void nextStep(std::map<std::string, std::map<char, std::string>>& program){
		std::string temp = program[q][headProgram->c];
		headProgram->c = temp[0];
		switch (temp[2]) {
			case 'R':
				if (headProgram->right==NULL) 
					insertBack(EMPTY);
				headProgram = headProgram->right;
				break;
			case 'L':
				if(headProgram==headScreen)
					screenLeft();
				headProgram = headProgram->left;
				break;
			case 'P':
			case 'S':
				break;
			default:
   				system("/bin/stty cooked");
				exit(EXIT_FAILURE);
		}
		q = temp.substr(4);
	}
};
#endif