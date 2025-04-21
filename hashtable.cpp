#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <chrono>
using namespace std;

struct AttrSums {
    long long attr1_sum = 0;
    long long attr2_sum = 0;
};

void process(const string& filename) {
    ifstream file(filename);
    string line;
    unordered_map<string, AttrSums> labelMap;
    int total_rows = 0;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string id, label, attr1, attr2;
        getline(ss, id, ',');
        getline(ss, label, ',');
        getline(ss, attr1, ',');
        getline(ss, attr2, ',');

        labelMap[label].attr1_sum += stoi(attr1);
        labelMap[label].attr2_sum += stoi(attr2);
        total_rows++;
    }
    long long total_attr1 = 0;
    long long total_attr2 = 0;

    for (const auto& entry : labelMap) {
        total_attr1 += entry.second.attr1_sum;
        total_attr2 += entry.second.attr2_sum;
    }

    cout << "Jumlah baris diproses: " << total_rows << endl;
    cout << "Total attr_1: " << total_attr1 << endl;
    cout << "Total attr_2: " << total_attr2 << endl;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    process("ind_500_2_product.csv");
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;
    return 0;
}
