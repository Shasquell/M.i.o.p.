#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

#include "declarations.h"

using namespace std;

int main(int argc,char*argv[])
{
    //variable definitions
    bool scripting=false;//indicates whether the program is running a script or not
    string raw_entry,command;
    string semp="";
    int bemp=0;
    char command_id;
    bool do_exit=0;
    vector<var>variables;
    string args;
    vector<string>lines{"out"};
    fstream file;

    //checking whether the program must run a script or not
    for(int i=1;i<argc;i++)
        args = args + argv[i];
    auto itr = lines.end();
    if(args!="")
    {
        file.open(args.c_str());
        while(!file.eof())
        {
            getline(file,semp,'\n');
            lines.push_back(semp);
        }
        lines.shrink_to_fit();
        itr = lines.begin();
    }
    if((!file.is_open())&&(args!=""))
        {cout << "unable to open file:" << args << '!' << endl;;}
    else if(file.is_open())
        scripting = true;
    if(file.is_open())
        file.close();
    //settings
    cout << "copyright Hossein Mohammadi 2024" << endl;
    cout << "program version 0.1.2" << endl;
    cout << "|>|program start:" << endl;
    system("COLOR 0e");
    Start:
    //start of the main loop
    semp="";bemp=0;
    command = "";
    if(!scripting)
    {
        cout << '-';
        getline(cin,raw_entry,'\n');
    }
    else
    {
        if(itr!=lines.end())
            raw_entry=*itr;
        else
            goto END;
        itr++;
    }
    // separation operation : separation of command from raw_entry
    if(raw_entry!="")
    {
        for(int i=0;(raw_entry[i]!=' ')&&(raw_entry[i]!='\0');i++)
            command = command + raw_entry[i];
        for(int i=command.length()+1;i<raw_entry.length();i++)
        {
            semp=semp+raw_entry[i];
        }
        raw_entry=semp;
        semp="";
    }
    else
        goto Start;
    if(command=="\\")
        goto Start;
    if(command=="")
        goto Start;
    command_id = detect(command);//detects the command and returns command ID number for the switch
    if(command_id==0)
        goto Start;
    JAUMP://ifjump jumps here to recheck and run the jump command

    //commands that will be checked and ran if they are the case:
    switch(command_id)
    {
//help
    case 'h':
        {
        if(raw_entry=="")
            {cout << "if you want info on a command ,write it after the help command:help \"command\"" << endl;break;}
        separate(raw_entry,0,semp,' ');
        if(semp=="all")
            {cout << "out \"string\"\nin [variable name]\nadd [amount/numeral data] [variable name]\nsubtract [amount/numeral data] [variable name]\nmultiply [variable name] [numeral data]\ndivide [variable name] [numeral data]\ndelete [variable name]\ntake [variable name] [from index] [amount]\nset [variable name] [optional:content]\ncopy [variable name] [variable name]\ninsert [variable name or string data] [variable name] [at index]\nmake [variable name] [optional:content]\nsystem [variable name]\nis [variable name or any data] [operator] [variable name or any data] [variable name]\njumpif [variable name or any data] [operator] [variable name or any data] [to line]\njump [to line]\nlength [variable name] [variable name]" << endl;break;}
        semp[0] = detect(semp);
        switch(semp[0])
        {
        case 'o':
            cout << "out \"string\"\nwrites all that is written after the command to console\noutv [variable name]\nwrites the variable\'s content to console\nto the end of any \"command\" an \'e\' can be added which represents endline\nPlease NOTE That when running a script commands don't automatically add an endline when writing to the console thus you should add an \'e\' if you want an endline!" << endl;
            break;
        case 'i':
            cout << "in [variable name]\ntakes entry from user and writes it to the contents of the given variable" << endl;
            break;
        case '+':
            cout << "add [amount/numeral data] [variable name]\nadds the given data to the given variable ,And saves the result to the second variable; Please NOTE That for adding strings to each other you have to use the command \"append\" and not this command" << endl;
            break;
        case '-':
            cout << "subtract [amount/numeral data] [variable name]\nsubtracts the given data from the given variable ,And saves the result to the second variable" << endl;
            break;
        case '*':
            cout << "multiply [variable name] [numeral data]\nmultiplies the given variable by the given number or numeral data ,And saves the result to the first variable" << endl;
            break;
        case '/':
            cout << "divide [variable name] [numeral data]\ndivides the given variable by the given number or numeral data ,And saves the result to the first variable" << endl;
            break;
        case '%':
            cout << "divide [variable name] [numeral data]\ndivides the given variable by the given number or numeral data ,And saves the remainder to the first variable" << endl;
            break;
        case 'd':
            cout << "delete [variable name]\ndeletes or removes the variable which its name is given; Please NOTE That this will not free up space in the memory but it just removes the variable name! if you want to free up do \"optimize\" after using delete this will free up memory as much as it can!" << endl;
            break;
        case 'k':
            cout << "remove [variable name] [from index] [amount]\nthe remove/take command or opposite of insert/put, it erases as many as amount specifies from the given index; Please NOTE That the formula is not from index to index but is from index and how many!" << endl;
            break;
        case 's':
            cout << "set [variable name] [optional:content]\nsets the contents of a variable.\nPlease NOTE That it will erase the contents of a variable ,if not given what to set the variables content to" << endl;
            break;
        case 'c':
           cout << "copy [variable name] [variable name]\ncopies the first variables content in to the second variable" << endl;
           break;
        case 'p':
            cout << "insert [variable name or string data] [variable name] [at index]\nputs/inserts the first given parameter \'at index\' of the second variable;Please NOTE That this works even with numeric variables and it will turn them into strings Only if you put a non numeric value" << endl;
            break;
        case 'm':
            cout << "make [variable name] [optional:content]\nmakes a variable and if given content will set its contents too" << endl;
            break;
        case '2':
            cout << "system [variable name]\nruns a system command\nsvstem [string data]\nruns a system command from the given variable" << endl;
            break;
        case '?':
            cout << "is [variable name or any data] [operator] [variable name or any data] [variable name]\nchecks whether the equation is \"true\"=1 or \"false\"=0 ,and saves the result to the last give argument;Please NOTE That 0 will be saved if false and 1 if true! Also if no argument is given to save to the result will be written;" << endl;
            break;
        case 'f':
            cout << "jumpif [variable name or any data] [operator] [variable name or any data] [to line]\nchecks whether the equation is \"true\" or \"false\" ,if its true it will jump to the given line ,else it wont" << endl;
            break;
        case 'j':
            cout << "jump [to line]\n jumps to the given line" << endl;
            break;
        case 'l':
            cout << "length [variable name] [variable name]\nmeasures the length of the first variable and saves it in the second one" << endl;
            break;
        default:
            cout << "was unable to provide help on!:" << command << endl;
            break;
        }
        semp="";
        break;
        }
//system
    case '2':
        if(command[1]=='v')
            {separate(raw_entry,0,semp,' ');get_var(variables,semp,raw_entry);system(raw_entry.c_str());}
        else//(command[1]=='v')
            system(raw_entry.c_str());
        break;
//out
    case 'o':
        if(command=="outve")
        {
            string *outwrite=new string;
            separate(raw_entry,0,semp,' ');
            get_var(variables,semp,*outwrite);
            cout << *outwrite << endl;
            delete outwrite;
        }
        else if(command=="outv")
        {
            string *outwrite=new string;
            separate(raw_entry,0,semp,' ');
            get_var(variables,semp,*outwrite);
            if(scripting)
                cout << *outwrite ;
            else
                cout << *outwrite << endl;
            delete outwrite;
        }
        else if(command=="out")
        {
            if(scripting)
                cout << raw_entry;
            else
                cout << raw_entry << endl;
        }
        else if(command=="oute")
        {
            cout << raw_entry << endl;
        }
        break;
//in
    case 'i':
        {
        if(raw_entry=="")
            {cout << "in ^;requires 1 parameter!" << endl;break;}
        separate(raw_entry,0,semp,' ');

        if(search_vars(variables,semp)!=-1)
        {
            string *entered = new string;
            cout << "=";
            getline(cin,*entered,'\n');
            set_var(variables,semp,*entered);
            delete entered;
        }
        else
            cout << "the following variable doesnt exist:\""+semp+"\"!" << endl;
        break;
        }
//calculation operations
    case '+':
        operation(variables,command,raw_entry,'+');
        break;
    case '-':
        operation(variables,command,raw_entry,'-');
        break;
    case '*':
        operation(variables,command,raw_entry,'*');
        break;
    case '/':
        operation(variables,command,raw_entry,'/');
        break;
    case '%':
        operation(variables,command,raw_entry,'%');
        break;
//copy
    case 'c':{
        if(raw_entry=="")
            {cout << "copy ^;requires 2 parameters!" << endl;break;}
        string *from = new string;
        string *to = new string;
        separate(raw_entry,0,*from,' ');
        separate(raw_entry,(*from).length()+1,*to,' ');
        if(*to!="")
        {
            get_var(variables,*from,*from);
            set_var(variables,*to,*from);//copy operation
        }
        else
            cout << "copy ^;requires 2 parameters!" << endl;
        break;}
//set
    case 's':{
        if(raw_entry=="")
            {cout << "set ^;requires 2 parameters!" << endl;break;}
        string *var_name = new string;
        string *content = new string;
        separate(raw_entry,0,*var_name,' ');
        separate(raw_entry,(*var_name).length()+1,*content,'\0');
        set_var(variables,*var_name,*content);
        break;}
//clearScreen
    case 'L':
        system("cls");
        break;
//is
    case '?':{
        semp = is(variables,raw_entry,'s');
        if(semp[0]!='f')
            cout << semp << endl;
        break;
        }
//jump
    case 'j':{
        if(scripting)
        {
            if(raw_entry!="")
            {
                semp = "";
                separate(raw_entry,0,semp,' ');
                string *data = new string;
                if(search_vars(variables,semp)!=-1)
                    get_var(variables,semp,*data);
                if(*data!="")
                {
                    if(is_num(*data))
                    {
                        if(int(stod(*data))<=lines.size())
                        {
                            if(int(stod(*data))<=lines.size())
                            {
                                itr = lines.begin();
                                for(int i=0;i<=stod(*data);i++)
                                    itr++;
                            }
                        else
                            cout << "entered line id is out of range!" << endl;
                        }
                    }
                    else
                        cout << "invalid line id:" << *data << '!' <<endl;
                }
                else if(is_num(semp))
                {
                    if(int(stod(semp))<=lines.size())
                    {
                        itr = lines.begin();
                        for(int i=0;i<=stod(semp);i++)
                            itr++;
                    }
                    else
                        cout << "entered line id is out of range!" << endl;
                }
                else
                    cout << "invalid line id:" << semp << '!' <<endl;
            }
            else
                cout << "jump ^;requires 1 parameter!" << endl;
        }
        else
            cout << "this command cannot be used outside of a script file!" << endl;
        semp = "";
        break;}
//jump if
    case 'f':
        if(scripting)
        {
            semp = is(variables,raw_entry,'f');
            if(semp[0]=='f'){;}
            else if(semp[0]=='1')
            {command_id = 'j';goto JAUMP;}
        }
        else
            cout << "this command cannot be used outside of a script file!" << endl;
        break;
//make
    case 'm':
        {
        if((raw_entry=="")||(raw_entry[0]==' '))
            {cout << "make ^;requires atleast 1 parameter!" << endl;break;}
        //checking whether there are two parameters to cut:
        for(int i=0;i<raw_entry.length();i++)
        {
            if((raw_entry[i]==' ')&&(i-1!=raw_entry.length()))
                {bemp = true;break;}
            else
                bemp = false;
        }
        string *par1 = new string;//parameter 1
        separate(raw_entry,0,*par1,' ');
        if(bemp==true)
        {
            string *par2 = new string;//parameter 2
            separate(raw_entry,(*par1).length()+1,*par2,'\0');
            if(search_vars(variables,*par1)==-1)
                {var *temp = new var(*par1,*par2);
                variables.push_back((*temp));}
            else
                cout << "the following variable:\"" << *par1 << "\" already exists!"<< endl;
        }
        else
            if(search_vars(variables,*par1)==-1)
                {var *temp = new var(*par1,"");
                variables.push_back((*temp));}
            else
                cout << "the following variable:\"" << *par1 << "\" already exists!"<< endl;
        }
        break;
//delete
    case 'd':
        if(raw_entry=="")
            {cout << "delete ^;requires 1 parameter!"<<endl;break;}
        separate(raw_entry,0,semp,' ');
        del_var(variables,semp);
        break;
//size
    case '0':
        cout << "size:" << variables.size() << " | capacity:" << variables.capacity() << endl;
        break;
//optimize
    case '1':
        variables.shrink_to_fit();
        break;
//length
    case 'l':{
        if(raw_entry=="")
            {cout << "length ^;requires 2 parameters!" << endl;break;}
        string *var1_name = new string;
        string *var2_name = new string;
        separate(raw_entry,0,*var1_name,' ');
        separate(raw_entry,(*var1_name).length()+1,*var2_name,' ');
        if(*var2_name=="")
            {cout << "length ^;requires 2 parameters!cap" << endl;break;}
        if(search_vars(variables,*var1_name)!=-1)
        {
        if(search_vars(variables,*var2_name)!=-1)
        {
            get_var(variables,*var1_name,*var1_name);
            string *length_ = new string;
            *length_ = to_string((*var1_name).length());
            set_var(variables,*var2_name,*length_);
        }
        else
            cout << "the following variable doesnt exist:\""+*var2_name+"\"!" << endl;
        }
        else
            cout << "the following variable doesnt exist:\""+*var1_name+"\"!" << endl;
        break;}
//put
    case 'p':{
        if(raw_entry=="")
            {cout << command << " ^;requires 3 parameters!" << endl;break;}
        string *data = new string;
        string *var_name = new string;
        string *at_index = new string;
        separate(raw_entry,0,*data,' ');
        separate(raw_entry,(*data).length()+1,*var_name,' ');
        if(!(*var_name).length())
            {cout << command << " ^;requires 3 parameters!" << endl;break;}
        if(search_vars(variables,*var_name)==-1)
            {cout << "the following variable doesnt exist:\""+*var_name+"\"!" << endl;break;}
        separate(raw_entry,(*data).length()+(*var_name).length()+2,*at_index,' ');
        if(!(*at_index).length())
            {cout << command << " ^;requires 3 parameters!" << endl;break;}
        string *var_content = new string;
        get_var(variables,*var_name,*var_content);
        if(search_vars(variables,*data)!=-1)
            get_var(variables,*data,*data);
        if(search_vars(variables,*at_index)!=-1)
            get_var(variables,*at_index,*at_index);
        if(is_num(*at_index))
        {
            if(stoi(*at_index)<=(*var_content).length())
            {
                semp = *var_content;
                semp.insert(stoi(*at_index),*data);
                set_var(variables,*var_name,semp);
            }
            else
                cout << "the entered index is out of range" << endl;
        }
        else
            cout << "the entered index is invalid" << endl;
        break;}
//remove
    case 'k':{
        if(raw_entry=="")
            {cout << command << " ^;requires 3 parameters!" << endl;break;}
        string *var_name = new string;
        string *from_index = new string;
        string *amount = new string;
        separate(raw_entry,0,*var_name,' ');
        if(search_vars(variables,*var_name)==-1)
            {cout << "the following variable doesnt exist:\"" << *var_name << "\"!" << endl;break;}
        separate(raw_entry,(*var_name).length()+1,*from_index,' ');
        if((*from_index).length())
            separate(raw_entry,(*var_name).length()+(*from_index).length()+2,*amount,' ');
        else
            {cout << command << " ^;requires 3 parameters!" << endl;break;}

        if((*amount).length())
            if((is_num(*from_index))&&(is_num(*amount)))
            {
                    string *var_content = new string;
                    int *fi= new int;
                    int *a = new int;
                    *fi = int(stod(*from_index));
                    *a = int(stod(*amount));
                    get_var(variables,*var_name,*var_content);
                    if(((*var_content).length()>=*fi)&&(*fi+*a<=(*var_content).length()))
                    {
                        (*var_content).erase(*fi,*a);
                        set_var(variables,*var_name,*var_content);
                    }
                    else
                        cout << "the entered indexes/Indices are out of range" << endl;
            }
            else
                cout << "the entered index and the amount to decrease both must be numeral and not strings!" << endl;
        else
            cout << command << " ^;requires 3 parameters!" << endl;
        break;}
//exit
    case 'e':
        do_exit=true;
        break;
    }
    if(!do_exit)goto Start;
    END:
    system("COLOR 07");
    cout << "\nenter anything to exit the program" << endl;
    getchar();
    return 0;
}
//end of main()
