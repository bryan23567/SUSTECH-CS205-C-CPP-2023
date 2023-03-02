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
        if (*num < '0' || *num > '9' && !(num[0] == '-' || num[0] == '+'))
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
        if ((*num < '0' || *num > '9') && *num != '.' && !(num[0] == '-' || num[0] == '+'))
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
        if ((*num < '0' || *num > '9') && (*num != 'e' && *num != '.'))
        {
            return false;
        }
        *num++;
    }
    return true;
}

char *deleteUnimportantChar(char *num)
{
    bool sign = false;
    int pos = 0;
    if (num[0] == '-')
    {
        num = num + 1;
        sign = true;
    };

    if (strlen(num) > 2 && num[0] == '0' && num[1] == '.')
    {
        if (sign)
        {
            char *res_new = (char *)malloc(sizeof(char) * (strlen(num) + 2));
            res_new[0] = '-';
            for (int i = 0; i < strlen(num); i++)
            {
                res_new[i + 1] = num[i];
            }
            res_new[strlen(num) + 1] = '\0';
            return res_new;
        }
        return num;
    }

    if (num[0] == '+') // delete the leading plus in a
    {
        num[0] = '0';
    }
    for (int i = 0; i < strlen(num); i++)
    {
        if (num[i] != '0')
        {
            break;
        }
        pos++;
    }

    num = num + pos;
    if (sign)
    {
        char *res_new = (char *)malloc(sizeof(char) * (strlen(num) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(num); i++)
        {
            res_new[i + 1] = num[i];
        }
        res_new[strlen(num) + 1] = '\0';
        return res_new;
    }
    return num;
}

char *insertDotAtIndex(char *num, int index)
{
    char *result = (char *)malloc(sizeof(char) * (strlen(num) + 1));
    char *resultHelp = (char *)malloc(sizeof(char) * (strlen(num) + 1));
    int i;
    for (i = 0; i < index; i++)
    {
        result[i] = num[i];
    }
    result[i] = '.';
    for (++i; i < strlen(num) + 1; i++)
    {
        result[i] = num[i - 1];
    }
    snprintf(resultHelp, strlen(num) + 2, result);
    return resultHelp;
}

char *addingMoreTrailingZero(char *before, int howMany)
{
    char *result = (char *)malloc(sizeof(char) * (strlen(before) + howMany));
    char *resultHelp = (char *)malloc(sizeof(char) * (strlen(before) + howMany));
    int i;
    for (i = 0; i < strlen(before); i++)
    {
        result[i] = before[i];
    }
    for (i = strlen(before); i < strlen(before) + howMany; i++)
    {
        result[i] = '0';
    }

    snprintf(resultHelp, strlen(before) + howMany + 1, result);
    return resultHelp;
}
char *delete_char(char *str, int k)
{
    char *temp = (char *)malloc(sizeof(char) * (strlen(str) - 1));
    char *tempHelp = (char *)malloc(sizeof(char) * (strlen(str) - 1));
    for (int i = 0; i < k; i++)
    {
        temp[i] = str[i];
    }
    for (int i = k + 1; i < strlen(str); i++)
    {
        temp[i - 1] = str[i];
    }
    snprintf(tempHelp, (strlen(str)), temp);
    return tempHelp;
}