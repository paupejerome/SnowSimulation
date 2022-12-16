#pragma once
#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include "GameObject.h"
#include "Player.h"

enum SnowflakeType {snowflakeNoContact,snowflakeRebound, snowflakeSine, snowflake};

class Snowflake : public GameObject
{
public:
    Snowflake(double x, double y);
    Snowflake();

    void update(double dt) override;
    virtual void collide(Player& o) override;

    void init();
    void init(double newX, double newY);
    double initXRand();
    double initYRand();
    double initYTop();

    SnowflakeType SFtype;
};
