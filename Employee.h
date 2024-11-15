#pragma once

#include "User.h"
#include "Dept.h"
#include <string>

class Employee : public User, public Dept {

public: 
    string status;
    Employee();
    Employee(const std::string& username, const std::string& password, const std::string& name, const std::string& deptName, const std::string& status);
    void updateStatus(const std::string& employeeId, const std::string& newStatus);
    
};