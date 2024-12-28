// processor.h
#pragma once
#include "token.h"
#include "text_processor.h"
#include "knowledge.h"
#include "utils.h"
#include <memory>

class Processor {
private:
    TextProcessor txtProc;     // text processing
    KnowledgeBase kb;         // knowledge base
    vector<Entity> entities;   // tracked entities

    // Parse input into tokens with POS and entity tags
    vector<Token> parse(const string& input) {
        vector<Token> tokens;
        auto words = Utils::tokenize(input);

        for (const auto& w : words) {
            Token t;
            t.text = w;
            t.lemma = txtProc.lemmatize(w);
            // Add POS tagging and entity recognition here
            tokens.push_back(t);
        }

        return tokens;
    }

    // Extract key terms from question
    string extractTerm(const vector<Token>& tokens) {
        if (tokens.size() < 3) return "";

        // Handle articles (a, an, the)
        int offset = 0;
        string lastWord = Utils::toLower(tokens.back().text);
        string corrected = txtProc.correctSpelling(lastWord);

        return Utils::stripPunct(corrected);
    }

public:
    Processor() {
        // Initialize knowledge
        kb.addConcept("dog", "A friendly domestic animal that barks");
        kb.addConcept("cat", "A domestic feline pet that meows");

        // Add relationships
        kb.addRel("dog", RelType::IS_A, "animal");
        kb.addRel("cat", RelType::IS_A, "animal");
    }

    string process(const string& input) {
        auto tokens = parse(input);
        if (tokens.empty()) return "Please say something.";

        // Handle questions
        if (tokens[0].lemma == "what" && tokens.size() >= 3) {
            string term = extractTerm(tokens);
            term = txtProc.correctSpelling(term);

            if (kb.hasConcept(term)) {
                return kb.getDef(term);
            }
            return "I don't know about " + term + " yet.";
        }

        // Handle "how are you"
        if (tokens.size() >= 3 &&
            tokens[0].lemma == "how" &&
            tokens[1].lemma == "be" &&
            tokens[2].text == "you") {
            return "I'm functioning well, thank you for asking.";
        }

        return "I'm still learning to understand that type of sentence.";
    }

    void learn(const string& word, const string& def) {
        kb.addConcept(Utils::toLower(word), def);
    }
};