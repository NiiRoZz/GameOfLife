#pragma once

#include <gf/Scene.h>

namespace gol
{
    struct GameHub;

    class GameScene : public gf::Scene
    {
    public:
        GameScene(GameHub& game);

    private:
        GameHub& m_game;
    };
}