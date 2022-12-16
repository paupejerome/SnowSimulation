#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "\10-ProjetVolumineux\ProgAvance\SDL2-devel-2.0.16-VC\SDL2-2.0.16\include\SDL.h"

#include "Constants.h"
#include "GameSnow.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
#include "SnowflakePool.h"
using namespace std;

GameSnow::GameSnow() :
    m_pause(false),
    p(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
{
    debugCheakSizeof();
    cout << endl;
    init(presets[0]);
}
void GameSnow::init(int nbSnowflakes)
{
    //////// ORIGINAL
    //cout << "Init with " << nbSnowflakes << " particles" << endl;
    //snowflakes.clear();
    //for (int i = 0; i < nbSnowflakes; i++)
    //{
    //    double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
    //    double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
    //    addSnowflake(x, y);
    //}

    cout << "Nb snowflakes : " << sfPool.getNbParticles() << " , MAX_SNOWFLAKES : " << MAX_SNOWFLAKES << endl;
}
void GameSnow::debugCheakSizeof()
{
    cout << "sizeof(GameObject) : " << sizeof(GameObject) << endl;
    cout << "sizeof(Player) : " << sizeof(Player) << endl;
    cout << "sizeof(Snowflake) : " << sizeof(Snowflake) << endl;
    cout << "sizeof(SnowflakeNoContact) : " << sizeof(SnowflakeNoContact) << endl;
    cout << "sizeof(SnowflakeRebound) : " << sizeof(SnowflakeRebound) << endl;
    cout << "sizeof(SnowflakeSine) : " << sizeof(SnowflakeSine) << endl;
}

void GameSnow::handleInput(const SDL_Event& event)
{
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            p.x = x;
            p.y = y;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            p.inputs.left = false;
            break;
        case SDLK_RIGHT:
            p.inputs.right = false;
            break;
        case SDLK_DOWN:
            p.inputs.down = false;
            break;
        case SDLK_UP:
        case SDLK_SPACE:
            p.inputs.jump = false;
            break;
        }
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            p.inputs.left = true;
            break;
        case SDLK_RIGHT:
            p.inputs.right = true;
            break;
        case SDLK_DOWN:
            p.inputs.down = true;
            break;
        case SDLK_UP:
        case SDLK_SPACE:
            p.inputs.jump = true;
            break;

            // Pause
        case SDLK_p:
            m_pause = !m_pause;
            break;

        case SDLK_1:
        case SDLK_2:
        case SDLK_3:
        case SDLK_4:
        case SDLK_5:
        case SDLK_6:
        case SDLK_7:
        case SDLK_8:
        case SDLK_9:
            init(presets[event.key.keysym.sym - SDLK_1]);
            break;

        case SDLK_ESCAPE:
            keepPlaying = false;
            break;
        }
    }
}

void GameSnow::update(unsigned long dt)
{
    if (m_pause) return;
    double delta_t = dt / 1000.0;

    // Physics
    p.update(delta_t);

    //////// TEMPLATELESS
    for (int i = 0; i < sfPool.nbSF; i++)
        sfPool.getSF(i).update(delta_t);
    for (int i = 0; i < sfPool.nbSFNC; i++)
        sfPool.getSFNC(i).update(delta_t);
    for (int i = 0; i < sfPool.nbSFR; i++)
        sfPool.getSFR(i).update(delta_t);
    for (int i = 0; i < sfPool.nbSFS; i++)
        sfPool.getSFS(i).update(delta_t);

    //////// TEMPLATED
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    sfPool.get<Snowflake>(i).update(delta_t);
    //for (int i = 0; i < sfPool.nbSFNC; i++)
    //    sfPool.get<SnowflakeNoContact>(i).update(delta_t);
    //for (int i = 0; i < sfPool.nbSFR; i++)
    //    sfPool.get<SnowflakeRebound>(i).update(delta_t);
    //for (int i = 0; i < sfPool.nbSFS; i++)
    //    sfPool.get<SnowflakeSine>(i).update(delta_t);


    // Collisions

    ////////// TEMPLATELESS
    for (int i = 0; i < sfPool.nbSF; i++)
        sfPool.getSF(i).testCollision(p);
    for (int i = 0; i < sfPool.nbSFNC; i++)
        sfPool.getSFNC(i).testCollision(p);
    for (int i = 0; i < sfPool.nbSFR; i++)
        sfPool.getSFR(i).testCollision(p);
    for (int i = 0; i < sfPool.nbSFS; i++)
        sfPool.getSFS(i).testCollision(p);

    //////// TEMPLATED
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    sfPool.get<Snowflake>(i).testCollision(p);
    //for (int i = 0; i < sfPool.nbSFNC; i++)
    //    sfPool.get<SnowflakeNoContact>(i).testCollision(p);
    //for (int i = 0; i < sfPool.nbSFR; i++)
    //    sfPool.get<SnowflakeRebound>(i).testCollision(p);
    //for (int i = 0; i < sfPool.nbSFS; i++)
    //    sfPool.get<SnowflakeSine>(i).testCollision(p);

    // Remove unused objects
    long size_before = sfPool.getNbParticles();

    //////// TEMPLATELESS
    for (int i = 0; i < sfPool.nbSF; i++)
        if (sfPool.getSF(i).shouldDelete())
            sfPool.destroySF(i);
    for (int i = 0; i < sfPool.nbSFNC; i++)
        if (sfPool.getSFNC(i).shouldDelete())
            sfPool.destroySFNC(i);
    for (int i = 0; i < sfPool.nbSFR; i++)
        if (sfPool.getSFR(i).shouldDelete())
            sfPool.destroySFR(i);
    for (int i = 0; i < sfPool.nbSFS; i++)
        if (sfPool.getSFS(i).shouldDelete())
            sfPool.destroySFS(i);

    //////// TEMPLATED
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    if(sfPool.get<Snowflake>(i).shouldDelete())
    //        sfPool.destroySF(i);
    //for (int i = 0; i < sfPool.nbSFNC; i++)
    //    if (sfPool.get<SnowflakeNoContact>(i).shouldDelete())
    //        sfPool.destroySFNC(i);
    //for (int i = 0; i < sfPool.nbSFR; i++)
    //    if (sfPool.get<SnowflakeRebound>(i).shouldDelete())
    //        sfPool.destroySFR(i);
    //for (int i = 0; i < sfPool.nbSFS; i++)
    //    if (sfPool.get<SnowflakeSine>(i).shouldDelete())
    //        sfPool.destroySFS(i);

    long nb_new_snowflakes = size_before - sfPool.getNbParticles();

    for (int i = 0; i < nb_new_snowflakes; i++)
        sfPool.spawnParticle();
}

void GameSnow::render(SDL_Renderer* renderer) const
{
    // -- Clear screen --
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    // Draw particles
    p.render(renderer);

    //////// TEMPLATELESS
    for (int i = 0; i < sfPool.nbSF; i++)
        sfPool.getSF(i).render(renderer);
    for (int i = 0; i < sfPool.nbSFNC; i++)
        sfPool.getSFNC(i).render(renderer);
    for (int i = 0; i < sfPool.nbSFR; i++)
        sfPool.getSFR(i).render(renderer);
    for (int i = 0; i < sfPool.nbSFS; i++)
        sfPool.getSFS(i).render(renderer);

    //////// TEMPLATELETED
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    sfPool.get<Snowflake>(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSFNC; i++)
    //    sfPool.get<SnowflakeNoContact>(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSFR; i++)
    //    sfPool.get<SnowflakeRebound>(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSFS; i++)
    //    sfPool.get<SnowflakeSine>(i).render(renderer);

    //////// V3
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    if (!sfPool.getSF(i).shouldDelete())
    //        sfPool.getSF(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSFNC; i++)
    //    if (!sfPool.getSFNC(i).shouldDelete())
    //        sfPool.getSFNC(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSF; i++)
    //    if (!sfPool.getSFR(i).shouldDelete())
    //        sfPool.getSFR(i).render(renderer);
    //for (int i = 0; i < sfPool.nbSFS; i++)
    //    if (!sfPool.getSFS(i).shouldDelete())
    //        sfPool.getSFS(i).render(renderer);

    SDL_RenderPresent(renderer);
}
