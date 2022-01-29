#include <iostream>
#include <string>
#include <vector>
#include "schedule.h"
using namespace std;

//node structure --
struct node { 
    //unsigned int date //due date

    //below is all strings
    //descrip //description DESCRIPTION: -> LOCATION:
    //title  SUMMARY: -> [
    //course - [ART1010C]
    //

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
    vector<node>tasks;
};
