#pragma once
#include <stdbool.h>
bool isANumber(char *num);
bool isInt(char *num);
bool isDecimal(char *num);
bool isScientific(char *num);
char* deleteUnimportantChar(char *num);