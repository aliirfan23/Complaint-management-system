#pragma once

#include "User.h"
#include "Dept.h"
#include <string>
using namespace std;

class Manager : public User, public Dept {
public:
    Manager();
    Manager(const string& username, const string& password, const string& name, const string& dept_name);
    string assignEmployee();
    void updateEmployeeStatus(const std::string& employeeId, const std::string& newStatus);

    // Access functions for User and Dept
    //const std::string& getUserRole() const;
};



