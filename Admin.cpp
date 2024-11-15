#include "admin.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include<ctime>
#include<chrono>
#include <unordered_map>


Admin::Admin() {}
void Admin::deleteTeacherById(const std::string& teacherId) {
    std::ifstream inputFile("teacher.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening teachers file." << std::endl;
        return;
    }

    std::ofstream tempFile("temp_teachers.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Extract the first 3 characters (teacher ID) from the line
        std::string lineTeacherId = line.substr(0, 3);

        // Check if the teacher ID matches the input ID
        if (lineTeacherId != teacherId) {
            // Write the line to the temporary file
            tempFile << line << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file
    if (remove("teacher.txt") != 0) {
        std::cerr << "Error deleting original file." << std::endl;
        return;
    }

    // Rename the temporary file to the original file name
    if (rename("temp_teachers.txt", "teacher.txt") != 0) {
        std::cerr << "Error renaming temporary file." << std::endl;
    }
}
void Admin::addTeacher() {
    std::string teacherId, password, name;
    cout << "\n\t***ADDING A NEW TEACHER***\n";                                  
    // Get teacher information from the user
    std::cout << "Enter Teacher ID: ";
    std::cin >> teacherId;

    std::cout << "Enter Password: ";
    std::cin >> password;

    std::cout << "Enter Teacher Name: ";
    std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, name);

    // Open the file in append mode
    std::ofstream file("teacher.txt", std::ios_base::app);

    if (!file.is_open()) {
        std::cerr << "Error opening teachers file." << std::endl;
        return;
    }

    // Write the new teacher information to the file
    file << teacherId << " " << password << " " << name << std::endl;

    std::cout << "Teacher added successfully." << std::endl;

    file.close();
}
void Admin::addEmployee() {
    std::string employeeId, password, name,dept,status;

    // Get employee information from the user
    std::cout << "Enter Employee ID: ";
    std::cin >> employeeId;

    std::cout << "Enter Password: ";
    std::cin >> password;

    std::cout << "Enter Employee Name: ";
    std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, name); 
    std::cout << "Enter Department Name: ";
    //std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, dept); 
    std::cout << "Enter Employee Status: ";
    //std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, status);


    // Open the file in append mode
    std::ofstream file("credentials_employee.txt", std::ios_base::app);

    if (!file.is_open()) {
        std::cerr << "Error opening employee credentials file." << std::endl;
        return;
    }

    // Write the new employee information to the file
    file << employeeId << " " << password << " " << name << " " << dept << " " << status << std::endl;

    std::cout << "Employee added successfully." << std::endl;
   
    file.close();
}
void Admin::addManager() {
    std::string managerId, password, name, department;

    // Get manager information from the user
    std::cout << "Enter Manager ID: ";
    std::cin >> managerId;

    std::cout << "Enter Password: ";
    std::cin >> password;

    std::cout << "Enter Manager Name: ";
    std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, name);

    std::cout << "Enter Manager Department: ";
    std::cin.ignore(); // Ignore the newline character left in the buffer
    std::getline(std::cin, department);

    // Open the file in append mode
    std::ofstream file("credentials_manager.txt", std::ios_base::app);

    if (!file.is_open()) {
        std::cerr << "Error opening manager credentials file." << std::endl;
        return;
    }

    // Write the new manager information to the file
    file << managerId << " " << password << " " << name << " " << department << std::endl;

    std::cout << "Manager added successfully." << std::endl;

    file.close();
}
void Admin::deleteManagerById(const std::string& managerId) {
    std::ifstream inputFile("credentials_manager.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening manager credentials file." << std::endl;
        return;
    }

    std::ofstream tempFile("temp_credentials_manager.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Extract the first 3 characters (manager ID) from the line
        std::string lineManagerId = line.substr(0, 3);

        // Check if the manager ID matches the input ID
        if (lineManagerId != managerId) {
            // Write the line to the temporary file
            tempFile << line << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file
    if (remove("credentials_manager.txt") != 0) {
        std::cerr << "Error deleting original file." << std::endl;
        return;
    }

    // Rename the temporary file to the original file name
    if (rename("temp_credentials_manager.txt", "credentials_manager.txt") != 0) {
        std::cerr << "Error renaming temporary file." << std::endl;
    }
}
void Admin::deleteEmployeeById(const std::string& employeeId) {
    std::ifstream inputFile("Credentials_employee.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening employee credentials file." << std::endl;
        return;
    }

    std::ofstream tempFile("temp_credentials_employee.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Extract the first 3 characters (employee ID) from the line
        std::string lineEmployeeId = line.substr(0, 3);

        // Check if the employee ID matches the input ID
        if (lineEmployeeId != employeeId) {
            // Write the line to the temporary file
            tempFile << line << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file
    if (remove("Credentials_employee.txt") != 0) {
        std::cerr << "Error deleting original file." << std::endl;
        return;
    }

    // Rename the temporary file to the original file name
    if (rename("temp_credentials_employee.txt", "Credentials_employee.txt") != 0) {
        std::cerr << "Error renaming temporary file." << std::endl;
    }
}

