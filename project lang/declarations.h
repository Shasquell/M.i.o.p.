#ifndef DECLARATIONS_
#define DECLARATIONS_

#include <string>
#include <string.h>
#include <vector>

using namespace std;

//class declarations:
class var
{
public:
    string name;
    string content;
    var(string Ename,string Econtent)
    {
        name = Ename;
        content = Econtent;
    }
};

//function declarations:
bool is_num(string&);
char detect(string&);
void separate(string &from,int indx,string &to,const char delim);
int search_vars(vector<var>&variables,string &var_name);
void del_var(vector<var>&variables,string &var_name);
void get_var(vector<var>&variables,string &var_name,string &to);
void set_var(vector<var>&variables,string &var_name,string &content);
void operation(vector<var>&variables,string &command,string &entry,const char op);
char is(vector<var>&variables,string &raw_entry,const char sorf);
#endif // DECLARATIONS
