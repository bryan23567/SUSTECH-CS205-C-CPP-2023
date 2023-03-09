#pragma once
#include <stdbool.h>
bool isANumber(char *num);
bool isInt(char *num);
bool isDecimal(char *num);
bool isScientific(char *num);
char *deleteUnimportantChar(char *num);
char *insertDotAtIndex(char *num, int index);
char *addingMoreTrailingZero(char *before, int howMany);
char *delete_char(char *str, int k);