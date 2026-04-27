#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nMarks: " << marks << "\n\n";
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student Added Successfully!\n";
}

// Display All Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No records found!\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {
    int id, found = 0;
    Student s;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            s.display();
            found = 1;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found!\n";
}

// Update Student
void updateStudent() {
    int id;
    Student s;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));
            cout << "Record Updated!\n";
            file.close();
            return;
        }
    }

    file.close();
    cout << "Student not found!\n";
}

// Delete Student
void deleteStudent() {
    int id;
    Student s;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    int found = 0;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            outFile.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record Deleted!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
