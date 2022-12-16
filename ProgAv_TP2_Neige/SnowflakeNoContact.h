#pragma once
#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include "Snowflake.h"

class SnowflakeNoContact : public Snowflake
{
public:
    SnowflakeNoContact(double x, double y);
    SnowflakeNoContact();

    void collide(Player& o) override;
};
