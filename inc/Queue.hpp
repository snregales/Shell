#pragma once

#include "testing.hpp"

#include <queue>
#include <string.h>
#define SPACE_DELIM " \t\n\r"

class Queue{
/*variables*/
// private: std::queue<char*> container; // FIFO container for holding users one line multicommands
private: char *next;

/*constructors*/
public: Queue(char *&input); // by reference
#ifndef CATCH_CONFIG_MAIN 
protected: 
#else
public:
    Queue();
    std::queue<char*>::size_type size();
#endif
    /*deligates how user input should be parsed*/
    void manager(char *&input);
/*returns if command member variable container is empty*/
public: bool empty() const;
/*wrapper function for the std::queque::push fuction*/
private: static void push(char *&command);
/*remove and returns next command in queque*/
public: char *&pop();
/*destructor*/
public: ~Queue();
};