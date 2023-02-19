#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
            if (count_E > 1)
            {
                return false;
            }

            break;
        case 'E':
            count_E++;
            loc_e = i;
            if (count_E > 1)
            {
                return false;
            }

            break;
        default:
            if (num[i] < '0' || num[i] > '9')
                return false;
            break;
        }
    }
    return true;
}
bool isInt(char *a)
{

    return true;
}

int main(int argc, char const *argv[])
{
    char *a = (char *)argv[1];
    char *op = (char *)argv[2];
    char *b = (char *)argv[3];

    if (!isANumber(a) && !(op == "*" || op == "+" || op == "-" || op == "/") && !isANumber(b))
    {
        printf("The input cannot be interpret as numbers!");
        return 0;
    }
    
    
    
    return 0;
};
