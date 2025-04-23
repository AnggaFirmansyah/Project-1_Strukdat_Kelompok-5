#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;

struct Baju {
    int id;
    string label;
    int harga;
    int ulasan;
};

bool domination (Baju A, Baju B) {
    return (A.harga <= B.harga && A.ulasan >= B.ulasan) &&
           (A.harga < B.harga || A.ulasan > B.ulasan);
}

vector<Baju> skylineQueryQueueVector(vector<Baju>& data) {
    vector<Baju> queue = data;  // menggunakan vector sebagai queue
    vector<Baju> skyline;

    while (!queue.empty()) {
        Baju kandidat = queue.front();       // ambil elemen di depan (Head)
        queue.erase(queue.begin());          // hapus elemen pertama (FIFO)

        bool dominated = false;
        for (auto& s : skyline) {
            if (domination(s, kandidat)) {
                dominated = true;
                break;
            }
        }

        if (!dominated) {
            vector<Baju> baru;
            for (auto& s : skyline) {
                if (!domination(kandidat, s)) {
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
    string line;
    getline(file, line); // skip header

    vector<Baju> data;
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
    vector<Baju> hasil = skylineQueryQueueVector(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durasi = end - start;

    cout << "Skyline Set (menggunakan Queue - Vector):\n";
    for (auto& b : hasil) {
        cout << b.label << " | Harga: " << b.harga << " | Ulasan: " << b.ulasan << endl;
    }

    cout << "\nWaktu eksekusi: " << durasi.count() << " ms" << endl;

    return 0;
}