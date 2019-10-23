#include <iostream>

#include "EditDistanceTester.h"
#include "CharWordHandler.h"

using namespace std;

int main(int argc, char **argv) {
    int testTimes = 5;

    bool showTime = false;
    bool isLoop = false;
    bool showMinLen = false;
    bool showMaxLen = false;
    bool showDist = true;

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
        case 'i':
            showMinLen = true;
            break;
        case 'I':
            showMinLen = false;
            break;
        case 's':
            showMaxLen = true;
            break;
        case 'S':
            showMaxLen = false;
            break;
        case 'd':
            showDist = true;
            break;
        case 'D':
            showDist = false;
            break;
        }
    }

    while (getline(cin, s1), getline(cin, s2), cin.good()) {

        int dist = tester->calculate(s1, s2);
        long long timeRes = tester->timeTestResult();

        for (int idx = 0; idx < testTimes - 1; idx++) {
            tester->calculate(s1, s2);
            timeRes += tester->timeTestResult();
        }
        timeRes /= testTimes;

        if (showDist)
            cout << dist << " ";

        if (showMinLen)
            cout << min(s1.size(), s2.size()) << " ";
        if (showMaxLen)
            cout << max(s1.size(), s2.size()) << " ";

        if (showTime)
            cout << timeRes;

        cout << '\n';

        if (!isLoop) {
            break;
        }
    }

    delete tester;

    return 0;
}

