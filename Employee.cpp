#include "Employee.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>

Employee::Employee() {}

Employee::Employee(const std::string& username, const std::string& password, const std::string& name, const std::string& deptName, const std::string& status)
	: User(name, username, password), Dept(deptName),status(status) {}
void Employee::updateStatus(const std::string& employeeId, const std::string& newStatus) {
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
