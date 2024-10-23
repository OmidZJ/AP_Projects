#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;



vector<string> split(const string &str, char delimiter = ',') {
    vector<string> result;
    string temp;

    for (auto s = str.begin(); s != str.end(); ++s) {
        if (*s == delimiter) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += *s;
        }
    }

    // Add the last part after the final delimiter (if any)
    if (!temp.empty()) {
        result.push_back(temp);
    }

    return result;
}

map<string,vector<string>> readFromFile(const string& filename,map<string,vector<string>> maptemp) {
    ifstream file(filename);
    string line;

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {};
    }

    // Read the file line by line
    while (getline(file, line)) {
        vector<string> row,temp;
        row = split(line);
        for(auto i = row.begin()+1; i!=row.end();i++){
            temp.push_back(*i);
        }
        maptemp[row[0]] = temp;
    }

    for(auto name:maptemp){
            cout << name.first << " ";
            for(auto value:name.second){
                cout << value << " ";
            }
            cout << endl;    
    }
        //cars.clear();

    file.close(); // Close the file
    return maptemp;
}

void request_spot(string temp,map<string,vector<string>> car, map<string,vector<string>> park, map<string,vector<string>> cost){
    string size,type,id, static_price, price_per_day;

    size = car[temp][0];
    for(auto place:park){
        if ((place.second[0] == size) and (place.second[2] == "0")){
            id = place.first;
            type = place.second[1];
            static_price = cost[size][0];
            price_per_day = cost[size][1];
            cout << id << ": " << type << " " << static_price << " " << price_per_day << "\n";
        }
    }

}

void assign_spot(string temp, map<string,vector<string>> park){
    if(park[temp][2]=="0"){
        park[temp][2] = "1";
        cout << "Spot " << temp << " is occupied now." << endl;
    }
}

void checkout(){
    cout << "\n";
}

int main(){
    string command,temp;
    map<string,vector<string>> cars,parking,costs;
    
    cars = readFromFile("cars",cars);

    parking = readFromFile("parking",parking);
    for(auto i:parking){
        parking[i.first].push_back("0"); // for empty
    }
    
    costs = readFromFile("costs",costs);

    while (cin >> command) {
        if (command == "request_spot") {
            cin >> temp;
            request_spot(temp, cars, parking, costs);
            cout << "\n";
        } else if (command == "assign_spot") {
            cin >> temp;
            assign_spot(temp,parking);
            cout << "\n";
        } else if (command == "checkout") {
            checkout();
            cout << "\n";
        } else if (command == "exit") {
            break;
        }
    }
    return 0;
}
