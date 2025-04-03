# include <iostream>
# include <string>

using namespace std;

class Person {
    protected:
        string name;
        string ID;
        bool fees_paid;
        string stop;
    
    public:
        Person(string name, string ID, bool fees_paid, string stop)
            : name(name), ID(ID), fees_paid(fees_paid), stop(stop) {}
        
        virtual void viewDetails() const {
            cout << "Name: " << name << "\nID: " << ID << "\nStop: " << stop << "\n";
        }
        
        virtual bool payFees() = 0;
        string getStop() const { return stop; }
        string getID() const { return ID; }
};

class Student : public Person {
    int *Attendance;
    int days;

public:
    Student(string name, string ID, bool fees_paid, string stop, int days)
        : Person(name, ID, fees_paid, stop), days(days) {
        Attendance = new int[days];
    }

    ~Student() { delete[] Attendance; }
    void markAttendance(int day) { Attendance[day - 1] = 1; }
    bool payFees() override { return fees_paid; }
    void viewDetails() const override {
        cout << "---- Student Details ----\n";
        Person::viewDetails();
        cout << "Fees Paid: " << (fees_paid ? "Yes" : "No") << endl;
    }
};

class Teacher : public Person {
    public:
        Teacher(string name, string ID, bool fees_paid, string stop)
            : Person(name, ID, fees_paid, stop) {}
        bool payFees() override { return fees_paid; }
        void viewDetails() const override {
            cout << "---- Teacher Details ----\n";
            Person::viewDetails();
            cout << "Fees Paid: " << (fees_paid ? "Yes" : "No") << endl;
        }
};

class StaffMember : public Person {
    public:
        StaffMember(string name, string ID, bool fees_paid, string stop)
            : Person(name, ID, fees_paid, stop) {}
        bool payFees() override { return fees_paid; }
        void viewDetails() const override {
            cout << "---- Staff Details ----\n";
            Person::viewDetails();
            cout << "Fees Paid: " << (fees_paid ? "Yes" : "No") << "\n";
        }
};

class Bus {
    string name;
    static int counter;
    int id;
    int max_stops, max_passengers, current_passengers;
    string* busStops;
    Person** passengers;

public:
    Bus(string name, int max_stops, int max_passengers)
        : name(name), max_stops(max_stops), max_passengers(max_passengers) {
        id = counter++;
        busStops = new string[max_stops];
        passengers = new Person*[max_passengers];
        current_passengers = 0;
    }

    ~Bus() {
        delete[] busStops;
        delete[] passengers;
    }

    void addStop(string stop, int index) {
        if (index < max_stops)
            busStops[index] = stop;
    }

    void addPassenger(Person* p) {
        if (current_passengers < max_passengers) {
            passengers[current_passengers++] = p;
            cout << p->getID() << " registered on bus " << id << "\n";
        } else {
            cout << "Bus full! Cannot register " << p->getID() << "\n";
        }
    }

    bool operator==(const Bus& other) const {
        if (max_stops != other.max_stops) return false;
        for (int i = 0; i < max_stops; i++) {
            if (busStops[i] != other.busStops[i]) return false;
        }
        return true;
    }

    void viewDetails() {
        cout << "Bus: " << name << " (ID: " << id << ")\nStops: ";
        for (int i = 0; i < max_stops; i++) cout << busStops[i] << " ";
        cout << "\n";
    }
};

int Bus::counter = 0;


int main() {
    cout << "\nStudent ID: K240973" << endl;
    cout << "Name: Talha Mirza\n" << endl;

    Bus bus1("Route A", 3, 5);
    bus1.addStop("A", 0);
    bus1.addStop("B", 1);
    bus1.addStop("C", 2);
    
    Student s1("Talha", "K240973", true, "A", 100);
    Teacher t1("Prof. Ahmed", "T120", true, "B");
    StaffMember st1("Mr. Ali", "S340", true, "C");
    
    bus1.addPassenger(&s1);
    bus1.addPassenger(&t1);
    bus1.addPassenger(&st1);
    
    bus1.viewDetails();
    s1.viewDetails();
    t1.viewDetails();
    st1.viewDetails();
    
    return 0;
}