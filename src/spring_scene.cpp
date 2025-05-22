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
		if (m_selected)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else
			{
				if (m_selected && m_connected)
				{
					float distance = Vector2Distance(m_selected->position, m_connected->position);
					m_world->CreateSpring(m_selected, m_connected, distance, 20);
				}
				m_selected = nullptr;
				m_connected = nullptr;
			}
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
		if (m_connected)
		{
			DrawCircleLine(m_connected->position, m_connected->size, WHITE, 10);
			DrawLine(m_selected->position, m_connected->position, 3, GREEN);
		}
		else
		{
			DrawLine(m_selected->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
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
