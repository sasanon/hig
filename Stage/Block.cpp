#include "../Main.h"
#define _USE_MATH_DEFINES
#include <math.h>

// ブロックの初期化
void CBlock::Reset() {
	// 見た目に関する初期化
	switch (Type / 100){
	case TB_NORMAL:     Texture = GetTexture(L"Block.png");     Scale = CVector(1, 1, 1)*0.05f;     break;
	case TB_CLOUD:      Texture = GetTexture(L"Cloud.png");     Scale = CVector(1, 1, 1)*0.10f;     break;
	case TB_KEY_HEART:  Texture = GetTexture(L"key-door.png");  Scale = CVector(1, 1, 1)*0.05f;     TextureScale = CVector(31 / 256.0f, 31 / 64.0f, 1.0f);  TexturePosition = CVector(32 * 0 / 256.0f, 32 * 0 / 64.0f, 1.0f);   break;
	case TB_KEY_CIRCLE: Texture = GetTexture(L"key-door.png");  Scale = CVector(1, 1, 1)*0.05f;     TextureScale = CVector(31 / 256.0f, 31 / 64.0f, 1.0f);  TexturePosition = CVector(32 * 1 / 256.0f, 32 * 0 / 64.0f, 1.0f);   break;
	case TB_KEY_STAR:   Texture = GetTexture(L"key-door.png");  Scale = CVector(1, 1, 1)*0.05f;     TextureScale = CVector(31 / 256.0f, 31 / 64.0f, 1.0f);  TexturePosition = CVector(32 * 2 / 256.0f, 32 * 0 / 64.0f, 1.0f);   break;
	case TB_ITEM:       Texture = GetTexture(L"Cloud.png");     Scale = CVector(1, 1, 1)*0.10f;     break;
	default:    break;
	}

	// 動作に関する初期化
	switch (Type % 100){
	case MB_CIRCLE:     MoveCenter = Position;     Velocity = CVector(0, 1, 0);     break;
	case MB_PENDULUM:   MoveCenter = Position;     Velocity = CVector(0, 1, 0);     break;
	case MB_X:          MoveCenter = Position;     Velocity = CVector(1, 0, 0);     break;
	case MB_XSIN:       MoveCenter = Position;     Velocity = CVector(1, 0, 0);     break;
	case MB_Y:          MoveCenter = Position;     Velocity = CVector(0, 1, 0);     break;
	case MB_YSIN:       MoveCenter = Position;     Velocity = CVector(0, 1, 0);     break;
	}
}

// ブロックの移動
void CBlock::Move() {
	Time++;
	// アニメーションの更新	
	if (Type/100 == TB_CLOUD){
		// 表示が雲ブロックの場合、わずかに拡縮し続ける
		if (Time >= 20)	Time -= 20;
		Scale = CVector(1, 1, 1)*0.07f + sin((Time / 300.0f) / M_PI)*0.03f;
	}
	
	switch (Type % 100){
		case MB_CIRCLE:	// 等速円運動
			// ブロックの移動ベクトルを回転
			Velocity *= RotationZ(60.0f * D3DX_PI * 2);
			// 上に乗っているものも一緒に移動
			MyShipList.Apply([&](CMyMover* e) {
				if (Length(e->Position - Position)<0.155f) {
					e->PosNext.X += Velocity.X * 0.01f;
				}
			});
			// ブロックを移動
			PosNext += Velocity * 0.01f;
			break;

		case MB_XSIN:
			Velocity = cos(Time/20.0f) * D3DX_PI / 2 /50;
			// 上に乗っているものも一緒に移動
			MyShipList.Apply([&](CMover* e) {
				if (Length(e->Position - Position)<0.155f) {
					e->PosNext.X += Velocity.X;
				}
			});
			PosNext.X += Velocity.X;
			break;

		case MB_YSIN:
			Velocity = cos(Time / 20.0f) * D3DX_PI / 2 / 50;
			// 上に乗っているものも一緒に移動
			MyShipList.Apply([&](CMover* e) {
				if (Length(e->Position - Position)<0.155f) {
					e->Position.Y += Velocity.Y;
				}
			});
			Position.Y += Velocity.Y;
			break;
		case MB_PENDULUM:
			break;
		case MB_ABOVE_PLAYER:
			// 敵に当たったら死亡
			MyShipList.Apply([&](CMover* p) {
				Position = p->Position + CVector(0.0f, 0.12f, 0.0f);
			});
			break;
	}

	// ブロックと敵の衝突 /////////////////////////////////////////////
	EnemyList.Apply([&](CMover* e) {
		if (Length(e->Position - Position)<0.155f) {
			e->Velocity = e->Velocity*(-1);
		}
	});
}

