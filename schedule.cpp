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
