#include <iostream>

#include "EditDistanceTester.h"
#include "CharWordHandler.h"

using namespace std;

int main(int argc, char **argv) {
    bool showTime = false;

    std::string s1;
    std::string s2;
    auto tester = new EditDistanceTester<string>;

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
        }
    }

    while (cin.good()) {
        getline(cin, s1);
        getline(cin, s2);

        cout << tester->calculate(s1, s2) << " ";

        if (showTime)
            cout << tester->timeTestResult();

        cout << '\n';
    }

    delete tester;

    return 0;
}

