#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "schedule.h"
using namespace std;

//node structure --
struct node { 
    unsigned int date; //due date format 0123 Jan
    string descrip;  //description DESCRIPTION: -> LOCATION:
    string title; //title  SUMMARY: -> [
    string course;  //course - [ART1010C]
};

//assignment class
class Schedulize {

    void reader() {
        //reader function
        //reads the file
        //creates a vector of node
    }

    //sort nodes by date

    //sort by time & date;

    void classSort(string courseCode);
    //display based by class

public:
    unsigned int totalTask = tasks.size(); //idk if this works
    vector<node>tasks;

    void dateSort() {
        ifstream file("hm.ics"); //the calender
        string calenInfo;
        string token;
        getline(file,calenInfo);
        while (getline(file,calenInfo)) { //while there is info to get
            cout<<calenInfo;

            stringstream Data(calenInfo);
            cout<<token;
            // getline(Data,token,"SUMMARY:");
            // node* temp = new node();

        }
};


};
