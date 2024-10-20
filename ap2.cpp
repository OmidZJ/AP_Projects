#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<string,vector<string>> cars;

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

void readFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Read the file line by line
    while (getline(file, line)) {
        vector<string> row,temp;
        row = split(line);
        for(auto i = row.begin()+1; i!=row.end();i++){
            temp.push_back(*i);
        }
        cars[row[0]] = temp;
    }

    for(auto name:cars){
            cout << name.first << " ";
            for(auto value:name.second){
                cout << value << " ";
            }
            cout << endl;    
    }
        cars.clear();

    file.close(); // Close the file
}

void request_spot(){
    cout << "\n";
}
void assign_spot(){
    cout << "\n";
}

void checkout(){
    cout << "\n";
}

int main(){
    string command;
    readFromFile("cars");
    readFromFile("parking");
    readFromFile("costs");

    while (cin >> command) {
        if (command == "request_spot") {
            request_spot();
            cout << "\n";
        } else if (command == "assign_spot") {
            assign_spot();
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
