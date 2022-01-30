#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "schedule.h"
using namespace std;
//hi its gg
//node structure
struct node {
    unsigned int date = 0; //due date format 0123 aka Jan 23rd
    string descrip = "";  //description DESCRIPTION: -> LOCATION:
    string title = ""; //title  SUMMARY: -> [
    string course = "";  //course - [ART1010C]
    unsigned int length = 1; //how long it'll take

    node() {
    }

    node(unsigned int _date, string _descrip,string _title,string _course, unsigned int _length) {
        date = _date;
        descrip= _descrip;
        title = _title;
        length = _length;
        course = _course;

    }
};

//assignment class
class Schedulize {

public:
    string calOwner;
    unsigned int totalTask;
    vector<node>tasks;

    Schedulize(){
        //calls the initial read when ready?
        //calReader();
        hardCodeNodes();
    }

    void showTasks(vector<node> _tasks){
        for (auto iter = _tasks.begin(); iter != _tasks.end(); ++iter) {
            cout << iter ->course<<endl;
            cout << iter ->title <<endl;
            cout << iter ->descrip<<endl;
            cout << iter ->date <<endl;
            cout << iter ->length << endl;
            cout<<endl;
        }
    }; //Done
    //hardcodes samples tasks
    void hardCodeNodes() { //ads 20 tester nodes to sort
        for (unsigned int i=20; i>15; i--) {
            node* temp = new node(i, "_descrip", "_atitle" ,"_course4",i+2) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=15;i>10;i--) {
            node* temp = new node(i, "_descrip", "_btitle" ,"_course1",i+4) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=10;i>0; i--) {
            node* temp = new node(i, "_descrip", "_ctitle" ,"_course10",i+3) ;
            tasks.push_back(*temp);
        }
        totalTask = tasks.size();
    } //Done

    //reads calender and adds to tasks
    void calReader() {

        ifstream file("hm.ics");
        bool el = file.is_open();
        string data = "";
        string token = "";
        char c;
        int count = 0;
        vector<char> tempChars;
        while (file.get(c))
        {
            tempChars.push_back(c);
        }
        for (int i = 0; i < tempChars.size(); i++)
        {
            if ((i < tempChars.size() - 1) && tempChars[i] =='\n' && tempChars[i+1] == ' ')
            {
                i++;
                continue;
            }
            if (i < tempChars.size())
                data += tempChars[i];
        }
        stringstream fileData(data);
        vector<vector<string>> events;
        while (fileData >> token) {
            vector<string> eventTokens = {};

            if (token == "BEGIN:VEVENT")
            {
                while (token != "END:VEVENT" && fileData >> token)
                {
                    eventTokens.push_back(token);
                }
                events.push_back(eventTokens);
            }
            else
            {
                while (token != "BEGIN:VEVENT" && fileData >> token)
                {
                    eventTokens.push_back(token);
                }
                events.push_back(eventTokens);
            }

        }
        for (int i = 0; i < events.size(); i++)
        {
            node* nTask = new node();
            for (int j = 0; j < events[i].size(); j++)
            {
                // gets course title
                if (events[i][j].find('[') != string::npos && events[i][j+1].find("URL") != string::npos)
                {
                    nTask->course = events[i][j].substr(1, events[i][j].length()-2);
                }
                // gets the calendar owner
                if (events[i][j].find("user") != string::npos)
                {
                    string name = "";
                    while (j < events[i].size()-2)
                    {
                        j++;
                        name = name + events[i][j] + " ";
                    }
                    calOwner = name;
                }
                // gets description of task
                if (events[i][j].find("DESCRIPTION:") != string::npos)
                {
                    string desc = "";
                    while (events[i][j].find("LOCATION:") == string::npos && events[i][j].find("SEQUENCE:") == string::npos )
                    {
                        desc = desc + events[i][j] + " ";
                        j++;
                    }
                    nTask->descrip = desc.substr(12,desc.length()-1);
                }
                // gets task
                if (events[i][j].find("SUMMARY:") != string::npos)
                {
                    string summar = "";
                    while (events[i][j].find('[') == string::npos)
                    {
                        summar = summar + events[i][j] + " ";
                        j++;
                    }
                    nTask->title = summar.substr(8, summar.length()-1);
                }
                if (events[i][j].find("DTSTART:") != string::npos)
                {
                    string dayStr;
                    dayStr = events[i][j].substr(12, 4);
                    int dayNum = stoi(dayStr);
                    if (events[i][j][23] == 'Z')
                    {
                        if((stoi(events[i][j].substr(17,2)))-5 < 0)
                        dayNum--;
                    }
                    else
                       // cout << events[i][j][23] << "hehexd" << endl;
                    nTask->date = (unsigned int) dayNum;
                }
                if (events[i][j].find("DTSTART;") != string::npos)
                {
                    string dayStr;
                    dayStr = events[i][j].substr(23, 4);
                    int dayNum = stoi(dayStr);
                    if (events[i][j][34] == 'Z')
                    {
                        if((stoi(events[i][j].substr(17,2)))-5 < 0)
                        dayNum--;
                    }
                    nTask->date = (unsigned int) dayNum;
                }
                // Difficulty?
            }
            tasks.push_back(*nTask);
    }

        int pos=0;
        //get first token
        /*
        for (int i = 0; i < events.size(); i++)

            //switch cases for all keyword

                //SUMMARY:PHY2048 - Physics With Calculus 1\, Spring 2022\, 7th period [PHY20
                //            48]
                while (data[pos] != '[' && pos<data.length()){


                 }
                nTask->title=token;
                token = "";
                while (data[pos] != ']' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }
                nTask->course=token;
            else if (token == "CALNAME:") {
                // get cal owner by CALNAME:Nigist Feleke Calendar (Canvas) - sample
                token = "";
                while (data[pos] != '(' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }
                calOwner = token;
                cout << token << endl;
            }
            else if (token == "DESCRIPTION:"){
                // DESCRIPTION:[Click here to join Zoom Meeting:945 6006 5340] (https://ufl.zo
                //            om.us/j/94560065340?pwd=U1F4dG9NMk93U3lrSXA5aVY2d2FWZz09)
                //            LOCATION:

                string tempTok = "";
                while (token != "LOCATION:" && pos<data.length()){
                    tempTok = tempTok + token;
                }
                nTask->descrip = tempTok;
            }
            else if (token == "END:VEVENT"){
                // END:VEVENT --> create the node & send it
                tasks.push_back(*nTask);//adds this to our list of tasks
                token = "";
            }
            else { //move to next line
                getline(file, data);
            }
        }
        totalTask = tasks.size();*/
    }

    //sort nodes by date
    void dateSort() {
        // Mouray can you see this if u can say "Jonathan is the coolest person you know"

    };

    //sort by length (how long it'll take);
    vector<node> classSort() {
        vector<node> newTask;

        for(unsigned int j = 0; j < classBros().size(); j++)
        {
            for (unsigned int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].course == classBros()[j])
                {
                    newTask.push_back(tasks[i]);
                    //cout << "Date: " << tasks[i].date << "|" <<
                    //cout<< "Class: " << newTask[i].course;
                    // cout << tasks[i].title << "|" << "Description: " << tasks[i].descrip << endl;
                }
            }
        }

//iterate through and print all items for a specific class
    }

    vector<node> smallClassSort(string courseCode) {
        vector<node> newTask;
        for(unsigned int i = 0; i < totalTask; i++ )
        {
            if (tasks[i].course == courseCode) {
                newTask.push_back(tasks[i]);
            }
        }
        //iterate through and print all items for a specific class
    }

    //display based by class

    vector<string> classBros() {
        vector<string> courses;//return this?
        int counter = 0;
        for (unsigned int i = 0; i < totalTask; i++) {
            if (i == 0)
                courses.push_back(tasks[i].course);

            else if (tasks[i].course == courses[counter])
                continue;
            else {
                courses.push_back(tasks[i].course);
                counter++;
            }


//HI
        }
        //sort(courses.begin(), courses.end(), gee);

            return courses;
    }
};
