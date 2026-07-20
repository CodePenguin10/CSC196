#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtility.h"
#include "Transform.h"
#include "Actor.h"
#include "Mesh.h"
#include "Model.h"

//Systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Scene.h"

namespace nu
{
	class Engine
	{
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

	private:
		Input m_input;
		Renderer m_renderer;

		Time m_time;
	};

	extern Engine engine;
}