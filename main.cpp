/* Jiajun Chen
    23966449
    CSC 211H - Spring 2020
    Feb.20th
    
    Assigment#2
    main.cpp
*/

/* This program create an Robot object.
And he will walk all over the room to find a coin.*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <math.h>
#include "World.h"
#include "Look_for.h"
#include "Robot.h"

using namespace std;

int main()
{
    std::cout << "Please input:"
              << "look-for"
              << "<coin1-x>  <coin1-y>  <coin2-x>  <coin2-y>  <coin3-x>  <coin3-y>\n";
    char input[50];
    int data[6], num_digit = 1, quotient;
    cin >> input;

    int total = atoi(input);
    std::cout << "total:" << total << endl;

    //identify how many number of digits
    do
    {
        quotient = total / pow(10, num_digit);
        num_digit += 1;
    } while (quotient > 1);

    // store int data into an array
    int remain = total;
    if (num_digit == 6)
    {
        for (int i = 6; i > 0; i--)
        {
            int divisor = pow(10, i - 1);
            int result = remain / divisor;
            remain %= divisor;
            if (result >= 0)
                data[6 - i] = result;

            else
            {
                std::cout << "The " << 6 - i << " Input should be in range(0-9)" << endl;
                std::cout << "Program terminating....\n";
                return 0;
            }
        }
    }
    else
    {
        std::cout << "Insufficient number of inputs,expect 6\n";
        std::cout << "Program is terminating....\n";
    }

    //create an Point object
    Point point;
    for (int i = 0; i < 6;)
    {
        point.set(data[i], data[i + 1]);
        std::cout << "x:" << point.getX() << "  y:" << point.getY() << endl;
        i += 2;
    }

    //create an World object
    World world;
    for (int i = 0; i < 3; i++)
    {
        world.set(i, data[i * 2], data[i * 2 + 1]);
    }
    world.print();

    Robot robot(data);
    robot.init();
    robot.print();

    while (true)
    {
        if (robot.eastEnd() && (robot.getOrientation() == 2))
        {
            robot.zag();
        }
        else if (robot.westEnd() && (robot.getOrientation() == 3))
        {
            robot.zig();
        }
        else if (robot.southEnd() && robot.westEnd())
        {
            break;
        }
        else
        {
            robot.forward();
        }
    }

    std::cout << "Demo finished!\n";
    return 0;
}