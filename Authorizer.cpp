#include "Authorizer.h"
#include <cstdio>
#include <cstdlib>
#include <cctype>    

using namespace std;


int Authorizer::strLength(const char* text) {
    if (!text) return 0;                  // !0 = 1, True---> return 0;
    int len = 0;
    while (text[len] != '\0') ++len;      //Pre-Increment, dosen't inlcude Last NullPtr "\0"
    return len;
}

bool Authorizer::isValid(int id) {
    return id > 0;
}

bool Authorizer::strEqual(const char* a, const char* b) {
    if (!a || !b) return false;
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}

bool Authorizer::strEqualIC(const char* a, const char* b)
{
    if (!a || !b) return false;
    size_t i = 0;
    while (a[i] && b[i]) {
        if (std::tolower(static_cast<unsigned char>(a[i])) !=
            std::tolower(static_cast<unsigned char>(b[i])))
            return false;
        ++i;
    }
    return a[i] == b[i];
}

int Authorizer::toInt(const char* text) {
    if (!text) return 0;
    return std::atoi(text);
}




