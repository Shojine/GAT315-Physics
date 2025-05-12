#include "PolarScene.h"
#include "Polar.h"

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{

	m_camera->BeginMode();
	DrawGrid(10, 5, WHITE);
	int steps = 3000;
	float rate = 1.8f;
	float time = (float)GetTime() * rate;
	{
		steps = 2000;
		//Archimedian Spiral  r = a + b * theta
		Polar p;
		p.radius = 0.5f;
		p.angle = 0.5f;
		for (int i = 0; i < steps; i++)
		{
			float theta =  ((float)i / steps) * 6 * PI; // normalization 0 - 1
			float r = (p.radius + p.angle * theta);
			float x = cosf(theta) * r; //  //scale by the radius
			float y = sinf(theta) * r;
			DrawCircle(Vector2{ x,y }, 0.05, YELLOW);
		}
	}

	// Cardiod r = a( 1 + cos(theta))
	{
		Polar p;
		p.radius = 1.0f;
		p.angle = 2.0f;
		for (int i = 0; i < steps; i++)
		{
			float theta = ((float)i / steps) * 2 * PI; // normalization 0 - 1
			float r = p.angle * (1 + cos(theta));
			float x = cosf(theta) * r; //  //scale by the radius
			float y = sinf(theta) * r;
			DrawCircle(Vector2{ x,y }, 0.05, BLUE);
		}
	}


	// Limacon  r = a + b * cos(theta)
	{
		Polar p;
		p.radius = 2.0f;
		p.angle = 1.2f;
		for (int i = 0; i < steps; i++)
		{
			float theta = ((float)i / steps) * 2 * PI; // normalization 0 - 1
			float r = p.radius + p.angle * cos(theta);
			float x = cosf(theta) * r; //  //scale by the radius
			float y = sinf(theta) * r;
			DrawCircle(Vector2{x,y}, 0.05, ORANGE);
		}
	}

	
	// Rose Curve = r = a * cos(k * theta) or r = a * sin(k * theta)
	{
		Polar p;
		p.radius = 2.0f;
		p.angle = 2.0f;
		for (int i = 0; i < steps; i++)
		{
			float theta = ((float)i / steps) * 2 * PI; // normalization 0 - 1
			float k = 3; // number of petals if even divide it by 2 else do nothing
			if ((int)k % 2 == 0)
			{
				k /= 2;
			}
			float r = p.radius * cos(k * theta);
			float x = cosf(theta) * r; //  //scale by the radius
			float y = sinf(theta) * r;
			DrawCircle(Vector2{ x,y }, 0.05, GREEN);
		}
	}

	// user generated wavy spiral: r = (a + b * theta) * (1 + c * sin(d * theta))
	{
		steps = 4000;
		Polar p;
		p.radius = 0.5f;
		p.angle = 0.5f;
		float c = 0.3f; // amplitude of the wave
		float d = 5.0f; // frequency of the wave
		for (int i = 0; i < steps; i++)
		{
			float theta = ((float)i / steps) * 6 * PI;; // normalization 0 - 1
;
			float r = (p.radius + p.angle * theta) * (1 + c * sin(d * theta));
			float x = cosf(theta) * r; // scale by the radius
			float y = sinf(theta) * r;
			DrawCircle(Vector2{ x,y }, 0.05, MAGENTA);
		}
	}


	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
