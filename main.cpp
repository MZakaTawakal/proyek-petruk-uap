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
    }
    if (conqueredRight && right) {
        log.push_back(string(root->name) + " menggabungkan " + right->name);
        root->stats.population += right->stats.population;
        root->stats.strength += right->stats.strength;
    }

    return root;
}

int main() {
    vector<string> logHasil;

    Territory* A = new Territory("A", 100, 30);
    Territory* B = new Territory("B", 150, 40);
    Territory* Root = new Territory("Root", 300, 50);

    Root->left = A;
    Root->right = B;

    conquerAndCombine(Root, logHasil);

    for (const string& log : logHasil) {
        cout << log << endl;
    }

    delete A;
    delete B;
    delete Root;

    return 0;
}
