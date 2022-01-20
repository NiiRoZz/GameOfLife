#pragma once

#include <gf/Scene.h>
#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <Pomme/Object.h>

#include "GridEntity.h"

namespace gol
{
    struct GameHub;

    class GameScene : public gf::Scene
    {
    public:
        static constexpr std::size_t WIDTH = 20u;
        static constexpr std::size_t LENGTH = 20u;

    public:
        GameScene(GameHub& game);

        bool getCell(int x, int y);
        void setCell(int x, int y, bool alive);

        void setCellNext(int x, int y, bool alive);

        void makeIteration();

    protected:
        virtual void doUpdate(gf::Time time) override;
        virtual void doShow() override;

    private:
        GameHub& m_game;
        bool matrix[LENGTH][WIDTH];
        bool matrixNextCycle[LENGTH][WIDTH];

        Pomme::ObjInstance* instanceGameScene;

        GridEntity m_grid;
    };
}