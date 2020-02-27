/* Jiajun Chen
    23966449
    CSC 211H - Spring 2020
    Feb.20th
    
    Assigment#2
    Look_for.h
*/

#ifndef LOOK_FOR_H
#define LOOK_FOR_H
class Point
{
private:
    int x;
    int y;

public:
    void print()
    {
        std::cout << "X:" << x;
        std::cout << " Y:" << y << std::endl;
    }
    void set(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int getX() { return this->x; }
    int getY() { return this->y; }
};
#endif
