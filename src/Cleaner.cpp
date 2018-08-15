#include "Cleaner.hpp"

char *
Cleaner::cleaner(char *dirty){
    _cleaner(dirty); // send dirty data to be cleaned
    return dirty; // cleaned 
}

void
Cleaner::_cleaner(char *&str){
    strcpy(str, strtok(str, SPACE_DELIM)); 
}