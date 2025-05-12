#pragma once
#include <vector>
#include "raylib.h"


struct Body;
class Scene;



class World
{
public:
	~World();

	void Initalize(Vector2 gravity = Vector2{ 0, -9.81 }, size_t poolSize = 30);
	

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timeStep);
	void Draw(const Scene& scene);
	void DestroyAll();

	static Vector2 gravity;

private:
	Vector2 m_gravity{ 0, 0 };
	std::vector<Body*> m_bodies;
};