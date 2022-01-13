#include "GameScene.h"

#include "GameHub.h"

namespace gol
{
    GameScene::GameScene(GameHub& game)
    : gf::Scene(game.getRenderer().getSize())
    , m_game(game)
    {
        setClearColor(gf::Color::Black);
    }
}