#include <iostream>

#include "EditDistanceTester.h"
#include "CharWordHandler.h"

using namespace std;

int main(int argc, char **argv) {
    std::string s1;
    std::string s2;
    auto tester = new EditDistanceTester<string>;

    if (argc > 0) {
        switch (argv[0][0]) {
        case '0':
            tester->toLevenshteinRec();
            break;
        case '1':
            tester->toWagnerFischer();
            break;
        case '2':
            tester->toDamerauLevenshtein();
            break;
        case '3':
            tester->toDamerauLevenshteinRec();
            break;
        }
    }

    while ((cin >> s1 >> s2).good()) {
        cout << tester->calculate(s1, s2) << " ";
        cout << tester->timeTestResult() << '\n';
    }

    delete tester;

    return 0;
}

