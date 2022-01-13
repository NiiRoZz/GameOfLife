#include "GameScene.h"

#include "GameHub.h"

namespace gol
{
    GameScene::GameScene(GameHub& game)
    : gf::Scene(game.getRenderer().getSize())
    , m_game(game)
    {
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

        for(int i = 0; i < 3; i++)
        {
            updateMatrix();
            display();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
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


    bool GameScene::getCellNext(int x, int y)
    {
        if(x >= 0 && x < WIDTH && y >= 0 && y < LENGTH)
        {
            return matrixNextCycle[x][y];
        }
        return false;
    }

    void GameScene::setCellNext(int x, int y, bool alive)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < LENGTH)
        {
            matrixNextCycle[x][y] = alive;
        }
    }

    int GameScene::nbAliveNeighbor(int x, int y)
    {
        int nbAliveNeighbor = 0;

        nbAliveNeighbor += getCell(x+1,y+1);
        nbAliveNeighbor += getCell(x+1,y-1);
        nbAliveNeighbor += getCell(x-1,y+1);
        nbAliveNeighbor += getCell(x-1,y-1);

        nbAliveNeighbor += getCell(x,y-1);
        nbAliveNeighbor += getCell(x,y+1);
        nbAliveNeighbor += getCell(x+1,y);
        nbAliveNeighbor += getCell(x-1,y);

        return nbAliveNeighbor;
    }

    bool GameScene::isAliveNextCycle(int x, int y)
    {
        return (nbAliveNeighbor(x,y) == 3 || (getCell(x,y) && nbAliveNeighbor(x,y) == 2));
    }

    void GameScene::updateMatrix()
    {
        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < LENGTH; y++)
            {
                setCellNext(x,y, isAliveNextCycle(x,y));
            }
        }

        for(int x = 0; x < WIDTH; x++)
        {
            for(int y = 0; y < LENGTH; y++)
            {

                matrix[x][y] = matrixNextCycle[x][y];
            }
        }
    }

    void GameScene::display() {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < LENGTH; y++)
            {
                std::cout << getCell(x,y);
            }
            std::cout << "" << std::endl;
        }
    }
}