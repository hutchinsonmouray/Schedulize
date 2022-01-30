#include <string>
#include <vector>
#include "schedule.cpp"

using namespace std;

int main() {

    Schedulize obj;
    obj.tasks;
    ifstream file("Schedulize your Calendar!.txt");
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

  if (obj.Class)
    obj.classSortf(obj.tasks);

    obj.exportToCSV();
}
