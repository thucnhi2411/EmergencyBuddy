#ifndef ALLTASK_H
#define ALLTASK_H
#include <vector>
#include "task.h"
#include "../DB/frtaskdb.h"

class alltask
{
public:
    alltask();

    void reload();

    std::vector<task*> *getTasks();
private:
    std::vector<task*> tasks;
    FrTaskDB *db;
};

#endif // ALLTASK_H
