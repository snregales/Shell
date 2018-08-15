#include "Affirm.hpp"

void /*print error to the screen*/
Affirm::print(bool failed, const char *module){
    if(failed) perror(module);
}

void /*print error to screen and signal exit to all decendent of parrent thread with status failure*/
Affirm::print_exit(bool failed, const char *module){
    print(failed, module);
    if(failed) exit(EXIT_FAILURE);
}

void /*print error to screen and abruptly terminate all decendent of running parrent thread with status failure*/
print__exit(bool failed, const char *module){
    Affirm::print(failed, module);
    if(failed) _exit(EXIT_FAILURE);
}

void
Affirm::_execv(std::vector<const char *> &paths, char**& argv){
    for(auto path: paths) 
        print(execv(path, argv) && errno != ENOENT, "execv");
    print_exit(true, "execv");
}

pid_t
Affirm::_fork(){
    pid_t pid = fork();
    print(pid < 0, "fork");
    return pid;
}

pid_t
Affirm::_waitpid(pid_t &child, int status){
    pid_t pid;
    print((pid = waitpid(child, &status, 0)) < 0, "waitpid");
    return pid;
}

int
Affirm::_open(const char *& path, bool read){
    int fd;
    if(read) fd = open(path, O_RDONLY);
    else fd = open(path, O_RDWR | O_CREAT | O_TRUNC | S_IRWXU, 0644);
    print(fd < 0, "open");
    return fd;
}

int
Affirm::_dup2(int newfd, int oldfd){
    int fd = dup2(oldfd, newfd);
    print(fd < 0, "dup2");
    return fd;
}

void
Affirm::_getcwd(char *&dir){
    /*get current working directory and store it in user buffer, if this fails print error on screen*/
    print(!getcwd(dir, PATH_MAX), "getcwd");
}

void
Affirm::_regcomp(regex_t &re, const char *&pattern, int flags){
    bool failed = regcomp(&re, pattern, flags) != 0;
    print(failed, "regcomp");
    if(failed) regfree(&re);
}

int
Affirm::_regexec(regex_t &re, char *&string, size_t nmatches, regmatch_t *pmatches, int flags){
    int status = regexec(&re, string, nmatches, pmatches, flags);
    print(
        status != 0 && status != REG_NOMATCH, 
        "regexec");
    return status;
}
