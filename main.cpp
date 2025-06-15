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

int main() {
    map();  // hanya menampilkan peta
    return 0;
}
