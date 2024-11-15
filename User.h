#pragma once
#include <string>

using namespace std;

class User {
public:
    string name;
    string username;
    string password;
public:
    User();
    User(const string& name, const string& username, const string& password);

    const string& getName() const;
    const string& getUsername() const;
    const string& getPassword() const;
};



