#pragma once
#include "User.h"
#include <string>

using namespace std;

class Admin : public User {
public:
	Admin();
	void deleteTeacherById(const std::string& teacherId);
	void addTeacher();
	void addEmployee();
	void addManager();
	void deleteManagerById(const std::string& managerId);
	void deleteEmployeeById(const std::string& employeeId);
};
