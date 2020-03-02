#ifndef AAL06_UTILITY_H_
#define AAL06_UTILITY_H_

#include <cstddef>
#include <iostream>

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

template<typename _T>
inline static
_T **copyMatrix(_T **const &data, size_t n, size_t m)
{
    _T **copy = Util::createMatrix<_T>(n, m);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            copy[i][j] = data[i][j];
        }
    }

    return copy;
}

template<typename _T>
inline static
void scanMatrix(_T **&data, size_t n, size_t m)
{
    data = Util::createMatrix<_T>(n, m);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

template<typename _T>
inline static
void typeMatrix(_T **const &data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cout << data[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

}

#endif // AAL06_UTILITY_H_

