#include "trigonometry_scene.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();
	DrawCircle(0, 0, 50, RED);
	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
