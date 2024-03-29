#include "../Main.h"

// 弾の初期化
void CBullet::Reset() {
	Texture=GetTexture(L"Bullet.png");
	Scale = CVector(1, 1, 1)*Random(0.02f, 0.04f);;
	Position.X = Random(-0.75f, 0.75f);
	Position.Y = 0.75f;
	MoveVec.X = Random(-0.01f,  0.01f);
	MoveVec.Y = Random(-0.02f, -0.005f);
}

// 弾の移動
void CBullet::Move() {
	Position.X += MoveVec.X;
	Position.Y += MoveVec.Y;
	BlockList.Apply([&](CMover* e) {
		if (Length(e->Position - Position)<0.1f) {
			Life = 0;
		}
	});
}

