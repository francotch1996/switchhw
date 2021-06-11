#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Bullet.h"
#include "player.h"
#include "Enermy.h"

#define MAX_ENERMY 10

unsigned int	g_enermyTexture;
ENERMY g_enermy[MAX_ENERMY];
static int generate_monster_timer;
void InitEnermy() 
{
	g_enermyTexture = LoadTexture("rom:/enermy.tga");

	for (int i = 0; i < MAX_ENERMY; i++)
	{
		g_enermy[i].pos = MakeFloat2(0.0f, 0.0f);
		g_enermy[i].vel = MakeFloat2(0.0f, -5.0f);
		g_enermy[i].isUse = false;
	}
	generate_monster_timer = 0;
	SetEnermy(MakeFloat2(0.0f, -300.0f), MakeFloat2(0.0f, 0.0f), 256.0f);


}

void UpdateEnermy() 
{
	CreateEnermy();
	CheckBulletEnermyCollision(); 
	CheckPlayerEnermyCollision();
	EnermyMoveMent();
	DeleteEnermy();
	generate_monster_timer++;
}

void DrawEnermy() 
{
	SetTexture(g_enermyTexture);
	for (int i = 0; i < MAX_ENERMY; i++)
	{
		if (g_enermy[i].isUse)
		{
			DrawSprite(g_enermy[i].pos.x, g_enermy[i].pos.y, 150.0f,150.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

void UninitEnermy() 
{
	UnloadTexture(g_enermyTexture);
}

ENERMY* GetEnermy() 
{
	return g_enermy;
}

void SetEnermy(Float2 pos,Float2 vel, float size)
{
	for (int i = 0; i < MAX_ENERMY; i++)
	{
		if (!g_enermy[i].isUse)
		{
			g_enermy[i].isUse = true;
			g_enermy[i].pos = pos;
			g_enermy[i].vel = vel;
			break;
		}
	}
}

void CheckBulletEnermyCollision()
{
	for (int i = 0; i < MAX_ENERMY; i++)
	{
		for (int j = 0; j < MAX_ENERMY; j++)
		{
			if (g_enermy[i].isUse &&  GetBullet()[j].isUse)
			{
				if (Collision_EnermyBullet_Box(g_enermy[i], GetBullet()[j]))
				{
					DestroyEnermy(i);
					DestroyBullet(j);
				}
			}
		}
	}
}

void CheckPlayerEnermyCollision() 
{
	for (int i = 0; i < MAX_ENERMY; i++)
	{
		if (g_enermy[i].isUse && GetIsLife()) 
		{
			if (Collision_EnermyPlayer_Box(g_enermy[i])) 
			{
				DestroyEnermy(i);
				SetIsLife(false);
			}
		}
	}
}

void CreateEnermy() 
{
	if (generate_monster_timer % 350 == 0) 
	{
		float x = -300 + rand() % 500;
		float y = -500.0f;
		SetEnermy(MakeFloat2(x, y), MakeFloat2(0.0f, 1.0f), 256);
	}
}

void EnermyMoveMent() 
{
	for (int i = 0; i < MAX_ENERMY; i++) 
	{
		if (g_enermy[i].isUse) 
		{
			g_enermy[i].pos.x += g_enermy[i].vel.x;
			g_enermy[i].pos.y += g_enermy[i].vel.y;
		}
	}
}

bool Collision_EnermyPlayer_Box(ENERMY enermy)
{
	if (enermy.pos.x < GetPlayerPos().x + 260.0f  &&
		GetPlayerPos().x < enermy.pos.x + 150.0f &&
		enermy.pos.y < GetPlayerPos().y + 200.0f &&
		GetPlayerPos().y < enermy.pos.y + 150.0f)
	{
		return true;
	}

	return false;
}

bool Collision_EnermyBullet_Box(ENERMY enermy, BULLET bullet)
{
	if (enermy.pos.x + 75.0f  > bullet.pos.x - 25.0f  &&
		bullet.pos.x + 25.0f > enermy.pos.x - 75.0f &&
		bullet.pos.y - 25.0f < enermy.pos.y + 75.0f)
	{
		return true;
	}

	return false;
}

void DestroyEnermy(int i)
{
	g_enermy[i].pos = MakeFloat2(0.0f, 0.0f);
	g_enermy[i].vel = MakeFloat2(0.0f, -5.0f);
	g_enermy[i].isUse = false;
}

void DeleteEnermy() 
{
	for (int i = 0; i < MAX_ENERMY; i++) 
	{
		if (g_enermy[i].pos.y > 500) 
		{
			DestroyEnermy(i);
		}
	}
}