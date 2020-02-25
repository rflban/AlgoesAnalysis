#ifndef AAL04_UTILITY_H_
#define AAL04_UTILITY_H_

#include <cstddef>
#include <cstdio>

namespace Util
{

template<typename _T>
inline static
_T **createMatrix(size_t n, size_t m)
{
    _T **matrix = (_T **)( new char[sizeof(_T *) * n + sizeof(_T) * n * m] );

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = (_T *)(matrix + n) + i * m;
    }

    return matrix;
}

}

#endif // AAL04_UTILITY_H_

