#include "../Main.h"

// ’e‚Ì‰Šú‰»
void CBullet::Reset() {
	Texture=GetTexture(L"Bullet.png");
	Scale = CVector(1, 1, 1)*Random(0.02f, 0.04f);;
	Position.X = Random(-0.75f, 0.75f);
	Position.Y = 0.75f;
	MoveVec.X = Random(-0.01f,  0.01f);
	MoveVec.Y = Random(-0.02f, -0.005f);
}

// ’e‚ÌˆÚ“®
void CBullet::Move() {
	Position.X += MoveVec.X;
	Position.Y += MoveVec.Y;
	BlockList.Apply([&](CMover* e) {
		if (Length(e->Position - Position)<0.1f) {
			Life = 0;
		}
	});
}

