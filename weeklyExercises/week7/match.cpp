#include<cstring>
const char *match(const char *s, char ch)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ch)
        {
            return s + i;
        }
    }
    return "Not found";
}
