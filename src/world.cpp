#include "world.h"
#include "Body.h"

Vector2 World::gravity{ 0, -9.81f };

World::~World()
{
}

void World::Initalize(Vector2 gravity, size_t poolSize)
{
	m_gravity = gravity;
	m_bodies.reserve(poolSize);
	World::gravity = gravity;
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{

	Body* body = new Body(position, size, color);
	m_bodies.push_back(body);

    return body;
}

void World::Step(float timeStep)
{
	for (auto body : m_bodies)
	{
		body->Step(timeStep);
	}
}

void World::Draw(const Scene& scene)
{
	for (auto body : m_bodies)
	{
		body->Draw(scene);
	}
}

void World::DestroyAll()
{
	for (auto body : m_bodies)
	{
		delete body;
	}

	m_bodies.clear();
}



