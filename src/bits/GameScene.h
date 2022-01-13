#pragma once

#include <gf/Scene.h>

#define LENGTH      20
#define WIDTH       20

namespace gol
{
    struct GameHub;

    class GameScene : public gf::Scene
    {
    public:
        GameScene(GameHub& game);

        bool getCell(int x, int y);
        void setCell(int x, int y, bool alive);

        bool getCellNext(int x, int y);
        void setCellNext(int x, int y, bool alive);

        bool isAliveNextCycle(int x, int y);
        int nbAliveNeighbor(int x, int y);
        void updateMatrix();

        void display();

    private:
        GameHub& m_game;
        bool matrix[LENGTH][WIDTH];
        bool matrixNextCycle[LENGTH][WIDTH];
    };
}