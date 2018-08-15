#pragma once

#include <string.h>

#define SPACE_DELIM " \t\n\r"

struct Parser{
    template<class T>
    static void splice(char *&str, T *func, const char *delim = SPACE_DELIM){
        char *token = strtok(str, delim); // initialize tokken to the first tokken in the list
        while(token){ // keep looping while there is still tokens being retrieve from str  
            func(token); // run containers version of push, to add token to container 
            token = strtok(NULL, delim); // get next tokken
        }
        delete token;
    }
};