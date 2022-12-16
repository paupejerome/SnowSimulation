#pragma once
#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include "Snowflake.h"

class SnowflakeRebound : public Snowflake
{
public:
    SnowflakeRebound(double x, double y);
    SnowflakeRebound();

    void update(double dt) override;
    void collide(Player& o) override;

private:
    bool alreadyHit;
    void rebound();
};
