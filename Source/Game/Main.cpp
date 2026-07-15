#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>

using namespace nu;

int main()
{
    // INITILALIZATION
    
    engine.Initialize();

    nu::Mesh mesh{ { Vector2{-3, 3}, Vector2{3,3}, Vector2{0,0} }, Color{ 0.0f, 255.0f, 255.0f} };

    Player player{ Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh>{mesh} };

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
        engine.Update();

        player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));

        player.Update(engine.GetTime().GetDeltaTime());

        if (engine.GetInput().GetButtonDown(Input::MouseButtons::Left))
        {
            if (points.empty()) 
            {
				points.push_back(engine.GetInput().GetMousePosition());
            }
            else
            { 
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
            
        }

        //Undo
        if (engine.GetInput().GetButtonPressed(Input::MouseButtons::Right))
        {
            if (points.empty()) {
                points.pop_back();
            }
		}
		

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
		engine.GetRenderer().Clear();

        for (size_t i = 0; i + 1 < points.size(); i++)
        {
			engine.GetRenderer().SetColor(0.0f, 255.0f, 255.0f);
			engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // CHARACTER
        player.Draw(engine.GetRenderer());
        
	    engine.GetRenderer().Present();
    }

    // SHUTDOWN
    engine.Shutdown();

    return 0;
}