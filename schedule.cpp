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

    unsigned int date; //due date format 0123 Jan
    string descrip;  //description DESCRIPTION: -> LOCATION:
    string title; //title  SUMMARY: -> [
    string course;  //course - [ART1010C]
    unsigned int length; //how long it'll take

    node() {
    }

    node(unsigned int _date, string _descrip,string _title,string _course) {
        date = _date;
        descrip= _descrip; //etc.
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

    //hardcodes samples tasks
    void hardCodeNodes() { //ads 20 tester nodes to sort
        for (int i=20; i--; i>0) {
            node* temp = new node(i, "_descrip"+i, "_title"+i ,"_course"+i) ;
            tasks.push_back(*temp);
        }
        totalTask = tasks.size();
    }

    //reads calender and adds to tasks
    void calReader() {

        ifstream file("text.txt");
        bool el = file.is_open();
        string data;
        while (getline(file, data)) {
            getline(file, data);

            stringstream _sData(data);

            cout << data;
        }


        string token = "";
        int pos=0;
        //get first token
        while (data[pos] != ' ' && pos<data.length()){
            token=token+data[pos];
            pos++;
        }

        while (pos<data.length()) {
            node* nTask = new node();

            //switch cases for all keyword
            if (token == "SUMMARY:") { //get title and course
                //SUMMARY:PHY2048 - Physics With Calculus 1\, Spring 2022\, 7th period [PHY20
                //            48]
                while (data[pos] != '[' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }
                nTask->title=token;
                token = "";
                while (data[pos] != ']' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }
                nTask->course=token;
            }
            else if (token == "CALNAME:") {
                // get cal owner by CALNAME:Nigist Feleke Calendar (Canvas) - sample
                token = "";
                while (data[pos] != '(' && pos<data.length()){
                    token=token+data[pos];
                    pos++;
                }
                calOwner = token;
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
        cout << "I created functionality buahahaha" << endl;
        cout << "I sorted the dates (jk not really lul)";
        // Mouray can you see this if u can say "Jonathan is the coolest person you know"
    };

    //sort by length (how long it'll take);

    void classSort(string courseCode) {
        //iterate through and print all items for a specific class
    }
    //display based by class

};
