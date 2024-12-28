// text_proc.h
#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "utils.h"
using namespace std;

class TextProcessor {
private:
    unordered_map<string, string> lemmas;  // word -> base form
    unordered_set<string> vocab;           // known words

    // Levenshtein distance for spelling correction
    int levDist(const string& s1, const string& s2) {
        vector<vector<int>> dp(s1.length() + 1,
            vector<int>(s2.length() + 1));

        for (size_t i = 0; i <= s1.length(); i++) {
            for (size_t j = 0; j <= s2.length(); j++) {
                if (i == 0) dp[i][j] = j;
                else if (j == 0) dp[i][j] = i;
                else if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min({ dp[i - 1][j],    // deletion
                                      dp[i][j - 1],       // insertion
                                      dp[i - 1][j - 1] });   // replacement
            }
        }
        return dp[s1.length()][s2.length()];
    }

public:
    TextProcessor() {
        // Initialize with common word forms
        loadDict();
    }

    // Load dictionary and word forms
    void loadDict() {
        // Common irregular verbs
        lemmas["am"] = "be";
        lemmas["is"] = "be";
        lemmas["are"] = "be";
        lemmas["was"] = "be";
        lemmas["were"] = "be";

        // Add common words to vocab
        vocab = { "dog", "cat", "human", "animal", "computer",
                "program", "system", "the", "a", "an", "is",
                "are", "what", "how", "who", "where", "when" };
    }

    // Get base form of word
    string lemmatize(const string& word) {
        string w = Utils::toLower(word);
        return lemmas.count(w) ? lemmas[w] : w;
    }

    // Correct spelling errors
    string correctSpelling(const string& word) {
        if (vocab.count(word)) return word;

        string bestMatch = word;
        int minDist = INT_MAX;

        for (const auto& w : vocab) {
            int dist = levDist(word, w);
            if (dist < minDist) {
                minDist = dist;
                bestMatch = w;
            }
        }

        return minDist <= 2 ? bestMatch : word;
    }
};