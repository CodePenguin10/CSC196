#include "../Engine/Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    // Handles events
    SDL_Event e;
    bool quit = false;

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

         // Set render draw color to black
        renderer.SetColor(0, 0, 0);

        // Clear the renderer
		renderer.Clear();

		renderer.SetColor(0, 255, 255); // Set render draw color to cyan
		renderer.DrawFillRect(50,50,50,50); // Render the rectangle
		renderer.DrawLine(100, 100, 200, 200); // Render the line

		renderer.Present();
    }

	renderer.Shutdown();

    return 0;

	//fnEngine();
}