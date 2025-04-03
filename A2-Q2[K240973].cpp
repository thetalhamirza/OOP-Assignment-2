#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ghost {
    protected:
    string workerName;
    int scareLevel;
    public:
    Ghost(string w, int s) : workerName(w), scareLevel(s) {}
    
    virtual void haunt() = 0;

    friend ostream& operator<<(ostream& os, Ghost& obj) {
        os << "Worker Name: " << obj.workerName << ", Scare Level: " << obj.scareLevel << endl;
        return os;
    }

    int getScareLevel() {return scareLevel;}
    // ***
};

class Poltergeist : virtual public Ghost {
    public:
    Poltergeist(string w, int s) : Ghost(w,s) {}
    void haunt() override {cout << "Poltergeist is moving objects!" << endl;}
    Poltergeist* operator+(Poltergeist& other) {
        return new Poltergeist(workerName + " and " + other.workerName, scareLevel + other.getScareLevel());
    }
};

class Banshee : public Ghost {
    public:
    Banshee(string w, int s) : Ghost(w,s) {}
    void haunt() override {cout << "Banshee is screaming loudly!" << endl;}
    Banshee* operator+(Banshee& other) {
        return new Banshee(workerName + " and " + other.workerName, scareLevel + other.getScareLevel());
    }
};

class ShadowGhost : virtual public Ghost {
    public:
    ShadowGhost(string w, int s) : Ghost(w,s) {}
    void haunt() override {cout << "ShadowGhost is whispering creepily!" << endl;}
    ShadowGhost* operator+(ShadowGhost& other) {
        return new ShadowGhost(workerName + " and " + other.workerName, scareLevel + other.getScareLevel());
    }
};

class ShadowPoltergeist : public ShadowGhost, public Poltergeist {
    public:
    ShadowPoltergeist(string w, int s) : ShadowGhost(w,s), Poltergeist(w,s), Ghost(w,s) {}
    void haunt() override {
        cout << "ShadowPoltergeist is whispering creepily and moving objects!" << endl;
    }
    ShadowPoltergeist* operator+(ShadowPoltergeist& other) {
        return new ShadowPoltergeist(workerName + " and " + other.workerName, scareLevel + other.getScareLevel());
    }
};

class HauntedHouse {
    string name;
    Ghost* ghosts[10];
    int ghostCount = 0;
    public:
    HauntedHouse(string n) : name(n) {}
    void addGhost(Ghost* ghost) {
        if (ghostCount < 10) {
            ghosts[ghostCount++] = ghost;
        }
    }
    void startHaunting() {
        cout << "\nHaunted House: " << name << " begins haunting!" << endl;
        for (int i = 0; i < ghostCount; i++) {
            ghosts[i]->haunt();
        }
        cout << endl;
    }
    string getName() {return name;}
    Ghost* getGhost(int index) {return ghosts[index];}
    int getGhostCount() {return ghostCount;}
};

class Visitor {
    string name;
    int bravery;
    public:
    Visitor(string n, int b) : name(n), bravery(b) {}
    void reactToHaunting(int scareLevel) {
        if (scareLevel < bravery - 2) {cout << name << " laughs at the ghosts!" << endl;}
        else if (scareLevel > bravery + 2) {cout << name << " screams and runs away!" << endl;}
        else {cout << name << " is shaken but stays!" << endl;}
    }
    int getBravery() {return bravery;}
};

void Visit(Visitor* visitors, int numV, HauntedHouse& house) {
    cout << "\nVisitors are entering " << house.getName() << "..." << endl;

    for (int i=0; i<numV ; i++) {
        int totalScare = 0;
        for (int j=0; j < house.getGhostCount(); j++) {
            totalScare += house.getGhost(j)->getScareLevel();
        }
        visitors[i].reactToHaunting(totalScare);
    }
}

int main() {
    srand(time(0));

    cout << "\nStudent ID: K240973" << endl;
    cout << "Name: Talha Mirza\n" << endl;

    
    HauntedHouse house1("Banshee's Lair");
    HauntedHouse house2("Ghostly Manor");

    house1.addGhost(new Poltergeist("Asad", rand() % 10 + 1));
    house1.addGhost(new Banshee("Sarah", rand() % 10 + 1));

    house2.addGhost(new ShadowGhost("Laiba", rand() % 10 + 1));
    house2.addGhost(new ShadowPoltergeist("Izaan", rand() % 10 + 1));

    Visitor visitors[3] = {Visitor("Ali", 9), Visitor("Saeed", 6), Visitor("Affan", 3)};

    house1.startHaunting();
    Visit(visitors, 3, house1);

    house2.startHaunting();
    Visit(visitors, 3, house2);
}