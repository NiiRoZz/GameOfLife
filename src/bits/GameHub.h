#pragma once

#include <gf/GameManager.h>
#include <Pomme/VirtualMachine.h>

#include "GameScene.h"

namespace gol
{
    struct GameHub: gf::GameManager
    {
        GameHub();

        GameScene game;

        Pomme::VirtualMachine vm;
    };
}