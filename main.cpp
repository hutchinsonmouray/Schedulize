#include <iostream>
#include <string>
#include <vector>
#include "schedule.cpp"
#include "schedule.h"
#include "visual.h"


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
    //??
    Schedulize obj;
    obj.tasks;
    ifstream file("Schedulize your Calender!.txt");
    string read;
    getline(file, read);
    char c;
    int counter = 0;
    vector<char> tempChars;
    while (file.get(c))
    {
        if (c == ':')
        {
            file.get(c);
            break;
        }
    }
    file.get(c);
    if ((c-'0') == 1)
        obj.Zoom = true;
    while (file.get(c))
    {
        if (c == ':')
        {
            file.get(c);
            break;
        }
    }
    file.get(c);
    if ((c-'0') == 0)
        obj.Date = false;
    while (file.get(c))
    {
        if (c == ':')
        {
            file.get(c);
            break;
        }
    }
    file.get(c);
    if ((c-'0') == 0)
        obj.Class = false;
    while (file.get(c))
    {
        if (c == ':')
        {
            file.get(c);
            break;
        }
    }
    file >> read;

    obj.startDate = read;
    while (file.get(c))
    {
        if (c == ':')
        {
            file.get(c);
            break;
        }
    }
    file >> read;
    obj.endDate = read;










    //Schedulize obj;
   // obj.tasks; //vector of nodes

    //I hard coded some task, try and sort them
    //  obj.calReader(); // testing function -J
 //   obj.dateSort();// -J
      obj.showTasks(obj.tasks); //- M
  // obj.classBros();
  if (obj.Class)
      //obj.classBros();
    obj.classSortf(obj.tasks);//- G

    obj.exportToCSV(); //-M
   // obj.classBros();
}
