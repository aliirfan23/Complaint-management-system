#pragma once

#include <string>
using namespace std;

class Dept {
public:
    string dept_name;

    Dept();
    Dept(const string& dept_name);

    const string& getName() const;    
};

