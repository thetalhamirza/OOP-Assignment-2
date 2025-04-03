#include <iostream>
using namespace std;

class Vehicle {
    protected:

    int vehicleID;
    float speed, capacity, energyEfficiency;
    static int totalDeliveries;
    
    public:
    Vehicle(float s, float c, float e) : speed(s), capacity(c), energyEfficiency(e), vehicleID(++totalDeliveries) {}
    
    virtual void optimalDeliveryRoute() = 0;
    virtual void estimateDeliveryTime() = 0;
    virtual void command(string cmd, int packageID) = 0;
    virtual void command(string cmd, int packageID, string urgency) = 0;

    friend bool operator==(const Vehicle& A, const Vehicle& B);

    friend void AIConflictResolution(Vehicle& A, Vehicle& B);

    int getID() {return vehicleID;}
};

bool operator==(const Vehicle& A, const Vehicle& B) {
    return (A.speed == B.speed && A.capacity == B.capacity && A.energyEfficiency == B.energyEfficiency);
}

void AIConflictResolution(Vehicle& A, Vehicle& B) {
    if (A == B) {
        cout << "Order assigned twice to the same vehicle!" << endl;
    } else {
        int a = 0, b = 0;
        if (A.speed > B.speed)  {
            cout << "In terms of speed, Vehicle " << A.vehicleID << "is better!" << endl;
            a++;
        }   else   {
            cout << "In terms of speed, Vehicle " << B.vehicleID << "is better!" << endl;
            b++;
        }
        if (A.capacity > B.capacity)    {
            cout << "In terms of capacity, Vehicle " << A.vehicleID << "is better!" << endl;
            a++;
        }    else   {
            cout << "In terms of capacity, Vehicle " << B.vehicleID << "is better!" << endl;
            b++;
        }
        if (A.energyEfficiency > B.energyEfficiency)  {
            cout << "In terms of Energy Efficiency, Vehicle " << A.vehicleID << "is better!" << endl;
            a++;
        }  else  {
            cout << "In terms of Energy Efficiency, Vehicle " << B.vehicleID << "is better!" << endl;
            b++;
        }

        if (a > b)  {
            cout << "According to AI Conflict Resolution System, Vehicle " << A.vehicleID << " is more suitable for executing the task!" << endl;
        }  else  {
             cout << "According to AI Conflict Resolution System, Vehicle " << B.vehicleID << " is more suitable for executing the task!" << endl;
        }
    }
}

int Vehicle::totalDeliveries = 0;

class RamzanDrone : public Vehicle {
    public:
    RamzanDrone(float s, float c, float e) : Vehicle(s,c,e) {}

    void optimalDeliveryRoute() override {
        cout << "Calculating optimal aerial route..." << endl;
    }
    void estimateDeliveryTime() override {
        cout << "Estimating delivery time when using aerial route..." << endl;
    }
    void command(string cmd, int packageID) override  {
        cout <<"Vehicle " << vehicleID << " executing command '" << cmd << "' for package " << packageID << "using Drone Mode!" << endl;
    }

    void command(string cmd, int packageID, string urgency) override   {
        cout << "Vehicle " << vehicleID << " executing command '" << cmd << "' for package " << packageID << " with Urgency: " << urgency << " using Drone Mode!" << endl;
        cout << "High-Speed Mode Activated!" << endl;
    }
};

class RamzanTimeShip : public Vehicle {
    public:
    RamzanTimeShip(float s, float c, float e) : Vehicle(s, c, e) {}
    void optimalDeliveryRoute() override  {
        cout << "Calculating optimal Time-Travel route..." << endl;
    }

    void estimateDeliveryTime() override    {
        cout << "Estimating delivery time when using Time-Travel..." << endl;
    }

    void command(string cmd, int packageID) override    {
        cout << "Vehicle " << vehicleID << " executing command '" << cmd << "' for package " << packageID << "using Time-Travel Mode!" << endl;
    }

    void command(string cmd, int packageID, string urgency) override    {
        cout << "Requiring Validation ! for Vehicle " << vehicleID << " to execute command '" << cmd << "' for package " << packageID << " with Urgency: " << urgency << " using Time-Travel Mode!" << endl;
    }
};

class RamzanHyperPod : public Vehicle {
    public:
    RamzanHyperPod(float s, float c, float e) : Vehicle(s, c, e) {}
    
    void optimalDeliveryRoute() override    {
        cout << "Calculating optimal Underground Transport Route..." << endl;
    }

    void estimateDeliveryTime() override    {
        cout << "Estimating delivery time when using Underground Transport route..." << endl;
    }

    void command(string cmd, int packageID) override    {
        cout << "Vehicle "<< vehicleID << " executing command '" << cmd << "' for package " << packageID << " using Underground Transport Mode!" << endl;
    }

    void command(string cmd, int packageID, string urgency) override    {
        cout << "Vehicle " << vehicleID << " executing commmand '" << cmd << "' for package " << packageID << " with Urgency: " << urgency << " using Hyper Pod Mode!" << endl;
        cout << "Navigating through an underground tunnel network!" << endl;
    }
};

int main() {
    cout << "\nStudent ID: K240973" << endl;
    cout << "Name: Talha Mirza\n" << endl;

    RamzanDrone drone(95, 25, 75);
    RamzanTimeShip timeShip(75, 80, 40);
    RamzanHyperPod hyperPod(140, 150, 75);

    Vehicle* arr[3];
    arr[0] = &drone;
    arr[1] = &timeShip;
    arr[2] = &hyperPod;

    for (int i = 0; i < 3; i++) {
        cout << "Vehicle ID: " << arr[i]->getID() << endl;
        arr[i]->estimateDeliveryTime();
        arr[i]->optimalDeliveryRoute();
        arr[i]->command("Deliver", i+200);
    }
}