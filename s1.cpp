#include <iostream>
#include <fstream>
#include <string>
#include "Teacher.h"
#include "Admin.h"
#include"Complaint.h"
#include"Manager.h"
#include"Employee.h"


#include <sstream>
#include <iomanip>
#include <unordered_map>
using namespace std;
void display(string managerId)
{
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
bool isvalidemployee(const string& username, const string& password, Employee& validemployee) {
    ifstream file("Credentials_employee.txt");
    Employee currentemployee;

    while (file >> currentemployee.username >> currentemployee.password >> currentemployee.name>>currentemployee.dept_name>>currentemployee.status) {
        if (currentemployee.username == username && currentemployee.password == password) {
            file.close();
            validemployee = currentemployee; // Set the validemployee information
            return true; // Username and password match
        }
    }

    file.close();
    return false; // Username and password do not match
}
// Function to check if a given username and password match the stored credentials
bool isValidTeacher(const string& username, const string& password, Teacher& validTeacher) {
    ifstream file("teacher.txt");
    Teacher currentTeacher;

    while (file >> currentTeacher.username >> currentTeacher.password >> currentTeacher.name) {
        if (currentTeacher.username == username && currentTeacher.password == password) {
            file.close();
            validTeacher = currentTeacher; // Set the validTeacher information
            return true; // Username and password match
        }
    }

    file.close();
    return false; // Username and password do not match
}
bool isValidmanager(const string& username, const string& password, Manager& validAdmin)
{
    ifstream file("credentials_manager.txt");
    Manager currentAdmin;

    while (file >> currentAdmin.username >> currentAdmin.password >> currentAdmin.name>>currentAdmin.dept_name) 
    {
        if (currentAdmin.username == username && currentAdmin.password == password) 
        {
            file.close();
            validAdmin = currentAdmin; 
            return true; // Username and password match
        }
    }

    file.close();
    return false; // Username and password do not match
}
bool isValidadmin(const string& username, const string& password, Admin& validAdmin)
{
    ifstream file("credentials.txt");
    Admin currentAdmin;

    while (file >> currentAdmin.username >> currentAdmin.password >> currentAdmin.name )
    {
        if (currentAdmin.username == username && currentAdmin.password == password)
        {
            file.close();
            validAdmin = currentAdmin;
            return true; // Username and password match
        }

    }

    file.close();
    return false; // Username and password do not match
}
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBox(const std::string& text) {
    std::string horizontalLine(text.length() + 4, '-');

    std::cout << "+ " << horizontalLine << " +\n";
    std::cout << "| " << text << " |\n";
    std::cout << "+ " << horizontalLine << " +\n";
}

char displayMenuAndGetOption() {
    char option;

    printBox("Welcome! Select your Role:");
    std::cout << "a) Teacher\n";
    std::cout << "b) Manager\n";
    std::cout << "c) Admin\n";
    std::cout << "d) Employee\n";
    std::cout << "q) to quit\n";
    printBox("Enter the corresponding letter (a, b, c, or d)");

    std::cin >> option;

    // Clear the input buffer in case the user entered invalid input
    clearInputBuffer();

    return option;
}
void waitenter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int main() 
{    
    string n = "n";
    char userOption;

    while (true)
    {
        //system("cls");
        userOption = displayMenuAndGetOption();

        if (userOption == 'a') {
            Teacher validTeacher;

            system("cls");
            std::cout << "\tTeacher.\n";
            printBox("Login");
            std::cout << "Enter your username: ";
            std::cin >> validTeacher.username;
            clearInputBuffer(); // Clear input buffer

            std::cout << "Enter your password: ";
            std::cin >> validTeacher.password;
            clearInputBuffer(); // Clear input buffer
            if (isValidTeacher(validTeacher.username, validTeacher.password, validTeacher))
            {
                cout << "Login successful. Welcome, " << validTeacher.name << "  (" << validTeacher.username << ")!\n";
                waitenter();
                system("cls");
            }
            else
            {
                system("cls");
                cout << "Invalid username or password. Login failed.\n";
                continue;
            }
            char op;
            while (true)
            {
                //system("cls");
                std::cout << "\n\tMENU\n";
                std::cout << "a) View Notification Bar\n";
                std::cout << "b) File a New Complaint\n";
                std::cout << "c) Close a Complaint\n";
                std::cout << "d) View Complaints you filed\n";
                std::cout << "x) Logout\n";
                std::cout << "Enter your choice: ";
                cin >> op;
                clearInputBuffer();
                if (op == 'a') {
                    system("cls");
                    validTeacher.displayComplaintsForTeacher(validTeacher.username);
                    waitenter();
                    system("cls");
                }
                else if (op == 'b') {
                    Complaint complaint1("", validTeacher.username);
                    complaint1.assigningManager();
                    complaint1.fileComplaintForTeacher(validTeacher, validTeacher.name);
                }
                else if (op == 'c') {
                    Complaint complaint1("", validTeacher.username);
                    int complaintId;
                    cout << "Enter the complaint# you are satisfied with: ";
                    cin >> complaintId;
                    complaint1.updateStatusInFile("notification.txt", complaintId, "Closed");
                    waitenter();
                    system("cls");
                }
                else if (op == 'd') {
                    system("cls");
                    Complaint c;
                    c.displayComplaintsForTeacher(validTeacher.username);
                    waitenter();
                    system("cls");
                }
                else if (op == 'x') {
                    system("cls");
                    std::cout << "Logging out...\n";
                    waitenter();
                    system("cls");
                    break;
                }
                else {
                    std::cout << "Invalid option. Please enter a valid option.\n";
                }
            }
        }
        else if (userOption == 'b') {
            
            system("cls");
            Manager validmanager;
            std::cout << "\tManager.\n";
            printBox("Login");
            std::cout << "Enter your username: ";
            std::cin >> validmanager.username;
            clearInputBuffer(); // Clear input buffer

            std::cout << "Enter your password: ";
            std::cin >> validmanager.password;
            clearInputBuffer(); // Clear input buffer
            if (isValidmanager(validmanager.username, validmanager.password, validmanager))
            {
                cout << "Login successful. Welcome, " << validmanager.name << " (" << validmanager.username << ", Dept: " << validmanager.dept_name << " )!\n";
                waitenter();
                system("cls");
            }
            else
            {
                cout << "Invalid username or password. Login failed.\n";
                waitenter();
                system("cls");
                continue;
            }
            char op;
            while (true)
            {
                //system("cls");
                std::cout << "\n\tMENU\n";
                std::cout << "a) View Complaint Bar\n";
                std::cout << "b) Assign employee to a complaint\n";
                std::cout << "c) Update a complaint status\n";
                std::cout << "x) Logout\n";
                std::cout << "Enter your choice: ";
                cin >> op;
                clearInputBuffer();
                if (op == 'a') {
                    system("cls");
                    Complaint c;
                    
                    c.displayComplaintsForManager(validmanager.username);
                    
                    waitenter();
                    system("cls");
                }
                else if (op == 'b') {
                    string temp = validmanager.assignEmployee();
                    if (temp == n)
                    {
                        cout << "\n->NONE OF THE EMPLOYEES WERE AVAILABLE to be assigned!\n";
                    }
                    else
                    {
                        validmanager.updateEmployeeStatus(temp, "Assigned");
                    }
                    
                    waitenter();
                    system("cls");
                }
                else if (op == 'c') {
                    Complaint c;
                    cout << "Enter the complaint ID you want to resolve: ";
                    int complaintId;
                    cin >> complaintId;
                    c.updateStatusInFile("complaints.txt", complaintId, "Resolved");
                    c.appendToNotificationFile("complaints.txt", complaintId, "Resolved");
                    
                    waitenter();
                    system("cls");
                }
                else if (op == 'x') {
                    system("cls");
                    std::cout << "Logging out...\n";
                    waitenter();
                    system("cls");
                    break;
                }
                else {
                    std::cout << "Invalid option. Please enter a valid option.\n";
                }
            }
        }
        else if (userOption == 'c') {
            system("cls");
            Admin validdirector;
            std::cout << "\tDirector.\n";
            printBox("Login");
            std::cout << "Enter your username: ";
            std::cin >> validdirector.username;
            clearInputBuffer(); // Clear input buffer

            std::cout << "Enter your password: ";
            std::cin >> validdirector.password;
            clearInputBuffer(); // Clear input buffer
            if (isValidadmin(validdirector.username, validdirector.password, validdirector))
            {
                cout << "Login successful. Welcome Director, " << validdirector.name << " (" << validdirector.username << " )!\n";
                waitenter();
                system("cls");
            }
            else
            {
                cout << "Invalid username or password. Login failed.\n";
                waitenter();
                system("cls");
                continue;
            }

            char op;
            while (true)
            {
                //system("cls");
                std::cout << "\n\tMENU\n";
                std::cout << "a) View Complaints Bar\n";
                std::cout << "b) Add a Manager\n";
                std::cout << "c) Remove a Manager\n";
                std::cout << "d) Add a Teacher\n";
                std::cout << "e) Remove a Teacher\n";
                std::cout << "f) Add a Employee\n";
                std::cout << "g) Remove a Employee\n";
                
                std::cout << "x) Logout\n";
                std::cout << "Enter your choice: ";
                cin >> op;
                clearInputBuffer();
                if (op == 'a') {
                    system("cls");
                    Complaint c;

                    c.displayFileContent("complaints.txt");

                    waitenter();
                    system("cls");
                }
                else if (op == 'b') {
                    validdirector.addManager();
                    waitenter();
                    system("cls");
                }
                else if (op == 'c') {
                    std::string managerId;

                    std::cout << "Enter the Manager ID to delete: ";
                    std::cin >> managerId;

                    validdirector.deleteManagerById(managerId);

                    std::cout << "Manager with ID " << managerId << " deleted." << std::endl;


                    waitenter();
                    system("cls");
                }
                else if (op == 'd') {
                    validdirector.addTeacher();
                    waitenter();
                    system("cls");
                }
                else if (op == 'e') {
                    std::string teacherId;

                    std::cout << "Enter the Teacher ID to delete: ";
                    std::cin >> teacherId;

                    validdirector.deleteTeacherById(teacherId);

                    std::cout << "Teacher with ID " << teacherId << " deleted." << std::endl;


                    waitenter();
                    system("cls");
                }
                else if (op == 'f') {
                    validdirector.addEmployee();

                    waitenter();
                    system("cls");
                }
                else if (op == 'g') {
                    std::string employeeId;

                    std::cout << "Enter the Employee ID to delete: ";
                    std::cin >> employeeId;

                    validdirector.deleteEmployeeById(employeeId);

                    std::cout << "Employee with ID " << employeeId << " deleted." << std::endl;


                    waitenter();
                    system("cls");
                }
                else if (op == 'x') {
                    system("cls");
                    std::cout << "Logging out...\n";
                    waitenter();
                    system("cls");
                    break;
                }
                else {
                    std::cout << "Invalid option. Please enter a valid option.\n";
                }
            }
            
        }
        else if (userOption == 'd') {
            system("cls");
            Employee validemployee;
            std::cout << "\tEmployee.\n";
            printBox("Login");
            std::cout << "Enter your username: ";
            std::cin >> validemployee.username;
            clearInputBuffer(); // Clear input buffer

            std::cout << "Enter your password: ";
            std::cin >> validemployee.password;
            clearInputBuffer(); // Clear input buffer
            if (isvalidemployee(validemployee.username, validemployee.password, validemployee))
            {
                cout << "Login successful. Welcome, " << validemployee.name << " (" << validemployee.username << ", Dept: " << validemployee.dept_name  << " )!\n";
                waitenter();
                system("cls");
            }
            else
            {
                cout << "Invalid username or password. Login failed.\n";
                waitenter();
                system("cls");
                continue;
            }
            char opt;
            while (true)
            {
                //system("cls");
                std::cout << "\n\tMENU\n";
                std::cout << "a) View Your status\n";
                std::cout << "b) Complete a complaint(job)t\n";
                std::cout << "x) Logout\n";
                std::cout << "Enter your choice: ";
                cin >> opt;
                clearInputBuffer();
                if (opt == 'a') {
                    system("cls");
                    cout << "\n\t->" << validemployee.name << " (" << validemployee.username << ", Dept: " << validemployee.dept_name << "\n\t\t-> Status: " << validemployee.status << "\n";
                    waitenter();
                    system("cls");
                }
                else if (opt == 'b') {
                    cout << "If the employee has completed his job press Y else N = ";
                    char opi;
                    cin >> opi;
                    if (opi == 'Y') {
                        validemployee.updateStatus(validemployee.username, "Free");
                        cout << "\nJob Completed stauts Updated in File!";
                    }
                    else
                    {
                        cout << "\nJob not completed yet !";
                    }
                    waitenter();
                    system("cls");
                }
                
                else if (opt == 'x') {
                    system("cls");
                    std::cout << "Logging out...\n";
                    waitenter();
                    system("cls");
                    break;
                }
                else {
                    std::cout << "Invalid option. Please enter a valid option.\n";
                }
            }
        }
        else if (userOption == 'q') {
            system("cls");
            cout << "\n\t\t******QUITING SYSTEM!******\n";
            break;
        }
        else {
            system("cls");
            std::cout << "Invalid option. Please enter a valid option (a, b, c, or d).\n";
            waitenter();
            system("cls");
        }
    }





    /*

   // Complaint c;
    //c.displayComplaintsForManager("3");

    int complaint_no;
    int userType;
    cout << "Select User Type:\n";
    cout << "1. Teacher\n";
    cout << "2. Manager\n";
    cout << "Enter choice (1 or 2): ";
    cin >> userType;

    if (userType == 1) {
        Teacher validTeacher;
        cout << "Enter username: ";
        cin >> validTeacher.username;

        cout << "Enter password: ";
        cin >> validTeacher.password;

        if (isValidTeacher(validTeacher.username, validTeacher.password, validTeacher))
        {
            cout << "Login successful. Welcome, " << validTeacher.name << " (" << validTeacher.username << ")!\n";
        }
        else
        {
            cout << "Invalid username or password. Login failed.\n";
        }
        validTeacher.displayComplaintsForTeacher(validTeacher.username);
        Complaint complaint1("", validTeacher.username);
        complaint1.assigningManager();
        complaint1.fileComplaintForTeacher(validTeacher,validTeacher.name);



    }
    else if (userType == 2)
    {
        Manager validAdmin;
        cout << "Enter username: ";
        cin >> validAdmin.username;

        cout << "Enter password: ";
        cin >> validAdmin.password;
        if (isValidAdmin(validAdmin.username, validAdmin.password, validAdmin))
        {
            cout << "Login successful. Welcome, " << validAdmin.name << " (" << validAdmin.username <<", Dept: "<<validAdmin.dept_name << " )!\n";
        }
        else
        {   
            cout << "Invalid username or password. Login failed.\n";
        }
        Complaint complaint2;
        complaint2.displayComplaintsForManager(validAdmin.username);
        cout << "Enter the complaint ID you want to resolve: ";
        int complaintId;
        cin >> complaintId;
        //string temp = validAdmin.assignEmployee();
        //validAdmin.updateEmployeeStatus(temp, "Assigned");
        complaint2.updateStatusInFile("complaints.txt", complaintId, "Resolved");
        complaint2.appendToNotificationFile("complaints.txt", complaintId, "Resolved");
        complaint2.displayComplaintsForManager(validAdmin.username);

    }
    */
    return 0;
}
