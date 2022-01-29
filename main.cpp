#include <iostream>
#include <string>
#include <vector>
#include "schedule.cpp"
#include "schedule.h"

using namespace std;

int main() {

    //if using main to test plz tag your work and commit/push often

    Schedulize obj;
    obj.tasks; //vector of nodes

    //I hard coded some task, try and sort them
 //   obj.calReader(); // testing function -J
 //   obj.dateSort();// -J
    obj.showTasks(obj.tasks); //- M

}
