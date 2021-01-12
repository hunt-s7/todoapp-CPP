#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
using namespace std;

// 1- add
// 2- delete
// 3- complete
// 4- listing(list)
// 5- help
// 6- Status

int add(string s) //add
{
    int pending,done;
    string temp;
    vector<string> v;

    ifstream read;
    read.open("todo.txt");

    while(getline(read,temp))
    {
        v.push_back(temp);
    }
    read.close();

    bool check=false; //task not present

    for(int i=0;i<v.size();i++)
    {
        if(s==v[i])
        check=true; // task is already added earlier, but needed to refresh it.
    }

    if(check==false)
    {
        fstream write;
        write.open("todo.txt",ios::app);
        write<<s<<endl;
        cout<<"Added todo : "<<"\""<<s<<"\""<<endl;
        write.close();
    }
    else
    {
        ofstream write;
        write.open("todo.txt");
        
        for(int i=0;i<v.size();i++)
        {
            if(v[i]!=s)
            {
                write<<v[i]<<endl;
            }
        }

        write<<s<<endl;
        cout<<"Added todo : "<<"\""<<s<<"\""<<endl;
        write.close();
    }
    
    return 0;
}

int del(int k) // delete
{
    string s;
    vector<string> v;

    ifstream read;
    read.open("todo.txt");
    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    if(k>v.size() ||k<1)
    {
        // if the task number entered is greater thsn the number of task, then it cannot be deleted or it does not exist.
        cout<<"ERROR...! task #"<<k<<" does not exist! No task is deletd!"<<endl;
    }
    else
    {
        ofstream write;
        write.open("todo.txt");
        for(int i=0;i<v.size();i++)
        {
            if(i!=k-1)
            write<<v[i]<<endl;
        }
        cout<<"Deleted todo #"<<k<<endl;
    }
    
    return 0;
}

int done(int k) // complete
{
    // we will bw printing exact time of the completetion also.

    int year,month,date,z;
    vector<string> v;
    string s,x;

    time_t ttime= time(0);
    tm *local_time=localtime(&ttime);
    year=local_time->tm_year + 1900;
    month=local_time->tm_mon + 1;
    date=local_time->tm_mday;

    // you have " year month and date stored."
    // these are just time functions, using which you can have curDate.

    ifstream read;
    read.open("todo.txt");

    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    // if k > number of tasks in queue then ERROR,

    if(k>v.size())
    {
        cout<<"ERROR...! task #"<<k<<" doesn't exist!"<<endl;
    } 
    else
    {
        ofstream write1,write2;
        write1.open("todo.txt");
        write2.open("done.txt",ios::app);
        for(int i=0;i<v.size();i++)
        {
            if(i==k-1)
            {
                x=v[i];
                cout<<"Marked todo #"<<k<<" as done."<<endl;
            }
            else
            {
                write1<<v[i]<<endl;
            }
        }
        write1.close();
        write2<<"x "<<year<<"-"<<month<<"-"<<date<<" "<<x<<endl;
        write2.close();
    }
    
    return 0;
}

int ls() // list
{
    string s;
    vector<string> v;

    ifstream read;
    read.open("todo.txt");
    while(getline(read,s))
    {
        v.push_back(s);
    }
    read.close();

    if(v.size()==0)
    {
        cout<<"There are no pending todos."<<endl;
    }
    else
    {
        for(int i=v.size()-1;i>=0;i--)
        {
            s=v.back();
            v.pop_back();
            cout<<"["<<(i+1)<<"]"<<" "<<s<<endl;
        }
    }

    return 0;
}

int help() //help
{
    //this is main, without it, you cant even run your app, its like a USER MANUAL

    cout<<"How to use this TODO APP :-"<<endl;
    cout<<"$ ./todoapp add \"todo item\"        #Add a new todo item"<<endl;
    cout<<"$ ./todoapp del NUMBER             #Delete a todo item"<<endl;
    cout<<"$ ./todoapp done NUMBER            #Complete a todo item"<<endl;
    cout<<"$ ./todoapp ls                     #Show remaining todo items"<<endl;
    cout<<"$ ./todoapp help                   #Show How to use"<<endl;
    cout<<"$ ./todoapp report                 #Display Statistics of the app."<<endl;

    return 0;
}

int report() //status
{
    int pending =0,done=0;
    string s;
    int year,month,date;

    ifstream read;
    read.open("todo.txt");  // todo.txt contains the pending tasks;
    if(read!=NULL)
    {
        while(getline(read,s))
        {
            pending++;
        }
    }
    read.close();

    read.open("done.txt"); // done.txt contains the completed tasks
    if(read!=NULL)
    {
        while(getline(read,s))
        {
            done++;
        }
    }
    read.close();

    // We will be displaying this with time.

    time_t ttime= time(0);
    tm *local_time=localtime(&ttime);
    year=local_time->tm_year + 1900;
    month=local_time->tm_mon + 1;
    date=local_time->tm_mday;

    cout<<year<<"-"<<month<<"-"<<date<<" "<<"Pending Tasks : "<<pending<<"Completed Tasks : "<<done<<endl;

    return 0;
    
}

int main(int argc, char* argv[])
{
    string s, s2;
    int k=0;

    if(argc>1)
    s=argv[1];

    if(argc==1 || s=="help")
    {
        help(); // call help
    }
    else if(s=="add")
    {
        // 1- if add is called and nothing added.
        // 2- if task is given to add

        if(argc==2)
        {
            cout<<"ERROR...! Missing todo string! Nothing Added!"<<endl;
        }
        else
        {
            s2=argv[2];
            add(s2);
        }
        
    }
    else if(s=="del")
    {
        // 1- if del is called and the task number to be deleted is not mentioned!
        // 2- if task number is mentioned

        if(argc==2)
        {
            cout<<"ERROR...! Missing task number! No task is deletd!"<<endl;
        }
        else
        {
            s2=argv[2];
            k=stoi(s2); //string to integer
            del(k);
        }
        
    }
    else if(s=="report")
    {
        report(); // call report
    }
    else if(s=="done")
    {
        // 1- if done is called and the task number which is completed is not mentioned!
        // 2- if task number is mentioned

        if(argc==2)
        {
            cout<<"ERROR...! Missing task number! No task is marked completed!"<<endl;
        }
        else
        {
            s2=argv[2];
            k=stoi(s2); // changes string to integer

            // if k = 0 , then there is no task in the queue, so no deletion
            if(k>0)
            done(k);
            else
            {
                cout<<"ERROR...! todo #0 does not exist!"<<endl;
            }
            
        }
        
    }
    else if(s=="ls")
    {
        ls(); // call list
    }

    return 0;
}
