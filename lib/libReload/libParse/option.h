#include "lib.h"


void   error_entry_message();

int    read_entry(char *rln);

int    isoption_ok(char *option, char *val);

int    read_option(char *option, char *val);

int    char_isnum(char c);

int    if_null_entry(char *entry);

int    check_option(int argc, char **argv);
