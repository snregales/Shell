#pragma once

#include <unistd.h> // exec
#include <errno.h> // error types
#include <sys/types.h> // fork, open, waitpid
#include <sys/stat.h> // open
#include <fcntl.h> // open, pipe
#include <sys/wait.h> // waitpid
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <vector>

struct Affirm{
    // TODO: refactor code to be templated
    static void print(bool failed, const char *module);
    static void print_exit(bool failed, const char *module);
    template<class F, class A>
    static void pass_o_print(F *func, A *&arg, const char *module){
        print(func(arg) < 0, module);
    }
    template<class F, class A>
    static void pass_o_die(F *func, A *&arg, const char *module){
        bool failed = func(arg) < 0;
        print(failed, module);
        if(failed) exit(EXIT_FAILURE);
    }
    static void _execv(std::vector<const char*> &paths, char **&argv);
    static pid_t _fork();
    static pid_t _waitpid(pid_t &child, int status);
    static int _open(const char *&path, bool read = false);
    static int _dup2(int newfd, int oldfd);
    static void _getcwd(char *&dir);
    static void _regcomp(regex_t &re, const char *&pattern, int flags);
    static int _regexec(regex_t &re, char *&string, size_t nmatches, regmatch_t *pmatches, int flags);
};