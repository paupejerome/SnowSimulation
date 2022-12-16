#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Snowflake.h"
using namespace std;

Snowflake::Snowflake(double x, double y)
    : GameObject{x, y}
{
    w = 3;
    h = 6;
    color_r = 0.8;
    color_g = 0.8;
    color_b = 1;
    color_a = 0.3;
    vy = 100 + rand()/(double)RAND_MAX * 100;
}
Snowflake::Snowflake()
    :GameObject{initXRand(),initYRand()}
{
    w = 3;
    h = 6;
    color_r = 0.8;
    color_g = 0.8;
    color_b = 1;
    color_a = 0.3;
    vy = 100 + rand() / (double)RAND_MAX * 100;
}

void Snowflake::update(double dt)
{
    GameObject::update(dt);
    if(y > SCREEN_HEIGHT + h)
        deleteMe = true;
}

void Snowflake::collide(Player& p)
{
    deleteMe = true;
}

void Snowflake::init()
{
    x = initXRand();
    y = initYTop();
}
void Snowflake::init(double newX, double newY)
{
    x = newX;
    y = newY;
}
double Snowflake::initXRand()
{
    return (rand() / (double)RAND_MAX * SCREEN_WIDTH);
}
double Snowflake::initYRand()
{
    return (rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10);
}
double Snowflake::initYTop()
{
    return -10;
}
