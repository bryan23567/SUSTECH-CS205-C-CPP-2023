#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "validation.h"
bool isANumber(char *num)
{
    int count_dot = 0;
    int count_E = 0;
    int count_plus = 0;
    int count_minus = 0;
    int loc_e = 0x3f3f3f3f;
    if (strlen(num) < 1)
    {
        return false;
    }

    if (strlen(num) == 1 && (num[0] < '0' || num[0] > '9'))
    {
        return false;
    }

    for (int i = 0; i < strlen(num); i++)
    {
        switch (num[i])
        {
        case '-':

            if (i == 0)
            {
                break;
            }
            else
            {
                if ((num[i - 1] == 'e' || num[i - 1] == 'E') && count_minus == 0)
                {
                    count_minus++;
                    break;
                }
                else
                {
                    return false;
                }
            }

        case '+':
            if (i == 0)
            {
                break;
            }
            else
            {
                if ((num[i - 1] == 'e' || num[i - 1] == 'E') && count_plus == 0)
                {
                    count_plus++;
                    break;
                }
                else
                {
                    return false;
                }
            }
            break;
        case '.':
            count_dot++;
            if (i == 0 || count_dot > 1 || i == strlen(num) - 1 || (num[i - 1] < '0' || num[i - 1] > '9') || (num[i + 1] < '0' || num[i + 1] > '9') || i > loc_e)
            {
                return false;
            }

            break;
        case 'e':
            count_E++;
            loc_e = i;
            if (count_E > 1 || i == 0)
            {
                return false;
            }

            break;
        case 'E':
            count_E++;
            loc_e = i;
            if (count_E > 1 || i == 0)
            {
                return false;
            }
            num[i] = 'e';
            break;
        default:
            if (num[i] < '0' || num[i] > '9')
                return false;
            break;
        }
    }
    return true;
}

bool isInt(char *num)
{
    while (*num)
    {
        if (*num < '0' || *num > '9')
        {
            return false;
        }
        *num++;
    }
    return true;
}
bool isDecimal(char *num)
{
    while (*num)
    {
        if ((*num < '0' || *num > '9') && *num != '.')
        {

            return false;
        }
        *num++;
    }
    return true;
}
bool isScientific(char *num)
{
    while (*num)
    {
        if ((*num < '0' || *num > '9') && (*num != '.' || *num != 'e'))
        {
            return false;
        }
        *num++;
    }
    return true;
}

char *deleteUnimportantChar(char *num)
{
    int pos = 0;
    if (num[0] == '+') // delete the leading plus in a
    {
        num[0] = '0';
    }
    for (int i = 0; i < strlen(num); i++)
    {
        if (num[i]!= '0')
        {
            break;
        }
        pos++;
    }

    num = num + pos;
    return num;
}