#pragma once
#include <vector>
#include <memory>

#include "Player.h"
#include "Snowflake.h"
#include "SnowflakePool.h"
#include "Game.h"


class GameSnow : public Game
{
public:
    GameSnow();

    void handleInput(const SDL_Event& event) override;
    void update(unsigned long dt) override;
    void render(SDL_Renderer* renderer) const override;

    void init(int nbSnowflakes);

    void debugCheakSizeof();

private:
    bool m_pause;
    unsigned long presets[9] = {1000, 2500, 5000, 6000, 7000, 8000, 9000, 10000, 12000};

    Player p;

    //////// ORIGINAL
    //std::vector<std::unique_ptr<Snowflake>> snowflakes;
    
    //////// MOI
    SnowflakePool sfPool;
};
