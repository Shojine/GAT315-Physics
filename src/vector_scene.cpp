#include "vector_scene.h"
#include "Body.h"
#include "raymath.h"
#include "mathUttils.h"


void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
	m_world = new World();
	m_world->Initalize();


	/*Body* body = new Body(Vector2{ 3,0 }, Vector2{ 0 }, 0.25, WHITE);
	m_head = body;
	m_player = body;

	for (int i = 0; i < 40; i++)
	{
		Body* newbody = new Body(Vector2{ randomf() * 5,randomf() * 5 }, Vector2{0}, 0.25, RED);
		body->next = newbody;	
		body = body->next;
	}*/

}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	if (IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float theta = randomf(0, 360);
			float x = cos(theta);
			float y = sin(theta);

			body->velocity = Vector2{ x, y} * randomf(1,6);
		}
	}
	m_world->Step(dt);


	/*float dt = GetFrameTime();
	Vector2 input = { 0,0 };
	if (IsKeyDown(KEY_W)) input.y += 1;
	if (IsKeyDown(KEY_S)) input.y -= 1;
	if (IsKeyDown(KEY_A)) input.x -= 1;
	if (IsKeyDown(KEY_D)) input.x += 1;
	input = Vector2Normalize(input);
	m_player->velocity = input * 3;

	Body* body = m_head;
	while (body)
	{
		if (body == m_player)
		{
			body->Step(dt);
			body = body->next;
			continue;
		}
		Vector2 direction = m_player->position - body->position;
		direction = Vector2Normalize(direction);
		body->velocity = direction * 1;

		body->Step(dt);
		body = body->next;
	}*/
}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
	/*m_camera->BeginMode();
	DrawGrid(10, 5, DARKGRAY);

	Body* body = m_head;
	while (body)
	{
		body->Draw(*this);
		body = body->next;
	}

	m_camera->EndMode();*/
}

void VectorScene::DrawGUI()
{
}
