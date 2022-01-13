#include "GameScene.h"

#include "GameHub.h"

namespace gol
{
    GameScene::GameScene(GameHub& game)
    : gf::Scene(game.getRenderer().getSize())
    , m_game(game)
    , instanceGameScene(nullptr)
    {
        game.getWindow().setFramerateLimit(1u);

        setClearColor(gf::Color::Black);

        for(int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < LENGTH; y++)
            {
                setCell(x,y,false);
            }
        }

        setCell(4,5,true);
        setCell(5,5,true);
        setCell(6,5,true);

        display();
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

    void GameScene::display()
    {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < LENGTH; y++)
            {
                std::cout << getCell(x,y);
            }
            std::cout << "" << std::endl;
        }
    }

    void GameScene::doUpdate(gf::Time time)
    {
        m_game.vm.interpretMethodFunction(instanceGameScene, m_game.vm.getFunctionName("update"), {});
    }

    void GameScene::doShow()
    {
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
            display();

            makeIteration();

            display();
            std::cout << std::endl << std::endl;
            
            return NULL_VAL;
        });
    }
}