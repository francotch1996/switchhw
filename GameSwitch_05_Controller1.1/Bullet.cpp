#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Bullet.h"
#include "player.h"

#define MAX_BULLET 10

unsigned int	g_bulletTexture;
BULLET g_bullet[MAX_BULLET];

void InitBullet() 
{
	g_bulletTexture = LoadTexture("rom:/ball.tga");

	for (int i = 0; i < MAX_BULLET; i++)
	{
		g_bullet[i].pos = MakeFloat2(0.0f, 0.0f);
		g_bullet[i].vel = MakeFloat2(0.0f, -5.0f);
		g_bullet[i].isUse = false;
	}
}

void UpdateBullet() 
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].isUse)
		{
			g_bullet[i].pos.y += g_bullet[i].vel.y;

			if (g_bullet[i].pos.y <= -500+50) 
			{
				g_bullet[i].isUse = false;
			}
		}
	}
}

void DrawBullet() 
{
	SetTexture(g_bulletTexture);
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].isUse)
		{
			DrawSprite(g_bullet[i].pos.x, g_bullet[i].pos.y, 50.0f, 50.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

void UninitBullet() 
{
	UnloadTexture(g_bulletTexture);
}

BULLET* GetBullet() 
{
	return g_bullet;
}

void SetBullet(Float2 pos,Float2 vel, float size)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_bullet[i].isUse)
		{
			g_bullet[i].isUse = true;
			g_bullet[i].pos = pos;
			g_bullet[i].vel = vel;
			break;
		}
	}
}

void CreateBullet() 
{
	for (int i = 0; i < MAX_BULLET; i++) 
	{
		if (g_bullet[i].isUse == false) 
		{
			g_bullet[i].isUse = true;
			g_bullet[i].pos.x = GetPlayerPos().x;
			g_bullet[i].pos.y = GetPlayerPos().y - 20;
			break;
		}
	}
}

void DestroyBullet(int i)
{
	g_bullet[i].pos = MakeFloat2(0.0f, 0.0f);
	g_bullet[i].vel = MakeFloat2(0.0f, -5.0f);
	g_bullet[i].isUse = false;
}