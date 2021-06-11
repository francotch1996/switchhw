
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "Bullet.h"

unsigned int	g_PlayerTexture;
Float2			g_PlayerPosition;
static bool isLife;

void InitPlayer()
{

	g_PlayerTexture = LoadTexture("rom:/plane.tga");
	isLife = true;
	g_PlayerPosition.x = 0.0f;
	g_PlayerPosition.y = 450.0f;
}



void UninitPlayer()
{

	UnloadTexture(g_PlayerTexture);

}


void UpdatePlayer()
{

	// �{�^��
	if (GetControllerPress(NpadButton::Left::Index))
		g_PlayerPosition.x += -20.0f;
	if (GetControllerPress(NpadButton::Right::Index))
		g_PlayerPosition.x += 20.0f;
	if (GetControllerPress(NpadButton::Up::Index))
		g_PlayerPosition.y += -20.0f;
	if (GetControllerPress(NpadButton::Down::Index))
		g_PlayerPosition.y += 20.0f;


	
	

	// �A�i���O�X�e�B�b�N
	Float2 stick;
	stick = GetControllerLeftStick();

	g_PlayerPosition.x += stick.x * 20.0f;
	g_PlayerPosition.y -= stick.y * 20.0f;



	// �^�b�`�X�N���[��
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		g_PlayerPosition = touch;
	}

	if (GetControllerTrigger(NpadButton::A::Index))
	{
		CreateBullet();
	}


	// �����x�Z���T�[
	/*if (GetControllerPress(NpadButton::A::Index))
	{
		Float3 acc;
		acc = GetControllerRightAcceleration();

		g_PlayerPosition.x += acc.x * 10.0f;
		g_PlayerPosition.y += -acc.y * 10.0f;
	}*/



	// �W���C���Z���T�[
	if (GetControllerPress(NpadButton::B::Index))
	{
		Float3 angle;
		angle = GetControllerRightAngle();

		g_PlayerPosition.x = angle.z * 1000.0f;
	}



	// �U��
	if (GetControllerPress(NpadButton::Y::Index))
	{
		SetControllerLeftVibration(5);
	}
	if (GetControllerPress(NpadButton::X::Index))
	{
		SetControllerRightVibration(5);
	}




	if (g_PlayerPosition.x < -500.0f + 128.0f)
		g_PlayerPosition.x = -500.0f + 128.0f;

	if (g_PlayerPosition.x > 500.0f - 128.0f)
		g_PlayerPosition.x = 500.0f - 128.0f;

	if (g_PlayerPosition.y < -500.0f + 100.0f)
		g_PlayerPosition.y = -500.0f + 100.0f;

	if (g_PlayerPosition.y > 500.0f - 100.0f)
		g_PlayerPosition.y = 500.0f - 100.0f;

}



void DrawPlayer()
{

	SetTexture(g_PlayerTexture);

	DrawSprite(g_PlayerPosition.x, g_PlayerPosition.y, 260.0f, 200.0f,
						0.0f, 0.0f, 1.0f, 1.0f,
						MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}

const Float2 GetPlayerPos() 
{
	return g_PlayerPosition;
}

bool GetIsLife() 
{
	return isLife;
}

void SetIsLife(bool b)
{
	isLife = b;
}