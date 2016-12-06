#ifndef TINYRPC_CONFIG_H
#define TINYRPC_CONFIG_H


#define COMMENT_CHAR '#'
#include <string>
#include <map>

using namespace std;

namespace tinyrpc{
    bool ReadConfig(const string & filename, map<string, string> & m);
    void PrintConfig(const map<string, string> & m);
}





#endif //TINYRPC_CONFIG_H
