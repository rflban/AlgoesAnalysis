#ifndef AAL01_UTILITY_H_
#define AAL01_UTILITY_H_

#include <cstddef>

namespace Util {

template<typename _T>
inline static
_T **createMatrix(size_t n, size_t m) {
    int **matrix = (_T **)( new char[sizeof(_T *) * n + sizeof(_T) * n * m] );

    for (size_t i = 0; i < n; i++) {
        matrix[i] = (_T *)(matrix + n) + i * m;
    }

    return matrix;
}

template<typename _T, int _N, int _M>
struct autoMatrix {
    _T instance[_N][_M];
};

}

#endif // AAL01_UTILITY_H_

