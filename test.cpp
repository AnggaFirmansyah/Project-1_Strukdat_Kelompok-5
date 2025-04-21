#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
using namespace std;

void process(const string& filename) {
    ifstream file(filename);
    string line;
    int total_rows = 0;
    long long total_attr1 = 0;
    long long total_attr2 = 0;

    // Skip header
    getline(file, line);

    // Baca setiap baris
    while (getline(file, line)) {
        stringstream ss(line);
        string id, label, attr1, attr2;
        getline(ss, id, ',');
        getline(ss, label, ',');
        getline(ss, attr1, ',');
        getline(ss, attr2, ',');

        total_attr1 += stoi(attr1);
        total_attr2 += stoi(attr2);
        total_rows++;
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
