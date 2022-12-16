#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"
#include <vector>
using namespace std;
#include "GameObject.h"
#include "Player.h"

GameObject::GameObject(double x, double y) :
    x{x}, y{y},
    vx{0}, vy{0}, ax{0}, ay{0},
    deleteMe{false}
{}

void GameObject::update(double dt)
{
    vx += dt * ax;
    vy += dt * ay;
    x += dt * vx;
    y += dt * vy;
}

void GameObject::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer,
        (int)(color_r * 255),
        (int)(color_g * 255),
        (int)(color_b * 255),
        (int)(color_a * 255));
    SDL_Rect r;
    r.x = (int)x;
    r.y = (int)y;
    r.w = (int)w;
    r.h = (int)h;
    SDL_RenderFillRect(renderer, &r);
}

void GameObject::testCollision(Player& p)
{
    if(isColliding(p))
        collide(p);
}

bool GameObject::isColliding(Player& p)
{
    //////// V1
    //const int LEFT = 0;
    //const int RIGHT = 1;
    //const int TOP = 2;
    //const int BOTTOM = 3;
    //vector<double> playerCoords;
    //vector<double> myCoords;

    //// Left
    //myCoords.push_back(x);
    //playerCoords.push_back(p.x);

    //// Right
    //myCoords.push_back(x + w);
    //playerCoords.push_back(p.x + p.w);

    //// Top
    //myCoords.push_back(y);
    //playerCoords.push_back(p.y);


    //// Bottom
    //myCoords.push_back(y + h);
    //playerCoords.push_back(p.y + p.h);

    //return !(
    //    // Un à gauche de l'autre
    //    playerCoords[RIGHT] < myCoords[LEFT] ||
    //    myCoords[RIGHT] < playerCoords[LEFT] ||

    //    // Un en haut de l'autre
    //    playerCoords[BOTTOM] < myCoords[TOP] ||
    //    myCoords[BOTTOM] < playerCoords[TOP]
    //    );


    //////// V2
    double pLeft, pRight, pTop, pBottom;
    double mLeft, mRight, mTop, mBottom;

    mLeft = x;
    pLeft = p.x;
    mRight = x + w;
    pRight = p.x + p.w;
    mTop = y;
    pTop = p.y;
    mBottom = y + h;
    pBottom = p.y + p.h;

    return !(
        pRight < mLeft ||
        mRight < pLeft ||
        pBottom < mTop ||
        mBottom < pTop
        );

}

bool GameObject::shouldDelete() const
{
    return deleteMe;
}
