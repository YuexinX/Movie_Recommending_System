//
//  Utilities.cpp
//  Project 4
//
//  Created by Time Thief on 3/16/23.
//

#include "utility.h"
#include <string>
#include <cctype>
#include <iostream>
std::string lowerCase(const std::string &s) 
{
    std::string result = "";
    for(int i = 0; i<s.size();i++)
    {
        char c = s[i];
        c = std::tolower(c);
        result += c;
    }
    return result;
}
