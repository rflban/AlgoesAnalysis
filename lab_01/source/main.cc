#include <iostream>

#include "EditDistanceTester.h"
#include "CharWordHandler.h"

using namespace std;

int main(int argc, char **argv) {
    bool showTime = false;
    bool isLoop = false;

    std::string s1;
    std::string s2;

    auto tester = new EditDistanceTester<string>;
    tester->enableOptInfo();

    for (int idx = 1; idx < argc; idx++) {
        switch (argv[idx][0]) {
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
        case 'o':
            tester->enableOptInfo();
            break;
        case 'O':
            tester->disableOptInfo();
            break;
        case 't':
            showTime = true;
            break;
        case 'T':
            showTime = false;
            break;
        case 'l':
            isLoop = true;
            break;
        case 'L':
            isLoop = false;
            break;
        }
    }

    while (getline(cin, s1), getline(cin, s2), cin.good()) {
        cout << tester->calculate(s1, s2) << " ";

        if (showTime)
            cout << tester->timeTestResult();

        cout << '\n';

        if (!isLoop) {
            break;
        }
    }

    delete tester;

    return 0;
}

