#include "spring_scene.h"
#include "gui.h"
#include "raymath.h"
#include "mathUttils.h"
#include "raygui.h"
#include "world.h"
#include <iostream>
#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
	m_world = new World();
	m_world->Initalize();

}

void SpringScene::Update()
{

	float dt = GetFrameTime();
	GUI::Update();

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;

	if (!GUI::mouseOverGUI)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			Body::Type type = (Body::Type)GUI::bodyTypeActive;
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			body->mass = GUI::massValue;
			std::cout << "mass: " << body->size << std::endl;

			body->size = GUI::sizeValue;
			body->restitution = randomf(0.5f, 1.0f);
		}

		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			
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

void SpringScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	if (m_selected)
	{
		DrawCircleLine(m_selected->position, m_selected->size, WHITE, 10);
	}


	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}


void SpringScene::FixedUpdate()
{
	
	//apply forces
	m_world->Step(Scene::fixedTimeStep);
	//apply gravitation
}
