#include "trigonometry_scene.h"


void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ (float)m_width / 2,(float)m_height / 2 });
}

void TrigonometryScene::Update()
{
}


float DegToRad(float degrees)
{
	return degrees * (PI / 180);
}

float RadToDeg(float radians)
{
	return radians * (180 / PI);
}

float Vector2Length(const Vector2& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y)); // Pythagorean theorem "length"
}


//Vector2 VectorNormalize(const Vector2& v)
//{
//	float l = Vector2Length(l);
//	if (l == 0) return Vector2{ 0, 0 }; // avoid division by zero
//	return Vector2{ v.x / l, v.y / l }; // normalize the vector
//	
//}

float Vector2Angle(const Vector2& v)
{
	float angle = atan2f(v.y, v.x); // get the angle in radians
	angle = RadToDeg(angle); // convert to degrees
	if (angle < 0) angle += 360; // normalize to 0 - 360 degrees
	return angle;
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, WHITE) ;
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);



	//Circle 
	float radius = 3;
	float rate = 1.8f;
	float time = (float)GetTime() * rate;

	float radians = 180 * DEG2RAD;
	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = ((float)i / steps) * 2 * PI; // normalization 0 - 1
		float x = cosf(theta) * radius; //  //scale by the radius
		float y = sinf(theta) * radius;

		DrawCircle(Vector2{ x, y },0.25, BLUE);
	}
	// Sin / Cos 

	for (float x = -9; x < 9;  x += 0.2)
	{
		float theta = time + ((float)x / 18) * 2 * PI; // normalization 0 - 1	10 + 10 = 20
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;
		
		DrawCircle(Vector2{ x, c }, 0.25, GREEN);

		DrawCircle(Vector2{ x, s }, 0.25, YELLOW);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x, y}, 0.25, RED);




	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}

void TrigonometryScene::FixedUpdate()
{

}
