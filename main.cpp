#include <iostream>
#include <string>
#include <vector>
#include "schedule.cpp"
#include "schedule.h"

//runs a menu of what the user would like to do
void menu() {
    //welcome
    //view class list
    //choose what to do
        //sort by date
        //sort by data & length
        //sort by course & data?
}

using namespace std;

int main() {

    //if using main to test plz tag your work and commit/push often

    Schedulize obj;
    obj.tasks; //vector of nodes

    //I hard coded some task, try and sort them
      obj.calReader(); // testing function -J
 //   obj.dateSort();// -J
      obj.showTasks(obj.tasks); //- M
  // obj.classBros();
    //obj.classSort("_course1"); //- G

}
