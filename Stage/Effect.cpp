#include "../Main.h"

// ���ʂ̏�����
void CEffect::Reset() {
	switch (Type){
	case TE_STAR:	// ���g�U�G�t�F�N�g
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
	case TE_DASH:	// �_�b�V�����G�t�F�N�g
		Texture = GetTexture(L"Cloud.png");
		Scale    = CVector(1, 1, 1)*0.02f;
		Velocity = CVector(0.0f, 0.003f, 0);
		FadeAlpha = 0.4f;
		break;
	}

}

// ���ʂ̈ړ�
void CEffect::Move()
{
	switch (Type){
	case TE_STAR:	// ���g�U�G�t�F�N�g
		Time++;
		Position += Velocity;
		Rotation *= RotationZ(0.02f);						// �f������
		if (FadeAlpha > 0){
			// �g�U��A�d�͂ɂ���č~�����̂Ƃ�
			FadeAlpha -= 0.02f;			// �i�X��������
			Color = CColor(1.0f, 1.0f, 1.0f, FadeAlpha);
			if (FadeAlpha <= 0){
				// ���S�ɓ����ɂȂ��������
				Life = 0;
			}
		}
		else
		if (Length(Position0 - Position) >= 0.2f){
			// �g�U���A��苗���܂ōL�������ꍇ
			// �d�͂ɂ��~���J�n�A�\���t�F�[�h�A�E�g�J�n
			Velocity = CVector(0, -0.002f, 0);
			FadeAlpha = 1.0f;
		}
		break;

	case TE_DASH:	// �_�b�V�������G�t�F�N�g
		Time++;
		Position += Velocity;

		// ���������\��
		Rotation *= RotationZ(0.005f);						// ��������
		Scale = CVector(1, 1, 1)*(0.02f + 0.002f * Time);	// �������傫��
		FadeAlpha -= 0.02f;			// �i�X��������
		Color = CColor(1.0f, 1.0f, 1.0f, FadeAlpha);
		// 3�b�ŏ���
		if (Time >= 30)	Life = 0;

		break;
	}

}