#include <iostream>

/*
 * “*” 匹配任意多个（大于等于 0 个）任意字符
 * “?” 匹配零个或者一个任意字符
 */


void Match(char* str, char* pattern, bool &matched)
{
    if (matched) return;

    if (str[0] == '\0' || pattern[0] == '\0') 
    {
        if (pattern[0] == '\0') matched = true;
        return;
    }

    if (str[0] == pattern[0] || pattern[0] == '*' || pattern[0] == '?')
    {
        Match(str+1, pattern+1, matched);
    }

    if (pattern[0] == '*' )
    {
        Match(str, pattern+1, matched);
        Match(str+1, pattern, matched);
    } else if (pattern[0] == '?')
    {
        Match(str, pattern+1, matched);
    }
}



int main(void)
{

    char str[] = "bfdasdfa";
    char pattern[] = "*s*f?a";

    bool matched = false;

    Match(str, pattern, matched);

    std::cout << "str: " << str << "  pattern: " << pattern << "   " << matched << std::endl;

    return 0;
}