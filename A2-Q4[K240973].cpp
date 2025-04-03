#include <iostream>
#include <vector>
using namespace std;

class User;

const int hashValue = 5381;

int generateHash(string pwd) {
    int hash = hashValue;
    for (char c : pwd) {
        hash = (hash * 33) + c;
    }
    return hash;
}

class User {
protected:
    string name, id, email;
    int hashedPwd;
    vector<string> permissionList;

public:
    User() {}

    User(string n, string id, string e, int h) : name(n), id(id), email(e), hashedPwd(h) {
        permissionList.resize(2, ""); // Properly initializing the vector
    }

    bool authenticateUser(string pwd) {
        return (hashedPwd == generateHash(pwd));
    }

    virtual void display() {
        cout << "\nUsername: " << name << endl;
        cout << "User ID: " << id << endl;
        cout << "Email: " << email << endl;
        cout << "Permissions given: " << endl;

        bool hasPermissions = false;
        for (const string &perm : permissionList) {
            if (!perm.empty()) {
                cout << "- " << perm << endl;
                hasPermissions = true;
            }
        }

        if (!hasPermissions) {
            cout << "No Permissions Granted" << endl;
        }
    }

    bool accessLab() {
        for (const string &perm : permissionList) {
            if (perm == "Lab is accessible") {
                cout << "User " << id << " has access to the Lab" << endl;
                return true;
            }
        }
        cout << "User " << id << " does not have access to the Lab" << endl;
        return false;
    }

    vector<string>& getList() { return permissionList; }
    string getID() { return id; }
};

class Student : public User {
protected:
    int assignmentList[10] = { -1 };

public:
    Student() {}

    Student(string n, string id, string e, int h) : User(n, id, e, h) {
        permissionList[0] = "Submit Assignment";
    }

    void display() override {
        cout << "The user is a student" << endl;
        User::display();
    }

    void assignAssignment(int index) {
        if (index >= 0 && index < 10) {
            assignmentList[index] = 0;
            cout << "Assignment " << index << " assigned successfully." << endl;
        } else {
            cout << "Invalid assignment index." << endl;
        }
    }

    void submitAssignment(int index) {
        string pwd;
        cout << "Enter your password: ";
        getline(cin, pwd);

        if (authenticateUser(pwd)) {
            if (index >= 0 && index < 10) {
                if (assignmentList[index] == 0) {
                    assignmentList[index] = 1;
                    cout << "Assignment " << index << " submitted successfully." << endl;
                } else if (assignmentList[index] == 1) {
                    cout << "The assignment has already been submitted." << endl;
                } else {
                    cout << "No work assigned." << endl;
                }
            } else {
                cout << "Invalid assignment index!" << endl;
            }
        } else {
            cout << "Incorrect password!" << endl;
        }
    }
};

class TA : public Student {
private:
    vector<Student*> studentList; // max 10 students
    vector<string> projectList;   // can work on max 2 projects

public:
    TA(string n, string id, string e, int h) : Student(n, id, e, h) {}

    void display() override {
        cout << "The user is a TA!" << endl;
        User::display();

        cout << "List of projects: ";
        if (projectList.empty()) {
            cout << "None" << endl;
        } else {
            for (size_t i = 0; i < projectList.size(); i++) {
                cout << "\n" << i + 1 << ": " << projectList[i];
            }
            cout << endl;
        }

        cout << "List of assigned students: ";
        if (studentList.empty()) {
            cout << "None" << endl;
        } else {
            for (size_t i = 0; i < studentList.size(); i++) {
                cout << "\n" << i + 1 << ": " << studentList[i]->getID();
            }
            cout << endl;
        }
    }

    void newProject() {
        string pwd;
        cout << "Enter your password: ";
        getline(cin, pwd);

        if (authenticateUser(pwd)) {
            if (projectList.size() < 2) {
                string projectName;
                cout << "Enter project name: ";
                getline(cin, projectName);
                projectList.push_back(projectName);
                cout << "Project added successfully!" << endl;
            } else {
                cout << "TA is already working on two projects, cannot add more." << endl;
            }
        } else {
            cout << "Incorrect password!" << endl;
        }
    }

    void assignStudent(Student* s) {
        string password;
        cout << "Enter your password: ";
        cin >> password;

        if (authenticateUser(password)) {
            if (studentList.size() < 10) {
                studentList.push_back(s);
                cout << "Student " << s->getID() << " assigned to TA " << name << endl;
            } else {
                cout << "TA already has 10 students assigned, cannot assign more." << endl;
            }
        } else {
            cout << "Incorrect password!" << endl;
        }
    }
};

class Professor : public User {
public:
    Professor(string n, string id, string e, int h) : User(n, id, e, h) {}

    void display() override {
        cout << "The user is a Professor" << endl;
        User::display();
    }
};

int main() {
    cout << "\nStudent ID: K240973" << endl;
    cout << "Name: Talha Mirza\n" << endl;

    Student s1("Alice", "S123", "alice@example.com", generateHash("password123"));
    TA ta1("Bob", "TA456", "bob@example.com", generateHash("ta_pass"));
    Professor prof1("Dr. Smith", "P789", "smith@example.com", generateHash("prof123"));

    cout << "\nTesting Student Authentication:\n";
    s1.authenticateUser("password123") ? cout << "Success\n" : cout << "Failure\n";

    s1.assignAssignment(2);
    s1.submitAssignment(2);

    ta1.newProject();
    ta1.assignStudent(&s1);

    s1.display();
    ta1.display();
    prof1.display();

    return 0;
}
