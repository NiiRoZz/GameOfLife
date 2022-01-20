#pragma once

#include <gf/Entity.h>
#include <gf/Grid.h>
#include <gf/ResourceManager.h>

namespace gol
{
    class GameScene;

    class GridEntity: public gf::Entity
    {
    public:
        GridEntity(GameScene& scene, gf::ResourceManager& resources, int priority = 0);

        virtual void update(gf::Time time) override;

        virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
    private:
        gf::Grid m_grid;

        GameScene& m_gamescene;

        std::size_t m_framerate;

        gf::Font& m_font;
    };
}