#pragma once
#include "raylib.h"
#include "Body.h"
#include "spring.h"
#include <vector>



using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;

class Scene;



class World
{
public:
	~World();

	void Initalize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);
	

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position,float mass, float size, const Color& color);
	void Step(float timeStep);
	void Draw(const Scene& scene);
	void DestroyAll();
	bodies_t& GetBodies(){ return m_bodies; }

	//springs

	Spring* CreateSpring(struct Body* bodyA, struct Body* bodyB, float restLength, float stiffness);

	inline static Vector2 gravity{ 0, -9.81f };
	inline static float gravitation = 0;
	inline static float springStiffnessMultiplier = 1;
	inline static bool simulate = true;


private:
	bodies_t m_bodies;
	springs_t m_springs;
};