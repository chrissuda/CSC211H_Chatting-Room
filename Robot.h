/* Jiajun Chen
    23966449
    CSC 211H - Spring 2020
    Feb.20th
    
    Assigment#2
    Robot.h
*/

#include <iostream>
#include "World.h"
using namespace std;

/*Define location in terms of (W,E,N,S) in(x,y)
x+->E             y+->S
*/

class Robot
{
private:
    Point point;
    enum orientation_type
    {
        north = 0,
        south,
        east,
        west
    };
    orientation_type orientation;
    int location[6];

public:
    Robot(int coin_location[])
    {
        for (int i = 0; i < 6; i++)
        {
            location[i] = coin_location[i];
        }
        cout << " " << endl;
    }

    void init()
    {
        point.set(0, 0);
        orientation = east;
    }

    bool check_coin()
    {
        for (int i = 0; i < 6;)
        {
            if (location[i] == point.getX() && location[i + 1] == point.getY())
                return true;
            else
                ;
            i += 2;
        }
        return false;
    }

    /*const method can be called by both const object
        and non-const object;*/
    void print() //const???
    {
        string direction[] = {"north", "south", "east", "west"};
        int x = point.getX();
        int y = point.getY();
        cout << "I am at ("
             << x
             << "," << y
             << ") and I am facing "
             << direction[orientation] << endl;

        if (check_coin())
        {
            cout << "I am at ("
                 << x
                 << "," << y
                 << ") finding the coin "
                 << "I am gonna be rich\n";
        }
    }

    int getOrientation()
    {
        return orientation;
    }

    void setOrientation(orientation_type orientation)
    {
        this->orientation = orientation;
    }

    bool forward()
    {
        int position;
        switch (orientation)
        {
        case 0:
            position = point.getY() - 1;
            if (position < 0)
            {
                return false;
            }
            else
            {
                point.set(point.getX(), position);
                print();
                return true;
            }
            break;
        case 1:
            position = point.getY() + 1;
            if (position > 9)
                return false;
            else
            {
                point.set(point.getX(), position);
                print();
                return true;
            }
            break;
        case 2:
            position = point.getX() + 1;
            if (position > 9)
                return false;
            else
            {
                point.set(position, point.getY());
                print();
                return true;
            }
            break;
        case 3:
            position = point.getX() - 1;
            if (position < 0)
                return false;
            else
            {
                point.set(position, point.getY());
                print();
                return true;
            }
            break;

        default:
            cout << "Wrong,went to default" << endl;
            return false;
        }
    }

    void turnCW()
    {
        switch (orientation)
        {
        case 0:
            orientation = east;
            break;
        case 1:
            orientation = west;
            break;

        case 2:
            orientation = south;
            break;
        case 3:
            orientation = north;
            break;
        }
    }
    void turnAntiCW()
    {
        switch (orientation)
        {
        case 0:
            orientation = west;
            break;
        case 1:
            orientation = east;
            break;

        case 2:
            orientation = north;
            break;
        case 3:
            orientation = south;
            break;
        }
    }
    bool eastEnd()
    {
        if (point.getX() == 9)
        {
            return true;
        }
        else
            return false;
    }

    bool westEnd()
    {
        if (point.getX() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool northEnd()
    {
        if (point.getY() == 0)
            return true;
        else
        {
            return false;
        }
    }
    bool southEnd()
    {
        if (point.getY() == 9)
            return true;
        else
            return false;
    }
    bool zag()
    {
        turnCW();
        forward();
        turnCW();
        return true;
    }
    bool zig()
    {
        turnAntiCW();
        forward();
        turnAntiCW();
        return true;
    }
};