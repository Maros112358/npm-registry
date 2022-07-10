#ifndef _UTILS_
#define _UTILS_

#include <vector>
#include <string>

using namespace std;

static vector<string> split(string str, string delimiter)
{
    vector<string> strings;
 
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
 
    strings.push_back(str.substr(prev));
 
    return strings;
}

#endif