#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <chrono>
using namespace std;

struct Baju {
    int id;
    string label;
    int harga;
    int ulasan;
};

bool mendominasi(Baju A, Baju B) {
    return (A.harga <= B.harga && A.ulasan >= B.ulasan) &&
           (A.harga < B.harga || A.ulasan > B.ulasan);
}

vector<Baju> skylineQueryQueue(const vector<Baju>& data) {
    queue<Baju> q;
    vector<Baju> skyline;

    for (const auto& baju : data) {
        q.push(baju);
    }

    while (!q.empty()) {
        Baju kandidat = q.front();
        q.pop();
        bool didominasi = false;

        for (auto& s : skyline) {
            if (mendominasi(s, kandidat)) {
                didominasi = true;
                break;
            }
        }

        if (!didominasi) {
            vector<Baju> baru;
            for (auto& s : skyline) {
                if (!mendominasi(kandidat, s)) {
                    baru.push_back(s);
                }
            }
            baru.push_back(kandidat);
            skyline = baru;
        }
    }

    return skyline;
}

int main() {
    ifstream file("ind_1000_2_product.csv");
    vector<Baju> data;
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, label, harga_str, ulasan_str;
        getline(ss, id_str, ',');
        getline(ss, label, ',');
        getline(ss, harga_str, ',');
        getline(ss, ulasan_str, ',');

        Baju b;
        b.id = stoi(id_str);
        b.label = label;
        b.harga = stoi(harga_str);
        b.ulasan = stoi(ulasan_str);
        data.push_back(b);
    }

    auto start = chrono::high_resolution_clock::now();

    vector<Baju> hasil = skylineQueryQueue(data);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    cout << "Produk-produk yang masuk skyline:\n";
    for (auto& b : hasil) {
        cout << b.label << " | Harga: " << b.harga << " | Ulasan: " << b.ulasan << endl;
    }

    cout << "\nWaktu eksekusi: " << elapsed.count() << " ms" << endl;

    return 0;
}