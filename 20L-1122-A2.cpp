#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <string.h>
#ifdef WINDOWS
#else
#define GetCurrDir getcwd
#endif

using namespace std;

int PipesUsed(string input)
{
    bool pipeused = false;
    int frequency = 0;
    //the loop runs till the size of the string
    for (int i = 0; i < input.size(); i++)
    {
        if (input.at(i) == '|')
        {
            //the pipe is found
            pipeused = true;
            frequency++;
            //it measures the number of pipes used
        }
    }
    return frequency;
    //it returns the number of pipes used in the string
}

int IdentifyOpr(string input)
{
    bool found = false;
    //the loop runs till the size of the string
    //the whole string is basically traversed
    for (int i = 0; i < input.size(); i++)
    {
        //we have used the .at function which will return a reference to the element present at location i in given string.
        if (input.at(i) == '<')
        {
            found = true;
            //this condition checks if the extraction operator was used
            return -1;
        }
        else if (input.at(i) == '>')
        {
            found = true;
            //this condition checks whether the insertion operator was used
            return 1;
        }
    }
    return 0;
}
vector<string> Tokenization(string input, char delimeter)
{

    vector<string> chunk;
    int dumflag = 0;
    stringstream Dummy(input);
    int temp1 = 0;
    string SubStr;
    // we have used to space to imply that the string will be tokenized based on space
    while (getline(Dummy, SubStr, delimeter))
    {
        dumflag++;
        temp1--;
        if (SubStr != "")
        {
            dumflag = 0;
            chunk.push_back(SubStr);
        }
        temp1 = -1;
    }
    return chunk;
}
void StoringCharArray(char*& str, string data)
{
    int elements;
    int i = 0;
    //we run a loop of size of the string
    for (int j = 0; j < data.length(); j++)
    {
        //counting number of characters in the string
        elements++;
        str[i++] = data[j];
    }

    str[i] = '\0';
    //here we are actually storing the string data into a character array
}


void Child(string input, int opr)
{
    int  flag1 = 0;
    int flag2 = 0;
    bool var = true;
    if (opr == 1)

    {
        var = false;
        //This separation os t extract File Name
        vector<string>Substr;
        stringstream Dummy(input);
        string token;
        flag1 = 1;
        while (getline(Dummy, token, '>'))
        {
            flag2++;
            Substr.push_back(token);
        }

        string buffer = Substr.at(Substr.size() - 1);
        flag2 = flag1;
        char* fname = new char[buffer.size()];
        StoringCharArray(fname, Substr.at(Substr.size() - 1));
        //opening the file
        int edit = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        var = false;
        vector<string> Sub = Tokenization(Substr.at(0), ' ');
        flag1++;
        char** Argument = new char* [Sub.size()];
        int dumyx = flag1;
        //made a dynamic 2d array
        //the loop runs till the end of the string
        int i;
        for (i = 0; i < Sub.size(); i++)
        {
            dumyx++;
            Argument[i] = new char[Sub.at(i).size()];
            var = true;
            StoringCharArray(Argument[i], Sub.at(i));
        }
        Argument[i] = { NULL };
        //we have used dup2 to duplicate the file descriptor
        dup2(edit, 1);//we are writing inside the file
        var = false;
        int child = fork();
        //forked the child
        if (child == 0)
        {
            int temp2 = dumyx;
            //the child process is created
            int file = 0;
            temp2++;
            file = execvp(Argument[0], Argument);
            if (file < 0)
            {
                temp2++;
                cout << "\n No Exetuable present" << endl;
            }
        }
        //parent process
        else if (child > 0)
        {
            var = true;
            //we will wait
            wait(NULL);
            dumyx++;
        }
    }
    else if (opr == -1)
    {
        //if it is the insertion operator
        int temp3 = 0;
        bool overflag = true;
        //This separation os t extract File Name
        vector<string>Substr;
        stringstream Dummy(input);
        bool watchstr = true;
        string token;
        while (getline(Dummy, token, '>'))
        {
            watchstr = false;
            Substr.push_back(token);
        }

        string buffer = Substr.at(Substr.size() - 1);
        temp3 = -1;
        char* fname = new char[buffer.size()];
        temp3++;
        StoringCharArray(fname, Substr.at(Substr.size() - 1));
        int tempio = temp3;
        int read = open(fname, O_RDONLY, 0);

        vector<string> Sub = Tokenization(input, '>');
        //created a dynamic 2d array
        char** Argument = new char* [Sub.size()];

       
        //the loop runs till the end of the string
        int i;
        for (i = 0; i < Sub.size(); i++)
        {
            overflag = true;
            Argument[i] = new char[Sub.at(i).size()];
            watchstr = true;
            StoringCharArray(Argument[i], Sub.at(i));
        }
        Argument[i] = { NULL };

        //we have used dup2 to duplicate the file descriptor
        dup2(read, 0);
        temp3++;
        int child = fork();
        //we forked the child here
        if (child == 0)
        {
            temp3 = 0;
            //child process is created
            int sucess = 0;
            watchstr = true;
            sucess = execvp(Argument[0], Argument);
            if (sucess < 0)
            {
                overflag = true;
                cout << "\n No Exetuable present" << endl;
            }
        }

        //parent process
        else if (child > 0)
        {
            //we will wait
            wait(NULL);
            watchstr = false;
        }
    }
    else
    {
    string s21 = "";
    bool chrarr = true;
    int max = 0;
        vector<string> token = Tokenization(input, ' ');

        for (int i = 0; i < token.size(); i++)
        {
            max++;
            cout << token.at(i) << endl;
        }
        //created a dynmaic 2d array
        char** Argument = new char* [token.size()];
        //the loop runs till the end of the string
        int i;
        for (i = 0; i < token.size(); i++)
        {
            chrarr = false;
            Argument[i] = new char[token.at(i).size()];
            max = max * 2;
            StoringCharArray(Argument[i], token.at(i));
        }

        Argument[i] = { NULL };
        chrarr = true;
        int child = fork();
        //the child is forked

        if (child == 0)
        {
            max = 0;
            //child process
            int success = 0;
            max = max + 1;
            success = execvp(Argument[0], Argument);
            if (success < 0)
            {
                chrarr = true;
                cout << "No Exetuable found" << endl;
            }
        }
        //parent process
        else if (child > 0)
        {
            chrarr = true;
            //we wil wait
            wait(NULL);
            max = -1;
        }
    }
}
int main()
{
    system("cls | clear");
    while (true)
    {
        char a, b, c;
        char A[100];
        int dum1 = 0, dum2 = -1;
        bool flg1 = true;
        GetCurrDir(A, FILENAME_MAX);
        //the path will be  printed to the current folder
        cout << "\n" << "Path" << "$ ";
        dum1 = 0;
        string input;
        int temp = dum1;
        getline(cin, input);

        //if the user enters exit the loop will terminate
        if (input == "exit")
        {
            dum2++;
            break;
        }
        vector<string> subs = Tokenization(input, '|');
        flg1 = true;
        int Processes = PipesUsed(input);

        //created a dynamic 2d array
        int** piping = new int* [Processes];

        int reading = dup(0);
        int pi = dum2;
        //0 is used for reading
        int writing = dup(1);
        //1 is used for writing


        //the loop will run for the number of processes
        for (int i = 0; i <= Processes; i++)
        {
            dum2++;
            piping[i] = new int[2];
            flg1 = false;
            pipe(piping[i]);

            if (i != Processes)
            {
                //the file desccriptor is duplicated
                dup2(piping[i][1], 1);
                dum1++;
            }
            else
            {
                dum2++;
                dup2(writing, 1);
            }
            int sign = IdentifyOpr(subs.at(i));
            flg1 = true;
            Child(subs.at(i), sign);
            //the file is closed
            close(piping[i][1]);
            int ko = dum1;
            //file descriptor is duplicated
            dup2(piping[i][0], 0);
            ko++;
        }
        dup2(reading, 0);
        dum1++;
        dup2(writing, 1);
        dum2++;
        for (int i = 0; i < Processes; i++)
        {
            //file is closed
            close(piping[i][0]);
        }


    }

    return 0;
}