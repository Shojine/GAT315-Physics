#include "Body.h"
#include "raymath.h"

void Body::Step(float dt)
{
	//Update position by velocity
	position += velocity * dt;
	velocity *= 1.0f / (1.0f + (damping * dt)); // Damping
	velocity += World::gravity * dt; // Gravity
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}
