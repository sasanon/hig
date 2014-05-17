#include "../Main.h"

// 効果の初期化
void CEffect::Reset() {
	switch (Type){
	case TE_STAR:	// 星拡散エフェクト
		Texture=GetTexture(L"Effect.png");
		Texture=GetTexture(L"starchip01.png");
		TextureScale = CVector(32/128.0f, 32/128.0f, 1.0f);
		TexturePosition = CVector(32*0/128.0f, 32*1/128.0f, 1.0f);
		Scale=CVector(1, 1, 1)*0.02f;
		Velocity.X = Random(-0.01f,  0.01f);
		Velocity.Y = Random(-0.01f,  0.01f);
		Velocity.Normalize();
		Velocity *= 0.03f;
		Position0 = Position;
		FadeAlpha = 0.0f;
		break;
	case TE_DASH:	// ダッシュ煙エフェクト
		Texture = GetTexture(L"Cloud.png");
		Scale    = CVector(1, 1, 1)*0.02f;
		Velocity = CVector(0.0f, 0.003f, 0);
		FadeAlpha = 0.4f;
		break;
	}

}

// 効果の移動
void CEffect::Move()
{
	switch (Type){
	case TE_STAR:	// 星拡散エフェクト
		Time++;
		Position += Velocity;
		Rotation *= RotationZ(0.02f);						// 素早く回す
		if (FadeAlpha > 0){
			// 拡散後、重力によって降下中のとき
			FadeAlpha -= 0.02f;			// 段々薄くする
			Color = CColor(1.0f, 1.0f, 1.0f, FadeAlpha);
			if (FadeAlpha <= 0){
				// 完全に透明になったら消去
				Life = 0;
			}
		}
		else
		if (Length(Position0 - Position) >= 0.2f){
			// 拡散中、一定距離まで広がった場合
			// 重力により降下開始、表示フェードアウト開始
			Velocity = CVector(0, -0.002f, 0);
			FadeAlpha = 1.0f;
		}
		break;

	case TE_DASH:	// ダッシュ時煙エフェクト
		Time++;
		Position += Velocity;

		// 煙を消す表現
		Rotation *= RotationZ(0.005f);						// ゆっくり回す
		Scale = CVector(1, 1, 1)*(0.02f + 0.002f * Time);	// ゆっくり大きく
		FadeAlpha -= 0.02f;			// 段々薄くする
		Color = CColor(1.0f, 1.0f, 1.0f, FadeAlpha);
		// 3秒で消去
		if (Time >= 30)	Life = 0;

		break;
	}

}