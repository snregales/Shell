#include "Regex.hpp"
//TODO: Refactor both replace and its overload and math
bool
Regex::match(char *&string, const char *pattern){
        regex_t re;
        Affirm::_regcomp(re, pattern, REG_EXTENDED|REG_NOSUB); // create a regex pattern that regexec can use
        int status = Affirm::_regexec(re, string, (size_t) 0, NULL, 0); // execute regular expression
        regfree(&re); // clean up, free regex_t created
        return !status ? true : false; // if status is zero than there is a match 
}

void 
Regex::replace_string(char *&string, int start, size_t size){
        strncpy(string, &string[start], size); //copy substing of "string" into string container
        string[size] = '\0'; // add a null termination to string container
}

void
Regex::replace(char *&string, const char *pattern, int groups, int group){
        regex_t re;
        regmatch_t pmatch[groups];
        Affirm::_regcomp(re, pattern, REG_EXTENDED); // create a regex pattern that regexec can use
        int status = Affirm::_regexec(re, string, groups, pmatch, 0); // execute regular expression
        regfree(&re); // clean up, free regex_t created
        if(!status) // if there is a match replace string
                replace_string(
                        string, 
                        pmatch[group].rm_so, 
                        (size_t) (pmatch[group].rm_eo - pmatch[group].rm_so)
                );
}

void 
Regex::replace_string(char *&string, const char *&replacer, regmatch_t &pmatch){
        char match[strlen(string)+strlen(replacer)+1]; // create a container big enough to hold both string and replacer
        size_t stop = (size_t) pmatch.rm_so;
        strncpy(match, string, stop); // copy the begining of the string to the start point of matched substring
        match[stop] = '\0'; // add null termination to container to insure no other random characters are included
        strcat(match, replacer); // append substring replacer to container
        strcat(match, &string[pmatch.rm_eo]); // append the rest of string
        strcpy(string, match); // copy temperary container "match" to string
}

void
Regex::replace(char *&string, const char *pattern, const char *replacer, int groups){
        regex_t re;
        regmatch_t pmatch[groups];
        Affirm::_regcomp(re, pattern, REG_EXTENDED);
        int status = Affirm::_regexec(re, string, groups, pmatch, 0);
        regfree(&re);
        if(!status)
                replace_string(
                        string, 
                        replacer, 
                        pmatch[1] // will need to be more abstract
                );
    
}