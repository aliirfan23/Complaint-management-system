
#include "Dept.h"
Dept::Dept() {}
Dept::Dept(const std::string& dept_name) : dept_name(dept_name) {}

const std::string& Dept::getName() const {
    return dept_name;
}
