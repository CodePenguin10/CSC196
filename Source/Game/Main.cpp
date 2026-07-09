#include "Engine.h"


#include <iostream>
#include <vector>

using namespace nu;

struct Transform
{
    Vector2 position;
    float rotation;
    float scale;
};


class Actor
{
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{ transform } {}

    void Update(float dt)
    {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer)
    {
        renderer.SetColor(0.0f, 255.0f, 255.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

	const Transform& GetTransform() const { return m_transform; }
    void SetPosition(const Vector2& position) { m_transform.position = position; }
	void SetRotation(float rotation) { m_transform.rotation = rotation; }
	void SetScale(float scale) { m_transform.scale = scale; }

	const Vector2& GetVelocity() const { return m_velocity; }
	void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
	Vector2 m_velocity{ 0.0f, 0.0f };
};

int main()
{
    // INITILALIZATION
    Renderer renderer;
    renderer.Initialize("Game Engine", 1280, 1024);

    nu::Input input;

    input.Initialize();

    nu::Time time;

    Actor player{ Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 50.0f } };

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

        for (size_t i = 1; i < points.size(); i++)
        {
			renderer.SetColor(0.0f, 255.0f, 255.0f);
			renderer.DrawLine(points[i].x, points[i].y, points[i - 1].x, points[i - 1].y);
        }

        // CHARACTER
        player.Draw(renderer);
        
	    renderer.Present();
    }

    // SHUTDOWN
	renderer.Shutdown();

    return 0;
}