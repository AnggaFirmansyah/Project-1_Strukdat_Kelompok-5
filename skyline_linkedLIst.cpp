#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Product {
    int id;
    int price;
    int review;
};

// Fungsi untuk membaca dataset dari file CSV
vector<Product> readDataset(const string& filename) {
    vector<Product> products;
    ifstream file(filename);
    string line;

    // Lewati header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Product p;

        getline(ss, token, ',');
        p.id = stoi(token);
        getline(ss, token, ','); // Lewati label
        getline(ss, token, ',');
        p.price = stoi(token);
        getline(ss, token, ',');
        p.review = stoi(token);

        products.push_back(p);
    }

    return products;
}

// Fungsi Skyline Query dengan Linked List
list<Product> skylineLinkedList(const list<Product>& products) {
    list<Product> skyline;

    for (const auto& p : products) {
        bool dominated = false;

        for (const auto& s : skyline) {
            // Cek apakah p didominasi oleh produk dalam skyline
            if (s.price <= p.price && s.review >= p.review) {
                dominated = true;
                break;
            }
        }

        if (!dominated) {
            // Hapus produk dalam skyline yang didominasi oleh p
            skyline.remove_if([&p](const Product& s) {
                return p.price <= s.price && p.review >= s.review;
            });
            skyline.push_back(p);
        }
    }

    return skyline;
}

int main() {
    // Baca dataset
    vector<Product> products = readDataset("ind_1000_2_product.csv");

    // Konversi ke Linked List
    list<Product> productList(products.begin(), products.end());

    // Jalankan Skyline Query dan ukur waktu
    auto start = high_resolution_clock::now();
    list<Product> skyline = skylineLinkedList(productList);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // Output hasil
    cout << "Skyline Products (Linked List):" << endl;
    for (const auto& p : skyline) {
        cout << "ID: " << p.id << ", Price: " << p.price << ", Review: " << p.review << endl;
    }

    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}