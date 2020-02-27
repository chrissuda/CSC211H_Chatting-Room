/* Jiajun Chen
    23966449
    CSC 211H - Spring 2020
    Feb.20th
    
    Assigment#2
    World.h
*/

#ifndef WORLD_H
#define WORLD_H
#include "Look_for.h"
class World
{
private:
    Point points[3];

public:
    void print()
    {
        for (int i = 0; i < 3; i++)
        {
            points[i].print();
        }
    }

    void set(int i, int x, int y)
    {
        points[i].set(x, y);
    }
};
#endif