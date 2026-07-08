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

    nu::Time time;

    Vector2 position{ 640.0f, 512.0f };
    float speed = 500.0f;

    std::vector<Vector2> points;

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
        time.Tick();

        if (input.GetButtonDown(Input::MouseButtons::Left))
        {
			points.push_back(input.GetMousePosition());
        }

        Vector2 velocity{ 0.0f, 0.0f };
		if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
		if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +speed;
		if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
		if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +speed;
        position += (velocity * time.GetDeltaTime());

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
		renderer.Clear();

        for (size_t i = 0; i < points.size(); i++)
        {
			renderer.SetColor(0.0f, 255.0f, 255.0f);
			renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // CHARACTER
        renderer.SetColor(0.0f, 255.0f, 255.0f);
		renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
        
	    renderer.Present();
    }

    // SHUTDOWN
	renderer.Shutdown();

    return 0;
}