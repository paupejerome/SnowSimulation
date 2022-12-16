#pragma once
#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include <string>
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(double x, double y);

    void update(double dt) override;
    void render(SDL_Renderer* renderer) const override;

    void collide(Player& o) override;

    struct Inputs {
        bool left;
        bool right;
        bool down;
        bool jump;
    } inputs;
private:
    bool isJumping;
};
