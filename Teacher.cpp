#include "Teacher.h"
#include<iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

Teacher::Teacher() {}
Teacher::Teacher(const string& username, const string& password, const string& name)
    : User(name, username, password){}

void Teacher::displayComplaintsForTeacher(const std::string& teachererId) const {
    std::ifstream notificationFile("notification.txt");
    if (!notificationFile) {
        std::cerr << "Error: Could not open complaint.txt\n";
        return;
    }

    std::string line;
    cout << "\n\n\n\t\t\t***NOTIFICATION CENTRE***\n\n";
    cout << "->NOTE: Complaints avaiting feedback!\n";
    // Display complaints matching the managerId
    while (std::getline(notificationFile, line)) {
        // Find the position of "Teacher:" in the line
        size_t managerPos = line.find("TeacherID:");
        
        // If "Manager:" is found, extract the manager ID
        if (managerPos != std::string::npos) {
            string assignedTeacherId = line.substr(managerPos + 10); // Assuming "Manager:" is 8 characters
            //cout << assignedManagerId ;
            // Check if the assignedManagerId matches the provided managerId
            if (stoi(assignedTeacherId) == stoi(teachererId)) {
                cout << line << "\n";
            }
        }
    }
    cout << "\n\t\t\t\t******\n";
    // Close the file
    notificationFile.close();
}