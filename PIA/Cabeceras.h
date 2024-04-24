#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <regex.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#if  defined(__linux__)
    #include <stdio_ext.h>
#endif

#define MAX_BYTES 1000