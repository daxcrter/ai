// token.h
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

// Part of speech tags
enum class POS {
    NOUN, VERB, ADJ, ADV, PREP, DET, PRON, CONJ, NUM, UNK
};

// Entity types
enum class EntityType {
    PERSON, LOC, ORG, DATE, NUM, MISC, NONE
};

// Represents a single token with its properties
struct Token {
    string text;        // original text
    string lemma;       // base form
    POS pos;           // part of speech
    EntityType ent;    // entity type
    size_t start;      // position in original text
    size_t end;        // end position
};

// Represents a span of tokens forming an entity
struct Entity {
    string text;       // entity text
    EntityType type;   // entity type
    vector<Token*> tokens; // tokens in this entity
};