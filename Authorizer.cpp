#include "Authorizer.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;


int Authorizer::strLength(const char* text) {
    if (!text) return 0;
    int len = 0;
    while (text[len] != '\0') ++len;      //Pre-Increment, dosen't inlcude Last NullPtr "\0"
    return len;
}

bool Authorizer::isValid(int id) {
    return id > 0;
}

bool Authorizer::isValidPassword(const char* password) {     //checks Null Pointers as well
    return password && strLength(password) >= 6;
}

bool Authorizer::isValidContact(const char* contact) {
    return contact && strLength(contact) >= 11;
}

bool Authorizer::isValidMenuChoice(int choice, int min, int max) {
    return choice >= min && choice <= max;
}

int Authorizer::toInt(const char* text) {
    if (!text) return 0;
    return std::atoi(text);
}




