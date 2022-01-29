#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "schedule.h"
using namespace std;

//node structure
struct node { 
    unsigned int date; //due date format 0123 Jan
    string descrip;  //description DESCRIPTION: -> LOCATION:
    string title; //title  SUMMARY: -> [
    string course;  //course - [ART1010C]
    unsigned int length; //how long it'll take
};

//assignment class
class Schedulize {

public:
    unsigned int totalTask = tasks.size(); //idk if this works
    vector<node>tasks;

    void calReader() {
        //reader function
        //reads the file
        //creates a vector of node
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
    }

    //sort nodes by date
    void dateSort() {
        cout < "I created functionality buahahaha";
    };
    //sort by length;


    void classSort(string courseCode) {
        //iterate through and print all items for a specific class
    }
    //display based by class

};
