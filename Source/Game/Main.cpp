#include "Engine.h"


#include <iostream>
#include <vector>

using namespace nu;

int main()
{
    // INITILALIZATION
    Renderer renderer;
    renderer.Initialize("Game Engine", 1280, 1024);

    nu::Input input;

    input.Initialize();

    //std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{0.5f, 0.5f };

    std::vector<Vector2> v;

    Vector2 mousePosition{ 0, 0 };

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
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
			}
        }

        // ENGINE
        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
		renderer.Clear();

        renderer.SetColor(0.0f, 255.0f, 255.0f);
		renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        // Lines
        for (int i = 0; i < 10; i++)
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawLine(RandomFloat(1280), RandomFloat(1040), RandomFloat(1280), RandomFloat(1040));
        }
        
        // Points
        for (int i = 0; i < 20; i++)
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        	renderer.DrawPoint(RandomFloat(1280), RandomFloat(1040));
}       
        
        //Squares (Unfilled)
        for (int i = 0; i < 10; i++) 
        {
        	renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        	renderer.DrawRect(RandomFloat(1280), RandomFloat(1040), (float)RandomInt(), (float)RandomInt());
        }
        
	    renderer.Present();
    }

    // SHUTDOWN
	renderer.Shutdown();

    return 0;
}