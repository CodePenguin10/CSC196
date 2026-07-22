#include "Assets.h"

using namespace nu;

namespace assets
{
    Mesh playerMesh{ { { 2, 0 }, { 1, -1 }, { -2, -1 }, { -2, 1 }, { 1, 1 }, { 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f} };
    Mesh playerMesh2{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 1.0f, 0.0f, 0.0f} };
    Mesh playerMesh3{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 1.0f, 0.0f, 0.0f} };

    Model playerModel{ std::vector<Mesh>{ playerMesh, playerMesh2, playerMesh3 } };

    Mesh enemyMesh{ { { 2, 0 }, { 1, -1 }, { -2, -1 }, { -2, 1 }, { 1, 1 }, { 2, 0 } }, Color{ 1.0f, 1.0f, 1.0f} };
    Mesh enemyMesh2{ { { -1, -1 }, { -2, -2 }, { -2, -1 } }, Color { 1.0f, 0.0f, 0.0f} };
    Mesh enemyMesh3{ { { -1, 1 }, { -2, 2 }, { -2, 1 }, }, Color { 1.0f, 0.0f, 0.0f} };

    Model enemyModel{ std::vector<Mesh>{ playerMesh, playerMesh2, playerMesh3 } };
}