// knowledge.h
#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

// Relationship types between concepts
enum class RelType {
    IS_A,      // inheritance
    HAS_A,     // composition
    PART_OF,   // membership
    SIMILAR,   // similarity
    OPPOSITE   // antonym
};

// Enhanced concept representation
struct ConceptNode {
    string name;       // concept name
    map<string, vector<string>> props;  // properties
    vector<pair<RelType, string>> rels; // relationships
    vector<string> syn;                 // synonyms
    vector<string> ctx;                 // context words

    // Add a relationship to another concept
    void addRel(RelType type, const string& target) {
        rels.push_back({ type, target });
    }

    // Add a property
    void addProp(const string& key, const string& val) {
        props[key].push_back(val);
    }
};

class KnowledgeBase {
private:
    unordered_map<string, ConceptNode> concepts;

public:
    // Add or update a concept
    void addConcept(const string& name, const string& def) {
        if (!concepts.count(name)) {
            concepts[name] = ConceptNode();
            concepts[name].name = name;
        }
        concepts[name].props["def"].push_back(def);
    }

    // Add relationship between concepts
    void addRel(const string& from, RelType type, const string& to) {
        if (concepts.count(from) && concepts.count(to)) {
            concepts[from].addRel(type, to);
        }
    }

    // Get concept definition
    string getDef(const string& name) {
        return concepts.count(name) && !concepts[name].props["def"].empty()
            ? concepts[name].props["def"][0]
            : "";
    }

    // Check if concept exists
    bool hasConcept(const string& name) {
        return concepts.count(name) > 0;
    }
};