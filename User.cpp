#include "User.h"
using namespace std;

User::User(const string& name, const string& username, const string& password)
    : name(name), username(username), password(password) {}
User::User()
{}
const string& User::getName() const {
    return name;
}

const string& User::getUsername() const {
    return username;
}

const string& User::getPassword() const {
    return password;
}