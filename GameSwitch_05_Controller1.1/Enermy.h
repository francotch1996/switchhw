#ifndef _ENERMY_H_
#define _ENERMY_H_

typedef struct
{
	Float2 pos;
	Float2 vel;
	float size;
	bool isUse;
}ENERMY;

void InitEnermy();
void UpdateEnermy();
void DrawEnermy();
void UninitEnermy();
void CreateEnermy();
ENERMY* GetEnermy();
void EnermyMoveMent();
void SetEnermy(Float2 pos, Float2 vel, float size);
void CheckBulletEnermyCollision();
bool Collision_EnermyBullet_Box(ENERMY enermy, BULLET bullet);
void CheckPlayerEnermyCollision();
bool Collision_EnermyPlayer_Box(ENERMY enermy);
void DestroyEnermy(int i);
void DeleteEnermy();
#endif
