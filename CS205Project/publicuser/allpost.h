#ifndef ALLPOST_H
#define ALLPOST_H
#include <vector>
#include "post.h"
#include "../DB/eventdb.h"
#include "puser.h"

class allpost
{
public:
    allpost();

    void reload();

    std::vector<post*> *getPosts();

private:
    std::vector<post*> posts;
    EventDB *db;


};

#endif // ALLPOST_H
