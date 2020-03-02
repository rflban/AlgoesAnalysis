#ifndef AA06_SALESMAN_H_
#define AA06_SALESMAN_H_

#include <cstddef>

class Salesman
{
public:
    inline
    void set(size_t **distances, size_t len)
    { this->distances = distances; this->len = len; }

    inline
    size_t **map()
    { return distances; }
    inline
    size_t length()
    { return len; }

    size_t distance(size_t *way, size_t qty);

    virtual size_t **operator()(size_t &minDist) = 0;

private:
    size_t len;
    size_t **distances;
};

#endif // AA06_SALESMAN_H_

