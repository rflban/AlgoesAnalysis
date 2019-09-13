#ifndef AAL01_CHARWORDHANDLER_H_
#define AAL01_CHARWORDHANDLER_H_

#include <string>

class CharWordHandler {
public:
    static int len(const char *str) {
        int l;

        for (l = 0; str[l] != 0; l++);

        return l;
    }

    static int len(const std::string &str) {
        return str.size();
    }
};


#endif // AAL01_CHARWORDHANDLER_H_

