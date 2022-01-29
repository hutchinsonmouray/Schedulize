#include <iostream>
#include <string>
#include <vector>
#include "schedule.h"
using namespace std;

//node structure --
struct node { 
    //unsigned int date //due date

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

    void dateSort();
    //sort nodes by date

    //sort by time & date;

    void classSort(string courseCode);
    //display based by class

public:
    unsigned int totalTask = tasks.size(); //idk if this works
    vector<node>tasks;
};
