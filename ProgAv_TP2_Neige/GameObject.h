#pragma once
class Player;

class GameObject
{
public:
    GameObject(double x, double y);

    virtual void update(double dt);
    virtual void render(SDL_Renderer* renderer) const;
    void testCollision(Player& obj);

    double getW() const;
    double getH() const;
    bool shouldDelete() const;

    double x;
    double y;
    double w, h;

    //////// INUTILE
    //double bloop[256];
    //double blaap[256];

protected:
    bool isColliding(Player& obj);
    virtual void collide(Player& obj) = 0;

    double vx;
    double vy;
    double ax;
    double ay;

    double color_r, color_g, color_b, color_a;
    bool deleteMe;

    //////// INUTILE
    //double bleep[256];
    //double bliip[256];
    //double bluup[256];
    //double blyyp[256];
};
