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

	if (World::reset)
	{
		m_world->DestroyAll();
		World::reset = false;
	}


	if (!GUI::mouseOverGUI)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL))
		{
			Body::Type type = (Body::Type)GUI::bodyTypeActive;
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			body->mass = GUI::massValue;
			std::cout << "mass: " << body->size << std::endl;

			body->size = GUI::sizeValue;
			body->restitution = randomf(0.5f, 1.0f);
			body->damping = GUI::dampingValue;

			body->ApplyForce(randomOnUnitCircle() * 10, Body::ForceMode::Velocity);
		}

		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selected)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
			{

				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				//Spring::ApplyForce(position, *m_selected, 0.2f, 15.0f);

				//m_connected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else
			{
				if (m_selected && m_connected)
				{
					float distance = Vector2Distance(m_selected->position, m_connected->position);
					m_world->CreateSpring(m_selected, m_connected, distance, GUI::stiffnessValue, GUI::dampingValue);
				}
				m_selected = nullptr;
				m_connected = nullptr;
			}
		}


	}

	//Apply collision
	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x);  // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);  // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
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
