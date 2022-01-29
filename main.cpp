#include <iostream>
#include <string>
#include <vector>
#include "schedule.cpp"
#include "schedule.h"

using namespace std;

int main() {
    Schedulize obj;
    obj.tasks; //vector of nodes

    //I hard coded some task, try and sort them
    obj.calReader(); // testing function
    obj.dateSort();

}
