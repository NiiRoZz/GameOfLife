#pragma once

#include <gf/Scene.h>
#include <Pomme/Object.h>

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

        void setCellNext(int x, int y, bool alive);

        void makeIteration();

        void display();

    protected:
        virtual void doUpdate(gf::Time time) override;
        virtual void doShow() override;

    private:
        GameHub& m_game;
        bool matrix[LENGTH][WIDTH];
        bool matrixNextCycle[LENGTH][WIDTH];

        Pomme::ObjInstance* instanceGameScene;
    };
}