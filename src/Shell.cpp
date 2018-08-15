#include "Shell.hpp"

Shell::Shell(const char *&paths){
    this->exit = false;
    this->paths = paths;
    set_default_name(); // set name member variable to 
    update_prompt();
    read_history(HIS); // read from .history and add it to memory
    printf("\033[1;33mThe \"EXIT\" command will exit shell.\n");
    queue_input(); // get user input
}

#ifdef CATCH_CONFIG_MAIN
bool
Shell::isExit() const{
    return this->exit;
}
#endif

void
Shell::setExit(){
    if(!this->exit) this->exit = true;
}

Shell &
Shell::instance(const char *paths){
    static Shell shell(paths);
    return shell;
}

void
Shell::reset_or_update_name(char *&name){
    if(name) strcat(strcpy(this->name, GREEN), name); // else copy new name to be name buffer
    else if(this->name) return; // if a name already exist and no local name is a nullptr return
    else set_default_name(); // if no arguments passed set name to be the default one
}

int
get_host(char *&host){
    return gethostname(host, HOST_NAME_MAX);
}

int
get_user(char *&user){
    return getlogin_r(user, HOST_NAME_MAX);
}

void
Shell::set_default_name(){
    char *user = new char[LOGIN_NAME_MAX], *host = new char[HOST_NAME_MAX];
    Affirm::pass_o_print(get_host, host, "gethostname");
    Affirm::pass_o_print(get_user, user, "getlogin_r");
   	strcpy(this->name, GREEN); // copy name color to name buffer
    strcat(this->name, strcat(strcat(strcat(user, "@"), strcat(host, NC)), ":")); // concat all to name member variable
    delete[] user;
    delete[] host;
}

void
Shell::update_prompt(char *name){
    reset_or_update_name(name);
    update_directory();
    set_prompt();
}

void
Shell::update_directory(){
    Affirm::_getcwd(this->dir);
    collapse_home(this->dir);
}

void
Shell::set_prompt(){
    strcpy(this->prompt, this->name);
    strcat(this->prompt, BLUE);
    strcat(this->prompt, this->dir);
    strcat(this->prompt, NC);
    strcat(this->prompt, "$ ");
    rl_set_prompt(this->prompt);
}

void 
Shell::collapse_home(char *&dir){
    char pattern[PATH_MAX];
    strcpy(pattern, "^.*[ \\t]*(");
    strcat(pattern, getenv("HOME"));
    strcat(pattern, ").*$");    
    Regex::replace(dir, pattern, "~", 2);
}

void
expand_environment(char *&string, const char *exp, const char *env){
    char *env_value = secure_getenv(env);
    if(env_value) Regex::replace(string, exp, env_value, 3);
}

void
Shell::expand_home(char *&dir){
    Regex::replace(dir, "^.*[ \\t]*(~).*$", getenv("HOME"), 2);
}

char *
Shell::get_user_input() const{
    // return readline(rl_prompt); // does not work properly ?!?
    return readline(this->prompt);
}

void
Shell::update_history(char *&input) const{
    add_history(input);
	write_history(HIS);
}

void
Shell::queue_input(){
    while(!this->exit){
        char *input = get_user_input(); // name user for next input
        update_history(input); // add input to history
        Queue container = Queue(input); // parse input into bitsize commands
        iterate_through(container); // deligate commands to be iterated through
    }
}

void
Shell::iterate_through(Queue &container){
    if(container.empty()) return; // if there is no commands in queue exit recursion
    char *cmd = container.pop(); // get the next command in queue
    Regex::replace(cmd, "^[ \\t]*(.*)[ \\t]*$", 2, 1);
    command_manager(cmd);
    iterate_through(container);
}

void
Shell::command_manager(char *&cmd){
    if(Regex::match(cmd, "^EXIT$"))
        this->exit = true;
    else if(Regex::match(cmd, "^PS1=\"?([^\"\\n\\r]+)\"?$"))
        ps1_controller(cmd, "^PS1=\"?([^\"\\n\\r]+)\"?$");
    else if(Regex::match(cmd, "^[A-Z]+=\"?([^\"\\n\\r]+)\"?$"))
        environment_controller(cmd);
    else if(Regex::match(cmd, "^cd (.*)$"))
        directory_controller(cmd, "^cd (.*)$");
    else if(Regex::match(cmd, "^.*\\$([A-Z]+).*$")){
        char *env;
        strcpy(env, cmd);
        Regex::replace(env, "^.*\\$([A-Z]+).*$", 2, 1);        
        expand_environment(cmd, "^.*(\\$([A-Z]+)).*$", env);
        printf("%s\n", cmd);
    }
    else
        /*temporary lines*/
        printf("%s\n", cmd); // print input to screen
        /*temporary lines*/
}
 
void
Shell::ps1_controller(char *&cmd, const char *exp){
    Regex::replace(cmd, exp, 2, 1);
    update_prompt(cmd);
}

void
Shell::environment_controller(char *&cmd){
    Affirm::pass_o_print(putenv, cmd, "putenv");
}

void
Shell::directory_controller(char *&cmd, const char *exp){
    Regex::replace(cmd, exp, 2, 1);
    Affirm::pass_o_print(chdir, cmd, "chdir");
    update_prompt();
}

Shell::~Shell(){
    delete[] this->name;
    delete[] this->dir;
}