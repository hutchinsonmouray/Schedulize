#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include<algorithm>
using namespace std;
//node structure
struct node {
    unsigned int date = 0; //due date format 0123 aka Jan 23rd
    string descrip = "";  //description DESCRIPTION: -> LOCATION:
    string title = ""; //title  SUMMARY: -> [
    string course = "";  //course - [ART1010C]
    unsigned int length = 1; //how long it'll take

    node() {
    }

    node(unsigned int _date, string _descrip,string _title,string _course, unsigned int _length) {
        date = _date;
        descrip= _descrip;
        title = _title;
        length = _length;
        course = _course;

    }
};

//assignment class
class Schedulize {

public:
    string calOwner;
    unsigned int totalTask;
    vector<node>tasks;
    bool Zoom = false;
    bool Date = true;
    bool Class = true;
    string startDate = "0/0";
    string endDate = "0/0";


    Schedulize(){
        //calls the initial read when ready?
        calReader();
        //hardCodeNodes();
    }

    //reads calender and adds to tasks
    void calReader() {

        ifstream file("hm.ics");
        string data = "";
        string token = "";
        char c;
        int count = 0;
        vector<char> tempChars;
        while (file.get(c))
        {
            tempChars.push_back(c);
        }
        for (int i = 0; i < tempChars.size(); i++)
        {
            if ((i < tempChars.size() - 1) && tempChars[i] =='\n' && tempChars[i+1] == ' ')
            {
                i++;
                continue;
            }
            if ((i < tempChars.size() - 1) && tempChars[i] =='\\' && tempChars[i+1] == ',')
            {
                i++;
                continue;
            }
            if (i < tempChars.size())
                data += tempChars[i];
        }
        stringstream fileData(data);
        vector<vector<string>> events;
        while (fileData >> token) {
            vector<string> eventTokens = {};

            if (token == "BEGIN:VEVENT")
            {
                while (token != "END:VEVENT" && fileData >> token)
                {
                    eventTokens.push_back(token);
                }
                events.push_back(eventTokens);
            }
            else
            {
                while (token != "BEGIN:VEVENT" && fileData >> token)
                {
                    eventTokens.push_back(token);
                }
                events.push_back(eventTokens);
            }

        }
        for (int i = 0; i < events.size(); i++)
        {
            node* nTask = new node();
            for (int j = 0; j < events[i].size(); j++)
            {
                // gets course title
                if (events[i][j].find('[') != string::npos && events[i][j+1].find("URL") != string::npos)
                {
                    nTask->course = events[i][j].substr(1, events[i][j].length()-2);
                    //cout << events[i][j].substr(1, events[i][j].length()-2) << endl;
                }
                // gets the calendar owner
                if (events[i][j].find("user") != string::npos && i == 0)
                {
                    string name = "";
                    while (j < events[i].size()-2)
                    {
                        j++;
                        name = name + events[i][j] + " ";
                    }
                    calOwner = name;
                }
                // gets description of task
                if (events[i][j].find("DESCRIPTION:") != string::npos)
                {
                    string desc = "";
                    while (events[i][j].find("LOCATION:") == string::npos && events[i][j].find("SEQUENCE:") == string::npos )
                    {
                        desc = desc + events[i][j] + " ";
                        j++;
                    }
                    nTask->descrip = desc.substr(12,desc.length()-1);
                }
                // gets task
                if (events[i][j].find("SUMMARY:") != string::npos)
                {
                    string summar = "";
                    int tempCount = 0;
                    while (events[i][j].find('[') == string::npos)
                    {
                        summar = summar + events[i][j] + " ";
                        j++;
                        tempCount++;
                    }
                    nTask->title = summar.substr(8, summar.length()-1);
                    j-=tempCount;
                    // course fix
                }
                if (events[i][j].find("DTSTART:") != string::npos)
                {
                    string dayStr;
                    dayStr = events[i][j].substr(12, 4);
                    int dayNum = stoi(dayStr);
                    if (events[i][j][23] == 'Z')
                    {
                        if((stoi(events[i][j].substr(17,2)))-5 < 0)
                            dayNum--;
                    }
                    nTask->date = (unsigned int) dayNum;
                }
                if (events[i][j].find("DTSTART;") != string::npos)
                {
                    string dayStr;
                    dayStr = events[i][j].substr(23, 4);
                    int dayNum = stoi(dayStr);
                    if (events[i][j][34] == 'Z')
                    {
                        if((stoi(events[i][j].substr(17,2)))-5 < 0)
                            dayNum--;
                    }
                    nTask->date = (unsigned int) dayNum;
                }
                // Difficulty?
            }
            if (i != 0)
                tasks.push_back(*nTask);
        }

    }

    void exportToCSV(){
// opens an existing csv file or creates a new file.
        unsigned int finSt = 0;
        unsigned int finEnd = 0;
        stringstream stD(startDate);
        stringstream endD(endDate);
        string sDD, eDD, sMM, eMM;
        getline(stD, sDD, '/');
        getline(stD, sMM, '/');
        getline(endD, eDD, '/');
        getline(endD, eMM, '/');
        try
        {
            finSt = stoi(sDD) + stoi(sMM)*10;
            finEnd = stoi(eDD) + stoi(eMM)*10;
        }
        catch(const invalid_argument& e)
        {
        }


        std::ofstream file("Schedulize_toDo.csv");

        file <<"Welcome "<< calOwner << "\n";
        file << "Thank you for using Schedulize! Your customized schedule is below: \n";
        file << "\n";

        file << "Assignment, "
             <<  "Course, "
             <<  "Date, "
             <<  "Difficulty, "
             << "description"
             << "\n";

        for (auto iter = tasks.begin(); iter!= tasks.end();iter++) {
            if (!Zoom && iter->descrip.find("Zoom") != string::npos)
                continue;
            if (finSt == 0 && iter->date < finSt)
                continue;
            if (finEnd != 0 && iter->date > finEnd)
                continue;

            // Insert the data to file
            file << iter->title << ", "
                 << iter->course << ", "
                 << iter->date/100 << "/" << iter->date%100 <<  ", "
                 << iter->length << ", "
                 << iter->descrip
                 << "\n";
        }
        file.close();
    }

    //4 Function below sort by class
    void classSortf(vector<node>& _tasks){
        vector<node>* helper = & _tasks;
        vector<node> newTasks = dateSortTotal ( dateSort(helper));
        tasks.clear();
        tasks = newTasks;
    }
    //sort nodes by date (group) - finish later turns map all into one vector Done
    vector<node> dateSortTotal(map<string, vector<node>> mapOTasks){
        
        vector<node> finalSortTasks;
        
        //iterate through map and from each vector push onto new larger node * vector
        for (auto iter = mapOTasks.begin(); iter!=mapOTasks.end(); ++iter) {
            while (!iter->second.empty()) {
                finalSortTasks.push_back(iter->second.back());
                iter->second.pop_back();   
            }
        }
        
        return finalSortTasks;
    }
    map<string, vector<node>> dateSort(vector<node>* _tasks) {

        //creates a map with date  < 1/11 , <Hwk1 , hwk2 , etc >
        map<string, vector<node>> dailyTasks;
        for (auto iter = _tasks->rbegin(); iter!=_tasks->rend(); ++iter){
           string g = iter->course;
           dailyTasks[g].push_back(*iter);
        }

        return dailyTasks;

    };
    vector<string> classBros() {
        vector<string> courses;//return this?
        int counter = 0;
        for (unsigned int i = 0; i < tasks.size(); i++) {
            if (i == 0)
                courses.push_back(tasks[i].course);
            if (tasks[i].course == courses[counter])
                continue;
            else {
                courses.push_back(tasks[i].course);
                counter++;
            }

//HI
        }
        //sort(courses.begin(), courses.end(), gee);
        for (int i = 0; i< courses.size();i++)
        {
            cout<<courses[i];
        }
        return courses;
    }


    //TEST: hardcodes samples tasks
    void hardCodeNodes() { //ads 20 tester nodes to sort
        for (unsigned int i=20; i>15; i--) {
            node* temp = new node(i, "_descrip", "_atitle" ,"_course4",i+2) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=15;i>10;i--) {
            node* temp = new node(i, "_descrip", "_btitle" ,"_course1",i+4) ;
            tasks.push_back(*temp);
        }
        for (unsigned int i=10;i>0; i--) {
            node* temp = new node(i, "_descrip", "_ctitle" ,"_course10",i+3) ;
            tasks.push_back(*temp);
        }
        totalTask = tasks.size();
    }

    //for future use?
    vector<node> smallClassSort(string courseCode) {
        vector<node> newTask;


        for(unsigned int i = 0; i < totalTask; i++ )
        {
            if (tasks[i].course == courseCode) {
                newTask.push_back(tasks[i]);
            }
        }
        return newTask;
        //iterate through and print all items for a specific class
        return newTask;
    } //- gg :)
    void showTasks(vector<node> _tasks){
        for (auto iter = _tasks.begin(); iter != _tasks.end(); ++iter) {
            cout << iter ->course<<endl;
            cout << iter ->title <<endl;
            cout << iter ->descrip<<endl;
            cout << iter ->date <<endl;
            cout << iter ->length << endl;
            cout<<endl;
        }
    };
    void classSort() {
        vector<node>* newTask = new vector<node>;

        for(unsigned int j = 0; j < classBros().size(); j++)
        {
            for (unsigned int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].course == classBros()[j])
                {
                    newTask->push_back(tasks[i]);
                    //cout << "Date: " << tasks[i].date << "|" <<
                    //cout<< "Class: " << newTask[i].course;
                    // cout << tasks[i].title << "|" << "Description: " << tasks[i].descrip << endl;
                }
            }
        }

        tasks.clear();
        for(auto iter = newTask->begin(); iter != newTask->end(); iter++) {
            tasks.push_back(*iter);
        }


//iterate through and print all items for a specific class
    }
};

