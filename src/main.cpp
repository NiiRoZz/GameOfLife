#include <iostream>
#include <gf/Window.h>
#include <gf/Color.h>
#include <gf/RenderWindow.h>
#include <gf/Event.h>
#include <Pomme/VirtualMachine.h>

int main(int , char const **)
{
    gf::Window window("GameOfLife", { 640, 480 });
    gf::RenderWindow renderer(window);

    renderer.clear(gf::Color::Black);

    Pomme::VirtualMachine pommeVm;

    while (window.isOpen())
    {
        //update
        gf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case gf::EventType::Closed:
                {
                    window.close();
                    break;
                }
            }
        }

        renderer.clear();

        //render

        renderer.display();
    }

    return 0;
}
