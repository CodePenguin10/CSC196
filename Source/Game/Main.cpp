#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>

using namespace nu;

int main()
{
    // INITILALIZATION
    
    engine.Initialize();

    Mesh mesh{ { { 2, 0 }, { 1, -1 }, { -2, -1 }, { -2, 1 }, { 1, 1 }, { 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f} };
    Mesh mesh2{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 1.0f, 0.0f, 0.0f} };
    Mesh mesh3{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 1.0f, 0.0f, 0.0f} };
    Model model{ std::vector<Mesh>{ mesh, mesh2, mesh3 } };
    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 25.0f };
    playerDesc.speed = 1000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);

   for (int i = 0; i < 20; i++) 
    {
       EnemyDesc enemyDesc;
       enemyDesc.name = "Enemy";
       enemyDesc.model = model;
       enemyDesc.transform = Transform{ Vector2{ RandomFloat(0.0f, 1280.0f), RandomFloat(0.0f, 1024.0f)}, 0.0f, 25.0f };
       enemyDesc.speed = 1000.0f;

       Enemy* enemy = new Enemy{ enemyDesc };
       scene.AddActor(enemy);
    }


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
        float dt = engine.GetTime().GetDeltaTime();

        //player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));
        //player.Update(dt);
        //enemy.Update(dt);

        scene.Update(dt);

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
        //player.Draw(engine.GetRenderer());
        //enemy.Draw(engine.GetRenderer());
        scene.Draw(engine.GetRenderer());
        
	    engine.GetRenderer().Present();
    }

    // SHUTDOWN
    engine.Shutdown();

    return 0;
}