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

    nu::Mesh mesh{ { Vector2{-3, 3}, Vector2{3,3}, Vector2{0,0} }, Color{ 0.0f, 255.0f, 255.0f} };


    Actor player{ Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh>{mesh} };

    Vector2 position{ 640.0f, 512.0f };
	Vector2 velocity{ 0.0f, 0.0f };
    float speed = 1000.0f;

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
            if (points.empty()) 
            {
				points.push_back(input.GetMousePosition()); 
            }
            else
            { 
                Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(input.GetMousePosition());
                }
            }
            
        }

        //Undo
        if (input.GetButtonPressed(Input::MouseButtons::Right))
        {
            if (points.empty()) {
                points.pop_back();
            }
		}

        Vector2 force{ 0.0f, 0.0f };
		if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
		if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
		if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
		if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));

        player.Update(time.GetDeltaTime());

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
		renderer.Clear();

        for (size_t i = 0; i + 1 < points.size(); i++)
        {
			renderer.SetColor(0.0f, 255.0f, 255.0f);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // CHARACTER
        player.Draw(renderer);
        
	    renderer.Present();
    }

    // SHUTDOWN
	renderer.Shutdown();

    return 0;
}