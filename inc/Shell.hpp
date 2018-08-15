#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Queue.hpp"
#include "Affirm.hpp"
#include "Regex.hpp"

#define HIS "./bin/.history"
#define NAME HOST_NAME_MAX + LOGIN_NAME_MAX
#define PROMPT NAME + PATH_MAX
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define NC "\033[1;0m"

class Shell{
/*variables*/
private: char *name = new char[NAME]; // pointer to a container that holds user@host 
private: char *dir = new char[PATH_MAX]; // pointer to a container that holds the current working directory
private: char prompt[PROMPT]; // container that holds the terminal name
private: const char *paths; // holds all paths that is used by unistd group libary fuctions
private: bool exit;

/*setters and getters*/
#ifdef CATCH_CONFIG_MAIN
public: bool isExit() const;
#endif
public: void setExit();
//TODO: extract controllers out to their own class
/*constructor*/
private: Shell(const char *&paths);

/*accesser to the Shell class, it will create a object instance only if none is already created*/
public: static Shell &instance(const char *paths);
/*write incoming paramater to .history file in ./bin directory*/
private: void update_history(char *&input) const;
/*reset to default name or update name to users desire, arguments default nullptr and green*/
public: void reset_or_update_name(char *&name);
/*set default name example user@host:*/
private: void set_default_name();
/*name user for input*/
protected: char *get_user_input() const;
protected: void update_prompt(char *name = nullptr);
protected: void update_directory();
/*update name with the current directory path*/
protected: void set_prompt();
/*collapse $HOME sub-directory within a directory to "~" symbol*/
private: void collapse_home(char *&dir);
/*expand "~" symbol (within a directory) to be expressed as $HOME (sub-)directory*/
private: void expand_home(char *&dir);
/*retrieve, archive and queue user input*/
protected: void queue_input();
/*iterate through elements in container and deligate the elment to reader*/
protected: void iterate_through(Queue &container);
/*read and deligate cmd to be processed and/or executed*/
protected: void command_manager(char *&cmd);
/*process PS1 command*/
private: void ps1_controller(char *&cmd, const char *exp);
/*sets environment variable*/
private: void environment_controller(char *&cmd);
/*change current working directory to the one commanded by user 
and update dir member variable*/
private: void directory_controller(char *&cmd, const char *exp);

/*destructor*/
public: ~Shell();
};

