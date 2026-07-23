#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>

using namespace nu;

int main()
{
    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


    // INITILALIZATION
    Engine::Get().Initialize();

    // mesh / model
    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 25.0f };
    playerDesc.speed = 1000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);

   for (int i = 0; i < 20; i++) 
    {
       EnemyDesc enemyDesc;
       enemyDesc.name = "Enemy";
       enemyDesc.model = assets::enemyModel;
       enemyDesc.transform = Transform{ Vector2{ RandomFloat(0.0f, 1280.0f), RandomFloat(0.0f, 1024.0f)}, 0.0f, 25.0f };
       enemyDesc.speed = 1000.0f;

       Enemy* enemy = new Enemy{ enemyDesc };
       scene.AddActor(enemy);
    }


    std::vector<Vector2> points;

    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);

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
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();
        audio->update();

        //player.SetRotation(player.GetTransform().rotation + (90.0f * Engine::Get().GetTime().GetDeltaTime()));
        //player.Update(dt);
        //enemy.Update(dt);

        scene.Update(dt);

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButtons::Left))
        {
            if (points.empty()) 
            {
				points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else
            { 
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
            
        }

        //Undo
        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButtons::Right))
        {
            if (points.empty()) {
                points.pop_back();
            }
		}
		

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
		Engine::Get().GetRenderer().Clear();

        for (size_t i = 0; i + 1 < points.size(); i++)
        {
			Engine::Get().GetRenderer().SetColor(0.0f, 255.0f, 255.0f);
			Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // CHARACTER
        //player.Draw(Engine::Get().GetRenderer());
        //enemy.Draw(Engine::Get().GetRenderer());
        scene.Draw(Engine::Get().GetRenderer());
        
	    Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}