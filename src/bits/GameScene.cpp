#include "GameScene.h"

#include "GameHub.h"

namespace gol
{
    GameScene::GameScene(GameHub& game)
    : gf::Scene(game.getRenderer().getSize())
    , m_game(game)
    , instanceGameScene(nullptr)
    , m_grid(*this, game.resources)
    , m_stopAction("StopAction")
    , m_stop(false)
    {
        game.getWindow().setFramerateLimit(14u);
        game.getWindow().setVerticalSyncEnabled(false);

        setClearColor(gf::Color::Black);

        std::memset(matrix, 0, WIDTH * LENGTH);
        std::memset(matrixNextCycle, 0, WIDTH * LENGTH);

        matrix[3][1]=true;
        matrix[4][2]=true;
        matrix[4][3]=true;
        matrix[3][3]=true;
        matrix[2][3]=true;

        m_stopAction.addKeycodeKeyControl(gf::Keycode::Space);
        m_stopAction.setInstantaneous();
        addAction(m_stopAction);

        addHudEntity(m_grid);
    }

    bool GameScene::getCell(int x, int y)
    {
        if(x >= 0 && x < WIDTH && y >= 0 && y < LENGTH)
        {
            return matrix[x][y];
        }

        return false;
    }

    void GameScene::setCell(int x, int y, bool alive)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < LENGTH)
        {
            matrix[x][y] = alive;
        }
    }

    void GameScene::setCellNext(int x, int y, bool alive)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < LENGTH)
        {
            matrixNextCycle[x][y] = alive;
        }
    }

    void GameScene::makeIteration()
    {
        for(int x = 0; x < WIDTH; ++x)
        {
            for(int y = 0; y < LENGTH; ++y)
            {
                matrix[x][y] = matrixNextCycle[x][y];
            }
        }
    }

    void GameScene::doHandleActions(gf::Window& window)
    {
        if (m_stopAction.isActive())
        {
            m_stop = !m_stop;
        }
    }

    void GameScene::doUpdate(gf::Time time)
    {
        gf::Scene::doUpdate(time);

        if (!m_stop)
        {
            m_game.vm.interpretMethodFunction(instanceGameScene, m_game.vm.getFunctionName("update"), {});
        }
    }

    void GameScene::doShow()
    {
        gf::Scene::doShow();

        instanceGameScene = m_game.vm.newInstance("GameScene");

        instanceGameScene->linkMethodNative(m_game.vm, m_game.vm.getFunctionName("getCell", "int", "int"), [&] (Pomme::VirtualMachine& vm, int argCount, Pomme::ObjInstance* instance, Pomme::Value* args) {
            int x = AS_INT(args[0]);
            int y = AS_INT(args[1]);

            return BOOL_VAL(getCell(x, y));
        });

        instanceGameScene->linkMethodNative(m_game.vm, m_game.vm.getFunctionName("setNextCell", "int", "int", "bool"), [&] (Pomme::VirtualMachine& vm, int argCount, Pomme::ObjInstance* instance, Pomme::Value* args) {
            int x = AS_INT(args[0]);
            int y = AS_INT(args[1]);
            bool alive = AS_BOOL(args[2]);

            setCellNext(x, y, alive);

            return NULL_VAL;
        });

        instanceGameScene->linkMethodNative(m_game.vm, m_game.vm.getFunctionName("makeIteration"), [&] (Pomme::VirtualMachine& vm, int argCount, Pomme::ObjInstance* instance, Pomme::Value* args) {
            makeIteration();
            
            return NULL_VAL;
        });
    }
}