#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct 
{
	Float2 pos;
	Float2 vel;
	float size;
	bool isUse;
}BULLET;

void InitBullet();
void UpdateBullet();
void DrawBullet();
void UninitBullet();
void CreateBullet();
BULLET* GetBullet();
void SetBullet(Float2 pos, Float2 vel, float size);
void DestroyBullet(int i);
#endif
