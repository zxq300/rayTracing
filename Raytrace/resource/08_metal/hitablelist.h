#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitableList: public hitable
{
public:
    hitableList() {}
    hitableList(hitable **l, int n)
    {
        list = l;
        list_size = n;
    }
    virtual bool hit(const ray &r, float tmin, float tmax, hitRecord &rec) const;

    hitable **list;
    int list_size;
};

bool hitableList::hit(const ray &r, float t_min, float t_max, hitRecord &rec) const
{
    hitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    int i = 0;
    for(i = 0; i < list_size; i++)
    {
        // in main() we instantiate list[i] as sphere
        // so the list[i]->hit() is the hit() in class sphere
        // find the hit in t_min to closest object
        // upgrade the closest in the newest hit
        // this ensure the correct order of objects
        if(list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif
