#include <regex.h>
#include <string.h>
#include "Affirm.hpp"

namespace Regex {
    /* "string" is the string being passed by the user
    "pattern" is the regular expression pattern used to search the string */
    /* "match" takes a string and a pattern and see if pattern exists with the string */
    bool match(char *&string, const char *pattern);
    /* "replace" takes a string and a pattern and if pattern is with in string
    "replace" will replace string with the selected group within the pattern
    "groups" is the amount of groups in the regular expression
    "group" is the group that you want to capture and replace */
    void replace(char *&string, const char *pattern, int groups, int group);
    /* given a string and regular expression pattern and a replacer string,
    replace will substitute the group given with the replacer string */
    void replace(char *&string, const char *pattern, const char *replacer, int groups);
    /* "replace_string" takes a string and replaces it with a substring of the string itself
    "start" is the start point of the substring within the string
    "size" is the length of the substring being captured */
    void replace_string(char *&string, int start, size_t size);
    /* replace_string will substitute section given by the match pointers pmatch
    with the given string replacer */
    void replace_string(char *&string, const char *&replacer, regmatch_t &pmatch);
}