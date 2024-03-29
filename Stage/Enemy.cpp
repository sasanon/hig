#include "../Main.h"

// 敵の初期化
void CEnemy::Reset() {
	Texture=GetTexture(L"Enemy.png");
	Scale = CVector(1, 1, 1)*0.05f;
	Velocity = CVector(-0.005f,0,0);
}

// 敵の移動
void CEnemy::Move() {
	Position += Velocity;
#if 0
	CVector v = Velocity;
	CHitRectangle hit;
	Apply(BlockList, hit);
	if(hit.Right || hit.Left)	Velocity = v*(-1);
	else						Velocity = v;
#endif
}


