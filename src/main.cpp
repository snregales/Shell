#include "testing.hpp"

#ifndef CATCH_CONFIG_MAIN

#include "main.hpp"

using namespace std;

/*
You may not use the getenv command to get the PATH variable.  
You may use it otherwise.
*/
int
main(int argc, const char **argv, const char **env){
    char *string;
    for(int i=0;env[i]!=NULL;i++){  
        string = strdupa(env[i]);
        if(Regex::match(string, "^PATH=(.*)$")){
            Shell::instance(env[i]);
            break;
        }
    }
}

/*
this can be done differently with the same result as above
int
main(int argc, const char **argv){
    char *path = getenv("PATH");
    Shell::instance(path);
}
*/

#endif