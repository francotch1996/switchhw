
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "player.h"
#include "Bullet.h"
#include "Enermy.h"
#include "UI.h"

void Init();
void Uninit();
void Update();
void Draw();


extern "C" void nnMain()
{
	Init();

    while( true )
	{
		Update();
		Draw();
	}

	Uninit();
}


void Init()
{
	InitSystem();

	// 後ろ向きを描画しない（通常設定）
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// 頂点が反時計回りならば前（通常設定）
	glFrontFace(GL_CCW);

	InitController();

	InitBG();
	InitPlayer();
	InitBullet();
	InitEnermy();
	InitUI();
}


void Uninit()
{
	UninitBG();
	UninitPlayer();
	UninitBullet();
	UninitEnermy();
	UninitUI();
	UninitController();
	UninitSystem();
}


void Update()
{
	UpdateController();

	UpdateBG();
	if (GetIsLife()) 
	{
		UpdatePlayer();
	}
	UpdateBullet();
	UpdateEnermy();
	UpdateUI();
}


void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawBG();
	if (GetIsLife()) 
	{
		DrawPlayer();
	}
	DrawBullet();
	DrawEnermy();
	DrawUI();
	SwapBuffers();
}