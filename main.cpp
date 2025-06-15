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

Territory* conquerAndCombine(Territory* root, vector<string>& log) {
    if (!root) return nullptr;

    Territory* left = conquerAndCombine(root->left, log);
    Territory* right = conquerAndCombine(root->right, log);

    bool conqueredLeft = true, conqueredRight = true;

    if (left && left->stats.strength > root->stats.strength) {
        log.push_back(string(root->name) + " gagal menaklukkan " + left->name);
        conqueredLeft = false;
    }
    if (right && right->stats.strength > root->stats.strength) {
        log.push_back(string(root->name) + " gagal menaklukkan " + right->name);
        conqueredRight = false;
    }

    if (conqueredLeft && left) {
        log.push_back(string(root->name) + " menggabungkan " + left->name);
        root->stats.population += left->stats.population;
        root->stats.strength += left->stats.strength;
        root->left = nullptr;
    }
    if (conqueredRight && right) {
        log.push_back(string(root->name) + " menggabungkan " + right->name);
        root->stats.population += right->stats.population;
        root->stats.strength += right->stats.strength;
        root->right = nullptr;
    }

    return root;
}

Territory* createSampleWorld(queue<Territory*>& wilayahQueue) {    
    int a, b;
    cout<<"Selamat datang di program divide and conquer wilayah\n";
    cout<<"Masukkan jumlah populasi kerajaan Anda: ";
    cin>>a;
    cout<<"Masukkan tingkat kekuatan kerajaan Anda: ";
    cin>>b;

    const char* names[] = {"North1", "North2", "South1", "South2", "East", "West", "Kingdom"};
    int pops[] = {200, 150, 180, 170, 300, 280, a};
    int strn[] = {50, 60, 40, 45, 70, 65, b};

    list<Territory*> wilayahList;

    for (int i = 0; i < 7; i++) {
        Territory* t = new Territory(names[i], pops[i], strn[i]);
        wilayahList.push_back(t);
        wilayahQueue.push(t);
    }

    auto it = wilayahList.begin();
    Territory* N1 = *it++;
    Territory* N2 = *it++;
    Territory* S1 = *it++;
    Territory* S2 = *it++;
    Territory* East = *it++;
    Territory* West = *it++;
    Territory* Kingdom = *it++;

    East->left = N1;
    East->right = N2;
    West->left = S1;
    West->right = S2;
    Kingdom->left = East;
    Kingdom->right = West;

    return Kingdom;
}

void map(){
    cout<<"North1    North2\n";
    cout<<"  \\         /\n";
    cout<<"   \\       /\n";
    cout<<"    \\     /\n";
    cout<<"      East-------------Kingdom-------------West\n";
    cout<<"                                           /   \\\n";
    cout<<"                                          /     \\\n";
    cout<<"                                         /       \\\n";
    cout<<"                                      South1    South2\n";
}

int main() {
    vector<string> logHasil; 
    queue<Territory*> wilayahQueue;
    stack<string> riwayatReverse;

    map();
    Territory* root = createSampleWorld(wilayahQueue);

    cout << "\nMemulai penaklukan...\n\n";
    conquerAndCombine(root, logHasil);

    for (const string& line : logHasil) {
        cout << line << "\n";
        riwayatReverse.push(line);
    }

    cout << "\n--- Log dalam urutan terbalik (stack): ---\n";
    while (!riwayatReverse.empty()) {
        cout << riwayatReverse.top() << "\n";
        riwayatReverse.pop();
    }

    cout << "\n--- Daftar semua wilayah (queue): ---\n";
    while (!wilayahQueue.empty()) {
        Territory* t = wilayahQueue.front();
        wilayahQueue.pop();
        cout << t->name << ", Populasi: " << t->stats.population
             << ", Kekuatan: " << t->stats.strength << "\n";
    }

    return 0;
}
