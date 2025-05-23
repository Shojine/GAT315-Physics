#include "vector_scene.h"
#include "gui.h"
#include "raymath.h"
#include "mathUttils.h"
#include "raygui.h"
#include "world.h"
#include <iostream>
#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
	m_world = new World();
	m_world->Initalize();

}

void VectorScene::Update()
{

	float dt = GetFrameTime();
	GUI::Update();

	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0))
	{
		Body::Type type = (Body::Type)GUI::bodyTypeActive;
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float theta = randomf(0, 360);
			float x = cos(theta);
			float y = sin(theta);
				
			body->mass = GUI::massValue;
			std::cout << "mass: " << body->size << std::endl;

			body->size = GUI::sizeValue;
			body->velocity = Vector2{ x, y };// *randomf(1, 6);
			body->restitution = randomf(0.5f, 1.0f);
		}
	}
	
	//Apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -1;
		}
		if(body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution; // restitution
		}
	}
	
}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	GUI::Draw();
}


void VectorScene::FixedUpdate()
{
	
	//apply forces
	m_world->Step(Scene::fixedTimeStep);
	//apply gravitation
}
