#include "config.h"


#include <fstream>
#include <iostream>

using namespace std;

namespace tinyrpc{
    bool IsSpace(char c)
    {
        if (' ' == c || '\t' == c)
            return true;
        return false;
    }

    bool IsCommentChar(char c)
    {
        if (c == COMMENT_CHAR){
            return true;
        }else{
            return false;
        }
    }

    void Trim(string & str)
    {
        if (str.empty()) {
            return;
        }
        int i, start_pos, end_pos;
        for (i = 0; i < str.size(); ++i) {
            if (!IsSpace(str[i])) {
                break;
            }
        }
        if (i == str.size()) { 
            str = "";
            return;
        }
        start_pos = i;
        for (i = str.size() - 1; i >= 0; --i) {
            if (!IsSpace(str[i])) {
                break;
            }
        }
        end_pos = i;
        str = str.substr(start_pos, end_pos - start_pos + 1);
    }

    bool AnalyseLine(const string & line, string & key, string & value)
    {
        if (line.empty())
            return false;
        int start_pos = 0, end_pos = line.size() - 1, pos;
        if ((pos = line.find(COMMENT_CHAR)) != -1) {
            if (0 == pos) { 
                return false;
            }
            end_pos = pos - 1;
        }
        string new_line = line.substr(start_pos, start_pos + 1 - end_pos);  

        if ((pos = new_line.find('=')) == -1)
            return false;  

        key = new_line.substr(0, pos);
        value = new_line.substr(pos + 1, end_pos + 1- (pos + 1));

        Trim(key);
        if (key.empty()) {
            return false;
        }
        Trim(value);
        return true;
    }

    
    bool ReadConfig(const string & filename, map<string, string> & m)
    {
        m.clear();
        ifstream infile(filename.c_str());
        if (!infile) {
            cout << "file open error" << endl;
            return false;
        }
        string line, key, value;
        while (getline(infile, line)) {
            if (AnalyseLine(line, key, value)) {
                m[key] = value;
            }
        }
        infile.close();
        return true;
    }


    void PrintConfig(const map<string, string> & m)
    {
        map<string, string>::const_iterator mite = m.begin();
        for (; mite != m.end(); ++mite) {
            cout << mite->first << "=" << mite->second << endl;
        }
    }

}



