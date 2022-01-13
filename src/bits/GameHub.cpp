#include "GameHub.h"

#include <Pomme/Compiler.h>

#include "config.h"

namespace gol
{
    GameHub::GameHub()
    : GameManager("Game Of Life", { GAME_DATADIR })
    , game(*this)
    {
        Pomme::Compiler compiler(vm);
        compiler.addStdLibrary();
        gf::Path path = resources.getAbsolutePath("game.pomme");
        if (path.empty())
        {
            std::exit(-1);
        }

        compiler.addFile(path);

        vm.interpret(compiler.compile());
        if (!vm.linkStdNative())
        {
            std::exit(-1);
        }

        pushScene(game);
    }
}