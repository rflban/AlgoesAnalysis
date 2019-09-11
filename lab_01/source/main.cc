#include <iostream>

#include "WagnerFischer.h"
#include "LevenshteinRecursive.h"
#include "DamerauLevenshtein.h"
#include "DamerauLevenshteinRecursive.h"

using namespace std;

class CharWordHandler {
public:
    static int len(const char *str) {
        int l;

        for (l = 0; str[l] != 0; l++);

        return l;
    }
};

int main() {
    std::string s1;
    std::string s2;

    WagnerFischer<const char *> wf;
    LevenshteinRecursive<const char *> lr;
    DamerauLevenshtein<const char *> dl;
    DamerauLevenshteinRecursive<const char *> dlr;

    WagnerFischer<string> swf;
    LevenshteinRecursive<string> slr;
    DamerauLevenshtein<string> sdl;
    DamerauLevenshteinRecursive<string> sdlr;

    cin >> s1 >> s2;

    cout << wf.distance(s1.c_str(), s1.size(), s2.c_str(), s2.size()) << '\n';
    cout << lr.distance(s1.c_str(), s1.size(), s2.c_str(), s2.size()) << '\n';
    cout << dl.distance(s1.c_str(), s1.size(), s2.c_str(), s2.size()) << '\n';
    cout << dlr.distance(s1.c_str(), s1.size(), s2.c_str(), s2.size()) << '\n';

    cout << swf.distance(s1, s1.size(), s2, s2.size()) << '\n';
    cout << slr.distance(s1, s1.size(), s2, s2.size()) << '\n';
    cout << sdl.distance(s1, s1.size(), s2, s2.size()) << '\n';
    cout << sdlr.distance(s1, s1.size(), s2, s2.size()) << '\n';

    return 0;
}

