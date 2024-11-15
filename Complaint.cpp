#include "Complaint.h"
#include"Teacher.h"
#include"Manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include<ctime>
#include<chrono>
#include <unordered_map>
using namespace std;
bool Complaint::isFileEmpty(const std::string& filename) 
{
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}
Complaint::Complaint() {}
Complaint::Complaint(const string& description, const string& teacher)
    : description(description), status("new"), teacher(teacher), manager(""), employees({}) 
{
    if (isFileEmpty("Complaints.txt")) {
        id=1;
    }
    else
    {
        id = (getLastAssignedId() + 1);
    }
    
}

int Complaint::getId() const {
    return id;
}

int Complaint::getLastAssignedId() {
    return readLastAssignedId();
}

int Complaint::readLastAssignedId() {
    ifstream file("complaints.txt");
    int lastId = 0;

    if (file.is_open()) {
        string line;

        // Check if the file is empty
        if (file.peek() == std::ifstream::traits_type::eof()) {
            lastId = 1; // If empty, assign complaint ID = 1
        }
        else {
            while (getline(file, line)) {
                size_t idPos = line.find("Complaint_# ");
                if (idPos != string::npos) {
                    int currentId;
                    if (sscanf_s(line.c_str() + idPos + 12, "%d", &currentId) == 1) {
                        lastId = max(lastId, currentId);
                    }
                }
            }
        }

        file.close();
    }

    return lastId;
}

void Complaint::updateLastAssignedId(int newId) {
    ofstream file("complaints.txt", ios::app);

    if (file.is_open()) {
        file << "Complaint_# " << newId << '\n';
        file.close();
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}

string Complaint::getDescription() const {
    return description;
}

string Complaint::getStatus() const {
    return status;
}

string Complaint::getTeacher() const {
    return teacher;
}

string Complaint::getManager() const {
    return manager;
}

vector<string> Complaint::getEmployees() const {
    return employees;
}

void Complaint::updateStatus(const string& newStatus) {
    status = newStatus;
}

void Complaint::setManager(const string& newManager) {
    manager = newManager;
}

void Complaint::addEmployee(const string& employee) {
    employees.push_back(employee);
}

void Complaint::saveToFile(const string& filename) const {
    ofstream file(filename);

    if (file.is_open()) {
        file << id << '\n';
        file << description << '\n';
        file << status << '\n';
        file << teacher << '\n';
        file << manager << '\n';

        for (const auto& employee : employees) {
            file << employee << '\n';
        }

        file.close();
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}

void Complaint::loadFromFile() {
    ifstream file("complaints.txt");

    if (file.is_open()) {
        file >> id;
        file.ignore(); // Ignore the newline character
        getline(file, description);
        getline(file, status);
        getline(file, teacher);
        getline(file, manager);

        file.close();
    }
    else {
        cerr << "Error: Unable to open file for reading.\n";
    }
}
std::string getCurrentDate() {
    // Get the current time point
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm structure in local time using localtime_s
    std::tm localTime;
    if (localtime_s(&localTime, &currentTime) != 0) {
        // Handle the error
        std::cerr << "Error in localtime_s" << std::endl;
        return "";
    }

    // Format the date as a string (e.g., "YYYY-MM-DD")
    char buffer[11];
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime) == 0) {
        // Handle the error
        std::cerr << "Error in strftime" << std::endl;
        return "";
    }

    return buffer;
}

void Complaint::fileComplaintForTeacher(const Teacher& teacher1, const string& str) {
    // Prompt the user for a complaint
    cout << "Enter your complaint:\n";
    getline(cin >> ws, description); // Read the entire line including spaces
    
    // Assign an available manager (needs to be done logic needed to be ma)
    // For now, let's assume manager id 1 is available
    //manager = "1";

    // Update the complaint information
    

    // Save the complaint to the specified file
    
    string d = getCurrentDate();
    ofstream file("complaints.txt", ios::app); // Open the file in append mode

    if (file.is_open()) {
        file <<"Complaint_# " << id << "   ";
        file << "Description:" << description << "   ";
        file <<"Status:" << status << "   ";
        file <<"TeacherID:" << teacher << "   ";
        file <<"TeacherNAME:" << str << "   ";
        file <<"Manager:" << manager << "   ";
        file << "Date:" << d;

        /*for (const auto& employee : employees) {
            file << employee << ' ';
        }*/

        file << '\n';
        file.close();
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}
void Complaint::updateStatusInFile(const string& filename, int complaintNumber, const string& newStatus) 
{
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Unable to open files.\n";
        return;
    }

    string line;

    while (getline(inFile, line)) {
        size_t numberPos = line.find("Complaint_# ");
        if (numberPos != string::npos) {
            int currentNumber;
            if (sscanf_s(line.c_str() + numberPos + 12, "%d", &currentNumber) == 1) {
                if (currentNumber == complaintNumber) {
                    // Update the status in the line
                    size_t statusPos = line.find("Status:");
                    if (statusPos != string::npos) {
                        line.replace(statusPos + 7, line.find("   ", statusPos + 7) - (statusPos + 7), newStatus);
                    }
                }
            }
        }

        // Write the line to the new file
        outFile << line << '\n';
    }

    inFile.close();
    outFile.close();

    // Rename the temporary file to the original file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}
void Complaint::assigningManager() {
    std::string department;

    // Prompt user to enter the name of the department
    std::cout << "Enter the name of the department to forward the complaint: ";
    std::cin >> department;

    // Open credentials_manager.txt to find the manager associated with the department
    std::ifstream managerFile("credentials_manager.txt");
    if (!managerFile) {
        std::cerr << "Error: Could not open credentials_manager.txt\n";
        return;
    }

    std::string line;
    bool found = false;
    char managerId[20];
    while (getline(managerFile, line)) {
        std::istringstream iss(line);
        
        char password[20];
        char managerName[50];
        char departmentName[50];

        // Use sscanf_s to parse the line
        if (sscanf_s(line.c_str(), "%s %s %s %s", managerId, sizeof(managerId),
            password, sizeof(password),
            managerName, sizeof(managerName),
            departmentName, sizeof(departmentName)) >= 4) {
            // Check if the entered department matches the current line
            if (std::string(departmentName) == department) {
                found = true;
                manager = managerId; // Assign manager ID
                break;
            }
        }
    }

    // Close the file
    managerFile.close();

    if (!found) {
        std::cerr << "Error: Department not found\n";
    }
    else {
        std::cout << "Manager assigned successfully. Manager ID: " << managerId << "\n";
        // Update the managerId in the complaint object
        manager = managerId;
    }
}
// Function to remove extra spaces from a string
string removeExtraSpaces(const std::string& input) {
    std::istringstream iss(input);
    std::ostringstream oss;

    // Copy words with a single space in between
    std::string word;
    while (iss >> word) {
        oss << word << ' ';
    }

    // Get the result as a string
    return oss.str();
}

void Complaint::displayComplaintsForManager(const std::string& managerId) {
    std::ifstream complaintFile("complaints.txt");
    if (!complaintFile) {
        std::cerr << "Error: Could not open complaint.txt\n";
        return;
    }

    std::string line;

    // Display complaints matching the managerId
    while (std::getline(complaintFile, line)) {
        // Find the position of "Manager:" in the line
        size_t managerPos = line.find("Manager:");
        //char[3] assignedManagerId;
        // If "Manager:" is found, extract the manager ID
        if (managerPos != std::string::npos) {
            string assignedManagerId = line.substr(managerPos + 8); // Assuming "Manager:" is 8 characters
            //cout << assignedManagerId ;
            // Check if the assignedManagerId matches the provided managerId
            string result = assignedManagerId.substr(0, 3);
            if (result == managerId) {
                cout << line << "\n";
            }
        }
    }

    // Close the file
    complaintFile.close();
}

void Complaint::appendToNotificationFile(const string& filename, int complaintNumber, const string& newStatus)
{
    ifstream inFile("Complaints.txt");
    

    if (!inFile.is_open() ) {
        cerr << "Error: Unable to open files.\n";
        return;
    }

    string line;

    while (getline(inFile, line)) {
        size_t numberPos = line.find("Complaint_# ");
        if (numberPos != string::npos) {
            int currentNumber;
            if (sscanf_s(line.c_str() + numberPos + 12, "%d", &currentNumber) == 1) {
                if (currentNumber == complaintNumber) 
                {
                    // Update the status in the line
                    std::ofstream notificationFile("notification.txt", std::ios::app);
                    if (!notificationFile) {
                        std::cerr << "Error: Could not open notification.txt for append\n";
                        return;
                    }
                    //cout << line;
                    notificationFile << line ;

                    // Close the file
                    notificationFile.close();
                }
            }
        }

        
    }

    inFile.close();
    

    


    std::ofstream notificationFile("notification.txt", std::ios::app);
    if (!notificationFile) {
        std::cerr << "Error: Could not open notification.txt for append\n";
        return;
    }
    //cout << line;
    notificationFile << line << "\n";

    // Close the file
    notificationFile.close();
}
void Complaint::displayFileContent(const string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

void Complaint::displayComplaintsForTeacher(const std::string& managerId) {
    std::ifstream complaintFile("complaints.txt");
    if (!complaintFile) {
        std::cerr << "Error: Could not open complaint.txt\n";
        return;
    }

    std::string line;

    // Display complaints matching the managerId
    while (std::getline(complaintFile, line)) {
        // Find the position of "Manager:" in the line
        size_t managerPos = line.find("TeacherID:");
        //char[3] assignedManagerId;
        // If "Manager:" is found, extract the manager ID
        if (managerPos != std::string::npos) {
            string assignedManagerId = line.substr(managerPos + 10); // Assuming "Manager:" is 8 characters
            //cout << assignedManagerId ;
            // Check if the assignedManagerId matches the provided managerId
            string result = assignedManagerId.substr(0, 3);
            if (result == managerId) {
                cout << line << "\n";
            }
        }
    }

    // Close the file
    complaintFile.close();
}