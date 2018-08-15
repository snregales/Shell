#include "System.hpp"

std::vector<const char *> paths; // container holding all the paths that execv will iterate through

System::System(char **& argv){
    set_paths();
    fork_execv(argv);
}

System::System(char *&routs, char **& argv){
    set_paths(routs);
    fork_execv(argv);
}

System::System(std::vector<const char *> &routs, char **& argv){
    paths = routs;
    fork_execv(argv);
}

void
System::set_paths(){
    char *paths = getenv("PATH");
    set_paths(paths);
}

void
System::push(char *&path){
    paths.push_back(std::string(path).c_str());
}

void
System::set_paths(char *&routs){
    Parser::splice(routs, System::push, ":");
}

void
sigchld_handler(int signal){
	printf("killing process %d\n", getpid());
	_exit(EXIT_FAILURE);
}

void 
sigaction_setup(struct sigaction sa){
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
}

void 
System::fork_execv(char**& argv){
	int status; pid_t child;
	struct sigaction sa; sigaction_setup(sa); 
	if((child = Affirm::_fork()) == 0){
        Affirm::_execv(paths, argv);
	}else Affirm::_waitpid(child, status);
}
