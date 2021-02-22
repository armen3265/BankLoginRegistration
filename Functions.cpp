#include "Functions.h"

std::string string_xor(const std::string& str, int key)
{
    std::string res;
    for (int i = 0; i < str.size(); i++)
    {
        res += str[i] ^ key;
    }
    return res;
}

bool checkInt(const std::string& obj)
{
    for(char c : obj)
    {
        if(c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}
