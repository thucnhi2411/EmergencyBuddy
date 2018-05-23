#include "allpost.h"

allpost::allpost()
{
    db=new EventDB("../pose.sqlite");
    posts = std::vector<post*>();

}


void allpost::reload(){
    int n = db->rowCount();

    for(int i = 1;i<=n;i++){
        bool has_post = false;
        for(post *p : posts){
            if(p->getid()==i) has_post=true;
        }
        if(!has_post){
            post *pp = new post();
            pp->seteventtype(db->geteventtype(i));
            pp->setlocation(db->getlocation(i));
            pp->setname(db->getname(i));
            pp->settime(db->geteventtime(i));
            pp->setnotitime(db->getnotitime(i));
            pp->setveri(db->getverify(i).toInt());
            pp->setinstr(db->getpublicinstruction(i));
            pp->setid(i);

            posts.push_back(pp);
        }


    }

}


std::vector<post*> *allpost::getPosts(){
    return &posts;
}
