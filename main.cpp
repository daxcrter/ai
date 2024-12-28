// main.cpp
#include "processor.h"
#include <iostream>

int main() {
    Processor ai;

    // Add some knowledge
    ai.learn("doge", "A friendly domestic animal that MEWS.");
    ai.learn("programming", "The art of telling computers what to do.");

    // Test cases
    vector<string> tests = {
        // 1. Valid Queries (Expected to be answered correctly)
        "What is a doge?",
        "What is dog?",
        "What is a human?",

        // 2. Semantic Variations (Rephrased valid queries)
        "Tell me about doge.",
        "Explain what a dog is.",
        "Can you describe a dog?",

        // 3. Edge Cases (Typos, grammatical errors)
        "What is an doge?",
        "What is dogge?",
        "What aree dog?",

        // 4. Unsupported Inputs (Not in the knowledge base)
        "What is a cat?",
        "Explain gravity.",
        "Tell me about space.",

        // 5. Statements (Non-questions)
        "The cat is brown.",
        "Dogs are friendly animals.",

        // 6. Ambiguous/Incomplete Inputs
        "How are s?",
        "What is?",
        "Tell me about.",
    };


    for (const auto& test : tests) {
        cout << "Input: " << test << '\n';
        cout << "Response: " << ai.process(test) << "\n\n";
    }

    return 0;
}