#include "GridEntity.h"

#include "GameScene.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Text.h>

namespace gol
{
    GridEntity::GridEntity(GameScene& scene, gf::ResourceManager& resources, int priority)
    : gf::Entity(priority)
    , m_gamescene(scene)
    , m_framerate(60u)
    , m_font(resources.getFont("Aquifer.otf"))
    {
    }

    void GridEntity::update(gf::Time time)
    {
        m_framerate = 1.f / time.asSeconds();
    }

    void GridEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
    {
        gf::Coordinates coordinates(target);

        float xSize = coordinates.getWindowSize().x / GameScene::WIDTH;
        float ySize = coordinates.getWindowSize().y / GameScene::LENGTH;

        if (xSize > ySize)
        {
            xSize = ySize;
        }
        else
        {
            ySize = xSize;
        }
        
        m_grid = gf::Grid::createOrthogonal({GameScene::WIDTH, GameScene::LENGTH}, {xSize, ySize});
        m_grid.setPosition(coordinates.getCenter());
        m_grid.setAnchor(gf::Anchor::Center);
        m_grid.setLineWidth(coordinates.getRelativeSize({0.05f, 0.05f}).x / GameScene::WIDTH);
        m_grid.setColor(gf::Color::White);

        for (std::size_t x = 0; x < GameScene::WIDTH; ++x)
        {
            for (std::size_t y = 0; y < GameScene::LENGTH; ++y)
            {
                if (m_gamescene.getCell(x, y))
                {
                    gf::RectangleShape shape;

                    shape.setColor(gf::Color::Yellow);
                    shape.setSize({xSize, ySize});
                    shape.setPosition((m_grid.getPosition() - (gf::Vector2f(xSize / 2.f, ySize / 2.f)* gf::Vector2f(GameScene::WIDTH, GameScene::LENGTH))) + gf::Vector2f(xSize * x, ySize * y));

                    shape.draw(target, states);
                }
            }
        }

        m_grid.draw(target, states);

        gf::Text text;

        text.setFont(m_font);
        text.setString("Framerate : " + std::to_string(m_framerate));
        text.setPosition(coordinates.getRelativePoint({0.0f, 0.05f}));
        text.setCharacterSize(coordinates.getRelativeCharacterSize(0.05f));
        text.setColor(gf::Color::Red);

        text.draw(target, states);
    }
}