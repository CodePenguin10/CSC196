#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu;

int main()
{
    // INITILALIZATION
    Renderer renderer;
    renderer.Initialize("Game Engine", 1280, 1024);

    //std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{0.5f, 0.5f };

    std::vector<Vector2> v;

    // MAIN LOOP
    bool quit = false;

    while (!quit) 
    {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // RENDER

         // Set render draw color to black
        renderer.SetColor(0.0f, 0.0f, 0.0f);

        // Clear the renderer
		renderer.Clear();

		renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat()); // Set render to random color
		renderer.DrawFillRect(50,50,50,50); // Render the rectangle
		renderer.DrawLine(100, 100, 200, 200); // Render the line

		renderer.Present();
    }

    // SHUTDOWN
	renderer.Shutdown();

    return 0;
}