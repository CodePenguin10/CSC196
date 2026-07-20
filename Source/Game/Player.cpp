#include "Player.h"
#include "Engine.h"
#include "Renderer.h"

using namespace nu;

void Player::Update(float dt)
{
	float thrust = 0.0f;

	if (engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 velocity{ 1, 0 };
	velocity = velocity.Rotate(m_transform.rotation * DegToRad) * thrust;
	AddVelocity(velocity * dt);

	//SetVelocity(GetVelocity() + (force * dt));

	Actor::Update(dt);
}

void Player::Draw(const Renderer& renderer)
{
	Actor::Draw(renderer);
}
