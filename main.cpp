#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <cstring> 
using namespace std;

struct Stats {
    int population;
    int strength;
};

class Territory {
public:
    char name[20];
    Stats stats; 
    Territory* left;
    Territory* right;

    Territory(const char* n, int pop, int str) : left(nullptr), right(nullptr) {
        strcpy(name, n);
        stats.population = pop;
        stats.strength = str;
    }
};

void map(){
    cout<<"North1    North2"<<endl;
    cout<<"  \\         /"<<endl;
    cout<<"   \\       /"<<endl;
    cout<<"    \\     /"<<endl;
    cout<<"      East-------------Kingdom-------------West"<<endl;
    cout<<"                                           /   \\"<<endl;
    cout<<"                                          /     \\"<<endl;
    cout<<"                                         /       \\"<<endl;
    cout<<"                                      South1    South2"<<endl;
}


struct Territory {
    string name;
    int population;
    int strength;
    Territory* left;
    Territory* right;

    Territory(string n, int p, int s)
        : name(n), population(p), strength(s), left(nullptr), right(nullptr) {}
};

Territory* conquerAndCombine(Territory* root) {
    if (!root) return nullptr;

    Territory* left = conquerAndCombine(root->left);
    Territory* right = conquerAndCombine(root->right);

    bool conqueredLeft = true, conqueredRight = true;

    // Conquer: Cek apakah anak bisa ditaklukkan
    if (left) {
        if (left->strength > root->strength) {
            cout << "Gagal menaklukkan " << left->name << " dari " << root->name << ".\n";
            conqueredLeft = false;
        } else {
            cout << root->name << " berhasil menggabungkan " << left->name << ".\n";
            root->population += left->population;
            root->strength += left->strength;
            root->left = nullptr;
        }
    }

    if (right) {
        if (right->strength > root->strength) {
            cout << "Gagal menaklukkan " << right->name << " dari " << root->name << ".\n";
            conqueredRight = false;
        } else {
            cout << root->name << " berhasil menggabungkan " << right->name << ".\n";
            root->population += right->population;
            root->strength += right->strength;
            root->right = nullptr;
        }
    }

    cout << "Status " << root->name << " → Populasi: " << root->population
         << ", Kekuatan: " << root->strength << "\n\n";

    return root;
}

Territory* createSampleWorld() {
    Territory* N1 = new Territory("North1", 200, 50);
    Territory* N2 = new Territory("North2", 150, 60);
    Territory* N3 = new Territory("South1", 180, 40);
    Territory* N4 = new Territory("South2", 170, 45);

    Territory* East = new Territory("East", 300, 70);
    Territory* West = new Territory("West", 280, 65);

    East->left = N1;
    East->right = N2;
    West->left = N3;
    West->right = N4;

    Territory* Kingdom = new Territory("Kingdom", 500, 80);
    Kingdom->left = East;
    Kingdom->right = West;

    return Kingdom;
}

int main() {
    map();
    Territory* world = createSampleWorld();
    cout << "Memulai proses penaklukan dan penggabungan wilayah...\n\n";
    conquerAndCombine(world);
    cout << "\nProses selesai. Total akhir:\n";
    cout << "Wilayah: " << world->name << "\nPopulasi: " << world->population
         << "\nKekuatan: " << world->strength << "\n";
    return 0;
}
