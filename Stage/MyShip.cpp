#include "../Main.h"


// 自機の初期化
void CMyShip::Reset() {
	// モーションデータ初期化
	motid  = M_WAIT_R;		frameid = 0;	// 右向き待機モーション0フレーム目に設定
	// 各モーションのコマ数を設定
	framemax[M_WAIT_R]     = 3;
	framemax[M_WALK_R]     = 6;
	framemax[M_JUMPUP_R]   = 4;
	framemax[M_JUMPDOWN_R] = 5;
	framemax[M_WAIT_L]     = 3;
	framemax[M_WALK_L]     = 6;
	framemax[M_JUMPUP_L]   = 4;
	framemax[M_JUMPDOWN_L] = 5;
	framemax[8] = 4;
	framemax[9] = 5;
	// テクスチャ初期化
	Texture=GetTexture(L"chara.png");								// テクスチャファイル
	TextureScale    = CVector(48.0f/512.0f,  48.0f/512.0f, 1.0f);	// テクスチャ座標の取込範囲
	TexturePosition = CVector(48.0f*frameid, 48.0f*motid, 1.0f);	// テクスチャ座標の取込位置(左上ピポッド)

	Velocity.X= 0.0f;	// 移動量0
	Scale=CVector(1, 1, 1)*0.07f;
}

// 自機の移動
void CMyShip::Move() {
	static float jump = 0.0f;

	// 時間でアニメーションさせる
	Time++;

	// 入力更新
	Velocity.X = 0.0f;
	if (KeyState[0][DIK_RIGHT])	Velocity.X += 0.015f;	// 右押下中
	if (KeyState[0][DIK_LEFT])	Velocity.X -= 0.015f;	// 左押下中

	// アニメパターンの更新
	if (Velocity.X > 0){
		motid = M_WALK_R;		// 右・歩行モーションへ切替
	}
	if (Velocity.X < 0){
		motid = M_WALK_L;		// 右・歩行モーションへ切替
	}
	if (Velocity.X == 0){
		if (motid == M_WALK_R)	motid = M_WAIT_R;		// 右・待機モーションへ切替
		if (motid == M_WALK_L)	motid = M_WAIT_L;		// 左・待機モーションへ切替
	}

	// uvアニメ更新
	if (Time >= 6){
		Time -= 6;
		frameid = (frameid + 1) % framemax[motid];
		TexturePosition = CVector(48 * frameid / 512.0f, 48 * motid / 512.0f, 1.0f);
	}


	// 重力設定
	Velocity.Y-=0.002f;

	// 移動量の適用
	Position+=Velocity;

	// ジャンプ
	if (/*hit.Down &&*/ OldKeyState[0][DIK_Z] && KeyState[0][DIK_Z]) Velocity.Y = 0.04f;

	// ダッシュ
	if (KeyState[0][DIK_X]){
		Position.X += Velocity.X;
		if (Time % 10 == 0 && Velocity.X != 0.0f && hit.Down)
			New<CEffect>(Position.X, Position.Y - 0.03f, 0, 0, 0, TE_DASH);
	}

	// 鍵をつかむ
	if (OldKeyState[0][DIK_X] && KeyState[0][DIK_X]){
		BlockList.Apply([&](CMover* b) {
			if (TB_KEY_STAR   <= b->Type / 100   &&			// 鍵ブロック範囲のはじめから
				b->Type / 100 <= TB_KEY_HEXAGRAM &&			// 鍵ブロック範囲のおわりまでの間の種別
				Length(b->Position - Position) < 0.13f){	// 対象ブロックと接触状態
				b->Type = b->Type - b->Type % 100 + MB_ABOVE_PLAYER;
				// モーションを鍵もち待機状態へ遷移 ★★★
			}
		});
	}

	// ブロックとの衝突処理
	CHitRectangle hit;
	Apply(BlockList, hit);

	// 得点アイテムの取得
	ItemList.Apply([&](CMover* e) {
		if (Length(e->Position - Position)<0.05f) {
			// 拡散する星エフェクトを20表示
			for (int i = 0; i<20; i++)	New<CEffect>(e->Position.X, e->Position.Y, 0, 0, 0, TE_STAR);
			// アイテム自体は消す
			e->Life = 0;
			Score += 10;
		}
	});

	// 敵との衝突処理
	EnemyList.Apply([&](CMover* e) {
		if (Length(e->Position-Position)<0.05f) {
			// 拡散する星エフェクトを20表示
			for (int i = 0; i<20; i++)	New<CEffect>(Position.X, Position.Y, 0, 0, 0, TE_STAR);
			Life = 0;
		}
	});
	// カメラの位置追従
	if (Life){
		CameraList.Apply([&](CMover* m) {
			if (m->Type == 0)
			m->Position = Position + CVector(0, 0, -10);
		});
	}
}

