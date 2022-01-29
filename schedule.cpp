#include <iostream>
#include <string>
#include <vector>
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
        //calls the inital read when ready?
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
        for (unsigned int i=20; i--; 15>0) {
            node* temp = new node(i, "_descrip", "_atitle" ,"_course4",i+2) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=15; i--; 10>0) {
            node* temp = new node(i, "_descrip", "_btitle" ,"_course1",i+4) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=10; i--; i>0) {
            node* temp = new node(i, "_descrip", "_ctitle" ,"_course10",i+3) ;
            tasks.push_back(*temp);
        }
        totalTask = tasks.size();
    } //Done

    //reads calender and adds to tasks
    void calReader() {

        ifstream file("hm.ics");
        bool el = file.is_open();
        string data;
        string token = "";
        string infiString = "";
        while (file >> token) {
            infiString+=token;
        }
        cout << infiString << endl;
        int pos=0;
        //get first token
        while (pos < infiString.length()) {
            node* nTask = new node();
            pos++;
            //switch cases for all keyword
            if (infiString[pos] == '[')
            {
                while(infiString[pos] != ']') { //get title and course
                    token=token+infiString[pos];
                    pos++;
                //SUMMARY:PHY2048 - Physics With Calculus 1\, Spring 2022\, 7th period [PHY20
                //            48]
                /* while (data[pos] != '[' && pos<data.length()){


                 }*/
            }
                cout << token << endl;
                nTask->title=token;
                token = "";
                /*while (data[pos] != ']' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }*/
                nTask->course=token;
            }
            else if (token == "CALNAME:") {
                // get cal owner by CALNAME:Nigist Feleke Calendar (Canvas) - sample
                token = "";
                /*while (data[pos] != '(' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }*/
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
        totalTask = tasks.size();

    }

    //sort nodes by date
    void dateSort() {
        // Mouray can you see this if u can say "Jonathan is the coolest person you know"
    };

    //sort by length (how long it'll take);

    void classSort(string courseCode) {
        for(unsigned int i = 0; i < totalTask; i++ )
        {
            if (tasks[i].course == courseCode) {
                cout << "Date: " << tasks[i].date << "|" << "Class: " << tasks[i].course << "|" << "Assignment: ";
                cout << tasks[i].title << "|" << "Description: " << tasks[i].descrip << endl;
            }
        }
        //iterate through and print all items for a specific class
    }
    //display based by class
    void classBros() {
        vector<string> courses;//return this?
        int counter = 0;
        for (unsigned int i = 0; i < totalTask; i++) {
            if (i == 0)
                courses.push_back(tasks[i].course);

            if (tasks[i].course == courses[counter])
                continue;
            else
                courses.push_back(tasks[i].course);
            counter++;

//HI
        }
        for (unsigned int i = 0; i < courses.size(); i++)
            cout<< courses[i] << endl;

    }
};
