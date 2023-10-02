#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


double convertIP(string s){
  string substring = "";
  char delimeter = '.';
  stringstream s2(s);
  double total = 0;
  int count = 3;
  
  while(getline(s2,substring,delimeter)){
    double num = stoi(substring);
    total = total + (num * pow(256,count));
    count--;
  }

  s2.clear();
  return total;
}

class LogEntry {  
    public:
        LogEntry(string);
        LogEntry(int);
        string entry;
        double IPRaw;
        string IPFull;
};

LogEntry :: LogEntry(int err){
    entry = "NA";
    IPRaw = 0;
    IPFull = "NA";
}
LogEntry ::LogEntry(string l) {
  entry = l;
  stringstream ss(l);
  vector<string> substrings;
  string substring;
  char delimeter = '|';

  while (getline(ss, substring, delimeter)) {
    substrings.push_back(substring);
  }

  IPFull = substrings[1];
  IPFull = IPFull.substr(5);

  IPRaw = convertIP(IPFull);
}

vector<string> readFile(string fileName){

    vector<string> entries;
    ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        
        return entries;
    }

    string line;

    while (getline(file, line)) {
       entries.push_back(line);
    }

    file.close();

    return entries;
}

void quicksort(vector<LogEntry>& logs, int left, int right) {
    if (left < right) {
        int i = left, j = right;
        LogEntry pivot = logs[(i + j) / 2];

        while (i <= j) {
            while (logs[i].IPRaw < pivot.IPRaw)
                i++;
            while (logs[j].IPRaw > pivot.IPRaw)
                j--;
            if (i <= j) {
                swap(logs[i], logs[j]);
                i++;
                j--;
            }
        }

        quicksort(logs, left, j);
        quicksort(logs, i, right);
    }
}

vector<int> findRange(vector<LogEntry> logs, string low, string high){
    
    vector<int> result = {-1, -1};

        // Find the first occurrence of target
        double l = convertIP(low);
        int left = 0;
        int right = logs.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (logs[mid].IPRaw == l) {
                result[0] = mid;
                right = mid - 1;  // Continue searching on the left side
            } else if (logs[mid].IPRaw < l) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Find the last occurrence of target
        double h = convertIP(high);
        left = 0;
        right = logs.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (logs[mid].IPRaw == h) {
                result[1] = mid;
                left = mid + 1;   // Continue searching on the right side
            } else if (logs[mid].IPRaw < h) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
}

int main() {
    vector<string> entries = readFile("bitacoraelb.txt");
    vector<LogEntry> logs;
    
    for(int i = 0; i < entries.size(); i++){
        LogEntry curr(entries[i]);
        logs.push_back(curr);
    }

    quicksort(logs, 0, logs.size() -1);

    vector<string> bot_top(2);
    
    cout << "ENTER TWO VALID IPs to be searched" << endl << "Enter lower bound" << endl;
    cin >> bot_top[0];
    cin.clear();

    cout << endl << "Enter higher bound" << endl;
    cin >> bot_top[1];
    cin.clear();
    
    vector<double> lohigh(2);

    for(int i = 0; i < bot_top.size(); i++){
        lohigh[i] = convertIP(bot_top[i]);
    }

    vector<int> range = findRange(logs, bot_top[0], bot_top[1]);
    
    cout <<endl << range[0] << "   " << range[1];
    if(range[0] <= range[1] && range[0] > -1 && range[1] > -1){
        for(int i = range[0]; i <= range[1]; i++){
            cout << logs[i].entry << endl;
        }
    }
    else{
        cout << "NO VALID IP DETECTED";
    }

    ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        for (int i = 0; i < logs.size(); i++) {
            outputFile << logs[i].entry << endl; // Write each string followed by a newline
        }
        outputFile.close(); // Close the file stream
        cout << "File 'output.txt' has been successfully written." << std::endl;
    } else {
        cerr << "Unable to open the file 'output.txt' for writing." << std::endl;
    }
    
}