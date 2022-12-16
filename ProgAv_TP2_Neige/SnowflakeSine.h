#pragma once
#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include "Snowflake.h"

class SnowflakeSine : public Snowflake
{
public:
    SnowflakeSine(double x, double y);
    SnowflakeSine();

    void update(double dt) override;

private:
    double timeSinceStart;
};
