#ifndef LOADER
#define LOADER

#include "infinite_world.h"

class Loader
{
public:
    Loader();
    ~Loader();
private:
    InfiniteWorld *_map;
};

#endif // LOADER
