#include "../Main.h"

// �A�C�e���̏�����
void CItem::Reset() {
	Texture = GetTexture(L"starchip01.png");
	TextureScale = CVector(32 / 128.0f, 32 / 128.0f, 1.0f);
	TexturePosition = CVector(32 * 3 / 128.0f, 32 * 2 / 128.0f, 1.0f);
	Scale = CVector(1, 1, 1)*0.05f;

}

// �A�C�e���̈ړ�
void CItem::Move() {
	Rotation *= RotationZ(0.01f);

}


