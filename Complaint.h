#pragma once
#include <string>
#include <vector>

using namespace std; // Including the entire namespace in the header file

class Teacher;

class Complaint {
private:
    int id;
    string description;
    string status;
    string teacher;
    string manager;
   
    vector<string> employees;

    
public:

    Complaint();
    Complaint(const std::string& description, const std::string& teacher);
    bool isFileEmpty(const std::string& filename);
    int getId() const; // Getter for the complaint ID
    static int readLastAssignedId();
    static int getLastAssignedId();  // Getter for the last assigned ID
    static void updateLastAssignedId(int newId);  // Function to update the last assigned ID in file


    string getDescription() const;
    string getStatus() const;
    string getTeacher() const;
    string getManager() const;
    vector<string> getEmployees() const;

    void updateStatus(const string& newStatus);
    void setManager(const string& newManager);
    void addEmployee(const string& employee);

    void saveToFile(const string& filename) const;
    void loadFromFile();

    // New method to file a complaint for a teacher
    void fileComplaintForTeacher(const Teacher& teacher,const string& str);
    void updateStatusInFile(const string& filename, int complaintId, const string& newStatus);
    void assigningManager();
    void displayComplaintsForManager(const std::string& managerId);
    void appendToNotificationFile(const string& filename, int complaintId, const string& newStatus);
    void displayFileContent(const string& filename);
    void displayComplaintsForTeacher(const std::string& managerId);
};


