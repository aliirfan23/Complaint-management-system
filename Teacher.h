#pragma once

#include "User.h"

#include <string>
using namespace std;

class Teacher : public User {
public:
    Teacher();
    Teacher(const string& username, const string& password, const string& name);
    void displayComplaintsForTeacher(const std::string& teachererId) const;
};

