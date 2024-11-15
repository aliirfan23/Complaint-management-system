#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
using namespace std;


Manager::Manager() {}
Manager::Manager(const string& username, const string& password, const string& name, const string& dept_name)
    : User(name, username, password), Dept(dept_name) {}

/*const std::string& Manager::getUserRole() const {
    return "Manager";
}*/
string Manager::assignEmployee() {
    string n = "n";
    std::ifstream employeeFile("Credentials_employee.txt");
    if (!employeeFile) {
        std::cerr << "Error: Could not open Credentials_employee.txt\n";
        return n;
    }

    std::string line;
std:string username1;
    std::string password, employeeName, employeeDept, employeeStatus;

    // Find an available employee with the same department
    while (getline(employeeFile, line)) {
        std::istringstream iss(line);
        iss >> username1 >> password >> employeeName >> employeeDept >> employeeStatus;
        
        // Check if the employee is in the same department and has status "free"
        if (employeeDept == dept_name && employeeStatus == "Free") {
            // Assign the employee
            std::cout << "Assigning Employee: " << employeeName << " to Manager of department : " << dept_name << "\n";

            return username1;
            // Break the loop after assigning one employee
            break;
        }
    }

    // Close the file
    employeeFile.close();
    return n;
}
void Manager::updateEmployeeStatus(const std::string& employeeId, const std::string& newStatus) {
    std::ifstream employeeFile("Credentials_employee.txt");
    if (!employeeFile) {
        std::cerr << "Error: Could not open Credentials_employee.txt\n";
        return;
    }

    std::string line;
    std::string username, password, employeeName, employeeDept, employeeStatus;

    // Temporary storage for all employee data
    std::vector<std::string> allEmployeeData;

    // Find the employee with the given ID and update the status
    while (getline(employeeFile, line)) {
        std::istringstream iss(line);
        iss >> username >> password >> employeeName >> employeeDept >> employeeStatus;

        // Check if the employee has the given ID
        if (username == employeeId) {
            // Update the status
            std::cout << "Updating status for Employee: " << employeeName << "\n";
            allEmployeeData.push_back(username + " " + password + " " + employeeName + " " + employeeDept + " " + newStatus);
        }
        else {
            // Store the data for other employees
            allEmployeeData.push_back(line);
        }
    }

    // Close the file
    employeeFile.close();

    // Rewrite the updated data to the file
    std::ofstream updatedEmployeeFile("Credentials_employee.txt");
    if (!updatedEmployeeFile) {
        std::cerr << "Error: Could not open Credentials_employee.txt for update\n";
        return;
    }

    for (const std::string& employeeData : allEmployeeData) {
        updatedEmployeeFile << employeeData << "\n";
    }

    // Close the updated file
    updatedEmployeeFile.close();
}