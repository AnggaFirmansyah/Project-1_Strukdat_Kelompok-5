#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

struct Product {
    int id;
    string label;
    int attr_1; // harga
    int attr_2; // ulasan
};

// Fungsi mengecek dominasi (apakah p1 mendominasi p2)
bool dominates(const Product& p1, const Product& p2) {
    return (p1.attr_1 <= p2.attr_1 && p1.attr_2 >= p2.attr_2) &&
           (p1.attr_1 < p2.attr_1 || p1.attr_2 > p2.attr_2);
}

void process(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    vector<Product> products;
    int total_attr1 = 0;
    int total_attr2 = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Product p;

        getline(ss, token, ','); p.id = stoi(token);
        getline(ss, token, ','); p.label = token;
        getline(ss, token, ','); p.attr_1 = stoi(token);
        getline(ss, token, ','); p.attr_2 = stoi(token);

        products.push_back(p);
        total_attr1 += p.attr_1;
        total_attr2 += p.attr_2;
    }

    // Skyline Query menggunakan array
    vector<Product> skyline;
    for (const auto& p : products) {
        bool is_dominated = false;
        for (const auto& s : skyline) {
            if (dominates(s, p)) {
                is_dominated = true;
                break;
            }
        }
        if (!is_dominated) {
            // Hapus semua yang didominasi oleh p
            vector<Product> temp;
            for (const auto& s : skyline) {
                if (!dominates(p, s)) {
                    temp.push_back(s);
                }
            }
            temp.push_back(p);
            skyline = temp;
        }
    }

    cout << "Jumlah baris diproses: " << products.size() << endl;
    cout << "Total keseluruhan attr_1: " << total_attr1 << endl;
    cout << "Total keseluruhan attr_2: " << total_attr2 << endl;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    process("dataset.csv");
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;
    return 0;
}
