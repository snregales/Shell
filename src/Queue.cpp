#include "Queue.hpp"
#include "Parser.hpp"
#include <stdio.h>

std::queue<char*> container; // FIFO container for holding users one line multicommands

Queue::Queue(char *&input){
    this->next = nullptr;
    manager(input);
}

#ifdef CATCH_CONFIG_MAIN

/*these following code are only for testing*/
Queue::Queue(){
    this->next = nullptr;
}

std::queue<char*>::size_type
Queue::size(){
    return container.size();
}

#endif

void
Queue::manager(char *&input){
    Parser::splice(input, Queue::push, ";");
}

bool
Queue::empty() const {return container.empty();}

void
Queue::push(char *&command){container.push(command);}

char *&
Queue::pop(){
    if(!empty()){
        this->next = container.front(); // set a pointer to the next element in queue
        container.pop(); // remove next element from queque
    }
    return next; // return the pointer holding the next element
}

Queue::~Queue(){}