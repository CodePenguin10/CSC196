#pragma once
#include "Actor.h"

class Player : public nu::Actor
{
public:
        Player() = default;
        Player(const nu::Transform& transform) : Actor{ transform } {}
        Player(const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model } {}

        void Update(float dt) override;
        void Draw(const class nu::Renderer& renderer) override;

private:
    int ammo = 0;
    float m_speed = 1000.0f;
};