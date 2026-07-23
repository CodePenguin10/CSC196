#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Engine.h"
#include "Renderer.h"

using namespace nu;

void Player::Update(float dt)
{
	float thrust = 0.0f;

	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 velocity{ 1, 0 };
	velocity = velocity.Rotate(m_transform.rotation * DegToRad) * thrust;
	AddVelocity(velocity * dt);

	//SetVelocity(GetVelocity() + (force * dt));

	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	{
		BulletDesc Desc;
		Desc.name = "Enemy";
		Desc.tag = "Bullet";
		Desc.model = assets::bulletModel;
		Desc.transform = m_transform;
		Desc.speed = 1500.0f;
		Desc.lifespan = 1.5f;

		Bullet* bullet = new Bullet{ Desc };
		m_scene->AddActor(bullet);
	}

	Actor::Update(dt);
}
