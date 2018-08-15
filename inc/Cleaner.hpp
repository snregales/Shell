#pragma once

#include <string.h>
#include <string>
#include "Regex.hpp"

#define SPACE_DELIM " \t\n\r"

struct Cleaner{
    static char *cleaner(char *dirty);
    /*remove unwanted spaces characters from data and copy cleaned data back into container*/
    static void _cleaner(char *&str);
};