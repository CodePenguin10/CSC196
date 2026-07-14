#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtility.h"

namespace nu
{
    void Actor::Update(float dt)
    {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer)
    {
        renderer.DrawModel(m_model, m_transform);
        //renderer.SetColor(m_model.GetColor().r, m_model.GetColor().g, m_model.GetColor().b);
        //renderer.SetColor(0.0f, 255.0f, 255.0f);
		//renderer.DrawPoint(m_transform.position.x, m_transform.position.y);
        //renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }
}