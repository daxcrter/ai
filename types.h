// types.h - Core data structures and types
#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

// Represents a word or phrase pattern with wildcards
struct Pattern {
    vector<string> tokens;     // fixed words in pattern
    vector<string> wildcards;  // variable parts
    float conf;               // match confidence 0-1
};

// Stores knowledge about a word/concept
struct Concept {
    string word;              // primary word
    vector<string> syn;       // synonyms
    vector<string> rel;       // related words
    map<string, vector<string>> props;  // properties
};

// Types of sentences we can handle
enum class SentType {
    QUESTION,    // interrogative
    STATEMENT,   // declarative
    COMMAND,     // imperative
    UNKNOWN      // unrecognized
};