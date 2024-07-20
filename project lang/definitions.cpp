#include "declarations.h"

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

//actual function definitions:
char detect(string &command)
{
    char id=0;
    if(command=="help")id='h';
    else if(command=="optimize")id='1';
    else if(command=="sizememory")id='0';
    else if(((command=="sys")||(command=="system"))||((command=="svstem")||(command=="svs")))id='2';
    else if(command=="exit")id='e';
    else if(command=="make")id='m';
    else if(command=="set")id='s';
    else if((command=="del")||(command=="delete"))id='d';
    else if(command=="jump")id='j';
    else if(((command=="if")||(command=="jumpif"))||(command=="ifjump"))id='f';//
    else if(command=="is")id='?';//
    else if(((command=="out")||(command=="oute"))||((command=="outv")||(command=="outve")))id='o';
    else if(command=="in")id='i';
    else if(command=="add")id='+';
    else if(command=="copy")id='c';
    else if((command=="len")||(command=="length"))id='l';
    else if((command=="put")||(command=="insert"))id='p';
    else if((command=="sub")||(command=="subtract"))id='-';
    else if((command=="mul")||(command=="multiply"))id='*';
    else if((command=="div")||(command=="divide"))id='/';
    else if((command=="remain")||(command=="remainder"))id='%';
    else if((command=="rem")||(command=="remove"))id='k';
    else if(((command=="cs")||(command=="clear"))||(command=="clearscreen"))id='L';
    else {cout << "no such command or command abbreviation:" << command << endl;return 0;}
    return id;
}

void separate(string &from,int indx,string &to,const char delim)
{
    for(;indx<from.length();indx++)
    {
        if(from[indx]==delim)
            break;
        else
            to=to+from[indx];
    }
}


int search_vars(vector<var>&variables,string &var_name)
{
    int counter=0;
    for( vector<var>::iterator it=variables.begin() ; it!=variables.end() ; it++)
    {
        if((*it).name==var_name)
            return counter;
        counter++;
    }
    return -1;
}

void del_var(vector<var>&variables,string &var_name)
{
    for( vector<var>::iterator it=variables.begin() ; it!=variables.end() ; it++)
    {
        if((*it).name==var_name)
            {variables.erase(it);return;}
    }
    cout << "the following variable didn't exist:\""+var_name+"\" thus could not be deleted!" << endl;
}

void get_var(vector<var>&variables,string &var_name,string &to)
{
    for( vector<var>::iterator it=variables.begin() ; it!=variables.end() ; it++)
    {
        if((*it).name==var_name)
            {to = (*it).content;return;}
    }
    cout << "the following variable doesnt exist:\""+var_name+"\"!" << endl;
}

void set_var(vector<var>&variables,string &var_name,string &content)
{
    string failure = "the following variable doesnt exist:\""+var_name+"\"!";
    for( vector<var>::iterator it=variables.begin() ; it!=variables.end() ; it++)
    {
        if((*it).name==var_name)
            {(*it).content=content;return;}
    }
    cout << failure <<endl;
}

bool is_num(string &Str)
{
    bool result = false;
    for(int i=0;i<Str.length();i++)
    {
        if(((isdigit(Str[i]))||(Str[i]=='.'))||(Str[i]=='-'))
            result = true;
    }
    return result;
}

void operation(vector<var>&variables,string &command,string &entry,const char op)
{
    if(entry=="")
        {cout << command << " ^;requires 2 parameters" << endl;return;}
    string data,var_name,var_content,temp;

    separate(entry,0,data,' ');
    if(data.length())
        separate(entry,data.length()+1,var_name,' ');
    else
        {cout << command << " ^;requires 2 parameters" << endl;return;}
    if(((op=='*')||(op=='/'))||(op=='%'))
    {
        temp=data;
        data=var_name;
        var_name=temp;
        temp="";
    }
    if(search_vars(variables,var_name)==-1)
        {cout <<"the following variable doesnt exist:\""<< var_name <<"\"!"<< endl;return;}
    if(search_vars(variables,data)!=-1)
        get_var(variables,data,data);
    if(!is_num(data))
        {cout << data << " must be numeric and not a string!" << endl;return;}
    get_var(variables,var_name,var_content);
    if(!is_num(var_content))
        {cout << var_name << " must be numeric and not a string!" << endl;return;}

    switch(op)
    {
    case '+':
        temp = to_string(stod(var_content)+stod(data));
        set_var(variables,var_name,temp);
        break;
    case '-':
        temp = to_string(stod(var_content)-stod(data));
        set_var(variables,var_name,temp);
        break;
    case '*':
        temp = to_string(stod(var_content)*stod(data));
        set_var(variables,var_name,temp);
        break;
    case '/':
        temp = to_string(stod(var_content)/stod(data));
        set_var(variables,var_name,temp);
        break;
    case '%':
        temp = to_string(int(stod(var_content))%int(stod(data)));
        set_var(variables,var_name,temp);
        break;
    }
}

char is(vector<var>&variables,string &raw_entry,const char sorf)
{
    string data1,op,data2,var_or_num,semp;
    char returner='\0';
    separate(raw_entry,0,data1,' ');
    separate(raw_entry,data1.length()+1,op,' ');
    separate(raw_entry,data1.length()+op.length()+2,data2,' ');
    separate(raw_entry,data1.length()+op.length()+data2.length()+3,var_or_num,' ');
    if(sorf=='s')
    {
        if((data1!="")&&(op!="")&&(data2!=""))
        {
            if(search_vars(variables,data1)!=-1)
                get_var(variables,data1,data1);
            if(search_vars(variables,data2)!=-1)
                get_var(variables,data2,data2);
            if((is_num(data1))&&(is_num(data2)))
            {
                switch(op[0])
                {
                case '=':
                    if(data1==data2)
                        returner='1';
                    else
                        returner='0';
                    break;
                case '!':
                    if(data1!=data2)
                        returner='1';
                    else
                        returner='0';
                    break;
                case '<':
                    if(stod(data1)<stod(data2))
                        returner='1';
                    else
                        returner='0';
                    break;
                case '>':
                    if(stod(data1)>stod(data2))
                        returner='1';
                    else
                        returner='0';
                    break;
                }
                semp=" ";
                semp[0]= returner;
                if(search_vars(variables,var_or_num)!=-1)
                    set_var(variables,var_or_num,semp);
                else return returner;
            }
            else if(((!is_num(data1))==(!is_num(data2)))==1)
            {
                if(op[0]=='='){
                    if(data1==data2)
                        returner='1';
                    else
                        returner='0';}
                else if(op[0]=='!'){
                    if(data1!=data2)
                        returner='1';
                    else
                        returner='0';}
                else {cout << "cannot compare two strings using:" << op[0] << '!' << endl;return 'f';}
                semp=" ";
                semp[0]= returner;
                if(search_vars(variables,var_or_num)!=-1)
                    set_var(variables,var_or_num,semp);
                else return returner;
            }
            else
                cout << "unable to compare data of different types!" << endl;
        }
        else
            cout << "if ^;requires atleast 3 parameters" << endl;
    }
    if(sorf=='f')
    {
        if((data1!="")&&(op!="")&&(data2!="")&&(var_or_num!=""))
        {
            if(search_vars(variables,var_or_num)!=-1)
                get_var(variables,var_or_num,var_or_num);
            if(search_vars(variables,data1)!=-1)
                get_var(variables,data1,data1);
            if(search_vars(variables,data2)!=-1)
                get_var(variables,data2,data2);
            if(!is_num(var_or_num))
                return 'f';
            raw_entry = var_or_num;
            if((is_num(data1))&&(is_num(data2)))
            {
                switch(op[0])
                {
                case '=':
                    if(data1==data2)
                        return '1';
                    else
                        return '0';
                    break;
                case '!':
                    if(data1!=data2)
                        return '1';
                    else
                        return '0';
                    break;
                case '<':
                    if(stod(data1)<stod(data2))
                        return '1';
                    else
                        return '0';
                    break;
                case '>':
                    if(stod(data1)>stod(data2))
                        return '1';
                    else
                        return '0';
                    break;
                }
            }
            else if(((!is_num(data1))==(!is_num(data2)))==1)
            {
                if(op[0]=='='){
                    if(data1==data2)
                        return 1;
                    else
                        return 0;}
                else if(op[0]=='!'){
                    if(data1!=data2)
                        return 1;
                    else
                        return 0;}
            }
            else
                cout << "unable to compare data of different types!" << endl;
        }
        else
            cout << "if ^;requires atleast 3 parameters" << endl;
    }
    return 'f';
}
