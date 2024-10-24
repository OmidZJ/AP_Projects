#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
const char delimiter = ',';

map<string, vector<string>> cars, parking, pcosts, ppcosts;
map<string, map<string, vector<string>>> costs;

vector<string> split(const string &str);
map<string, vector<string>> readFromFile(const string &filename, map<string, vector<string>> maptemp);
void request_spot(string temp);
void assign_spot(string temp);
void checkout(string temp);
void pass_time(string temp);
void update_costs();
void initializing(string icars, string iparking, string ipcosts);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " param1 param2 param3" << endl;
        return 1;
    }

    string command, temp;

    initializing(argv[1], argv[2], argv[3]);

    while (cin >> command)
    {
        if (command == "request_spot")
        {
            cin >> temp;
            request_spot(temp);
        }
        else if (command == "assign_spot")
        {
            cin >> temp;
            assign_spot(temp);
        }
        else if (command == "checkout")
        {
            cin >> temp;
            checkout(temp);
        }
        else if (command == "pass_time")
        {
            cin >> temp;
            pass_time(temp);
        }
        else if (command == "exit")
        {
            break;
        }
    }
    return 0;
}

vector<string> split(const string &str)
{
    vector<string> result;
    string temp;

    for (auto s = str.begin(); s != str.end(); ++s)
    {
        if (*s == delimiter)
        {
            result.push_back(temp);
            temp.clear();
        }
        else
        {
            temp += *s;
        }
    }

    if (!temp.empty())
    {
        result.push_back(temp);
    }

    return result;
}

map<string, vector<string>> readFromFile(const string &filename, map<string, vector<string>> maptemp)
{
    ifstream file(filename);
    string line;

    // Check if the file is open
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return {};
    }

    // Read the file line by line
    while (getline(file, line))
    {
        vector<string> row, temp;
        row = split(line);
        for (auto i = row.begin() + 1; i != row.end(); i++)
        {
            temp.push_back(*i);
        }
        maptemp[row[0]] = temp;
    }



    file.close(); // Close the file
    return maptemp;
}

void request_spot(string temp)
{
    string size, type, id, static_price, price_per_day;

    size = cars[temp][0];
    for (auto place : parking)
    {
        if ((place.second[0] == size) and (place.second[2] == "0"))
        {
            id = place.first;
            type = place.second[1];

            static_price = costs[type][size][0];
            price_per_day = costs[type][size][1];

            cout << id << ": " << type << " " << static_price << " " << price_per_day << "\n";
        }
    }
}

void assign_spot(string temp)
{
    if (parking[temp][2] == "0")
    {
        parking[temp][2] = "1";
        cout << "Spot " << temp << " is occupied now." << endl;
    }
    update_costs();
}

void checkout(string temp)
{
    if (parking[temp][2] == "1")
    {
        parking[temp][2] = "0";
        cout << "Spot " << temp << " is free now." << endl;
        cout << "Total cost: " << parking[temp][3] << endl;
    }
}

void pass_time(string temp)
{

    for (auto i : parking)
    {
        if (parking[i.first][2] == "1")
        {
            parking[i.first][4] = to_string(stoi(parking[i.first][4]) + stoi(temp));
        }
    }
    update_costs();
}

void update_costs()
{
    for (auto i : parking)
    {
        if (i.second[2] == "1")
        {
            parking[i.first][3] = to_string(stoi(costs[i.second[1]][i.second[0]][0]) + stoi(costs[i.second[1]][i.second[0]][1]) * stoi(i.second[4]));
        }
    }
}

void initializing(string icars, string iparking, string ipcosts)
{
    cars = readFromFile(icars, cars);

    parking = readFromFile(iparking, parking);
    for (auto i : parking)
    {
        parking[i.first].push_back("0"); // for empty
        parking[i.first].push_back("0"); // for costs
        parking[i.first].push_back("0"); // for days
    }

    pcosts = readFromFile(ipcosts, pcosts);
    ppcosts = pcosts;
    costs["normal"] = pcosts;

    for (auto i : pcosts)
    {
        pcosts[i.first] = {to_string(stoi(i.second[0]) + 50), to_string(stoi(i.second[1]) + 30)};
        ppcosts[i.first] = {to_string(stoi(i.second[0]) + 80), to_string(stoi(i.second[1]) + 60)};
    }
    costs["covered"] = pcosts;
    costs["CCTV"] = ppcosts;
}
