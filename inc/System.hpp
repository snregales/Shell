#pragma once

#include "Affirm.hpp"
#include "Parser.hpp"

#include <signal.h>
#include <string>
#include <vector>

class System{

/*constructors*/
public: System(char **& argv);
public: System(std::vector<const char *> &paths, char **& argv);
public: System(char *& paths, char **& argv);

#ifndef CATCH_CONFIG_MAIN
protected: 
#else
public:
#endif
    void set_paths();
    void set_paths(char *& paths);
    void fork_execv(char **& argv);
    /*wrapper for std::vector::push that parser::splice can use*/
private: static void push(char *&path);

/*destructor*/
public: ~System();
};
