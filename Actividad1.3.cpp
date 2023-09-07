#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


double convertIP(string s){
  string substring;
  char delimeter = '.';
  stringstream s2(s);
  double total;
  int count = 3;
  
  while(getline(s2,substring,delimeter)){
    double num = stoi(substring);
    total = total + (num * pow(256,count));
    count--;
  }

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

  string IPFull = substrings[1];
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

int first(vector<LogEntry> logs, int low, int high, double key)
{
    int ans = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        double midVal = logs[mid].IPRaw;
 
        if (midVal < key) {
            low = mid + 1;
        }
        else if (midVal > key) {
            high = mid - 1;
        }
        else if (midVal == key) {
            ans = mid;
            high = mid - 1;
        }
    }
 
    return ans;
}

int last(vector<LogEntry> logs, int low, int high, double key)
{
    int ans = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        double midVal = logs[mid].IPRaw;
 
        if (midVal < key) {
            low = mid + 1;
        }
        else if (midVal > key) {
            high = mid - 1;
        }
        else if (midVal == key) {
            ans = mid;
            low = mid + 1;
        }
    }
 
    return ans;
}

int total(vector<LogEntry>  logs, int low, int high, double key){
    int answer = 0;

    int top = last(logs,low,high,key);
    int bottom = first(logs,low,high,key);

    if(top  < 0 || bottom < 0){
        return answer;
    }

    answer = top - bottom;
    return answer;
}

int main() {
    vector<string> entries = readFile("bitacoraelb.txt");
    vector<LogEntry> logs;
    
    for(int i = 0; i < entries.size(); i++){
        LogEntry curr(entries[i]);
        logs.push_back(curr);
    }

    quicksort(logs, 0, logs.size() -1);

    for(int i = 0; i < 5; i++){
        cout << logs[i].entry << endl;
    }

    double low = convertIP("0.0.142.26");
    double high = convertIP("0.18.36.48");

    int ind_low = first(logs,0,logs.size(),low);
    int ind_high = last(logs,0,logs.size(),high);

    cout << ind_low << " and then " << ind_high;
}