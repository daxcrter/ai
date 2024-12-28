// utils.h
#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

class Utils {
public:
    // Convert string to lowercase
    static string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    // Split string into tokens
    static vector<string> tokenize(const string& s) {
        vector<string> tokens;
        string token;
        size_t start = 0, end = 0;

        while ((end = s.find(" ", start)) != string::npos) {
            token = s.substr(start, end - start);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            start = end + 1;
        }

        token = s.substr(start);
        if (!token.empty()) {
            tokens.push_back(token);
        }

        return tokens;
    }

    // Check if string contains substring
    static bool contains(const string& str, const string& sub) {
        return toLower(str).find(toLower(sub)) != string::npos;
    }

    // Remove punctuation from end of string
    static string stripPunct(string s) {
        while (!s.empty() && ispunct(s.back())) {
            s.pop_back();
        }
        return s;
    }
};