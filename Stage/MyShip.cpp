#include "../Main.h"


// ���@�̏�����
void CMyShip::Reset() {
	// ���[�V�����f�[�^������
	motid  = M_WAIT_R;		frameid = 0;	// �E�����ҋ@���[�V����0�t���[���ڂɐݒ�
	// �e���[�V�����̃R�}����ݒ�
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
	// �e�N�X�`��������
	Texture=GetTexture(L"chara.png");								// �e�N�X�`���t�@�C��
	TextureScale    = CVector(48.0f/512.0f,  48.0f/512.0f, 1.0f);	// �e�N�X�`�����W�̎捞�͈�
	TexturePosition = CVector(48.0f*frameid, 48.0f*motid, 1.0f);	// �e�N�X�`�����W�̎捞�ʒu(����s�|�b�h)

	Velocity.X= 0.0f;	// �ړ���0
	Scale=CVector(1, 1, 1)*0.07f;
}

// ���@�̈ړ�
void CMyShip::Move() {
	static float jump = 0.0f;

	// ���ԂŃA�j���[�V����������
	Time++;

	// ���͍X�V
	Velocity.X = 0.0f;
	if (KeyState[0][DIK_RIGHT])	Velocity.X += 0.015f;	// �E������
	if (KeyState[0][DIK_LEFT])	Velocity.X -= 0.015f;	// ��������

	// �A�j���p�^�[���̍X�V
	if (Velocity.X > 0){
		motid = M_WALK_R;		// �E�E���s���[�V�����֐ؑ�
	}
	if (Velocity.X < 0){
		motid = M_WALK_L;		// �E�E���s���[�V�����֐ؑ�
	}
	if (Velocity.X == 0){
		if (motid == M_WALK_R)	motid = M_WAIT_R;		// �E�E�ҋ@���[�V�����֐ؑ�
		if (motid == M_WALK_L)	motid = M_WAIT_L;		// ���E�ҋ@���[�V�����֐ؑ�
	}

	// uv�A�j���X�V
	if (Time >= 6){
		Time -= 6;
		frameid = (frameid + 1) % framemax[motid];
		TexturePosition = CVector(48 * frameid / 512.0f, 48 * motid / 512.0f, 1.0f);
	}


	// �d�͐ݒ�
	Velocity.Y-=0.002f;

	// �ړ��ʂ̓K�p
	Position+=Velocity;

	// �W�����v
	if (/*hit.Down &&*/ OldKeyState[0][DIK_Z] && KeyState[0][DIK_Z]) Velocity.Y = 0.04f;

	// �_�b�V��
	if (KeyState[0][DIK_X]){
		Position.X += Velocity.X;
		if (Time % 10 == 0 && Velocity.X != 0.0f && hit.Down)
			New<CEffect>(Position.X, Position.Y - 0.03f, 0, 0, 0, TE_DASH);
	}

	// ��������
	if (OldKeyState[0][DIK_X] && KeyState[0][DIK_X]){
		BlockList.Apply([&](CMover* b) {
			if (TB_KEY_STAR   <= b->Type / 100   &&			// ���u���b�N�͈͂̂͂��߂���
				b->Type / 100 <= TB_KEY_HEXAGRAM &&			// ���u���b�N�͈͂̂����܂ł̊Ԃ̎��
				Length(b->Position - Position) < 0.13f){	// �Ώۃu���b�N�ƐڐG���
				b->Type = b->Type - b->Type % 100 + MB_ABOVE_PLAYER;
				// ���[�V�������������ҋ@��Ԃ֑J�� ������
			}
		});
	}

	// �u���b�N�Ƃ̏Փˏ���
	CHitRectangle hit;
	Apply(BlockList, hit);

	// ���_�A�C�e���̎擾
	ItemList.Apply([&](CMover* e) {
		if (Length(e->Position - Position)<0.05f) {
			// �g�U���鐯�G�t�F�N�g��20�\��
			for (int i = 0; i<20; i++)	New<CEffect>(e->Position.X, e->Position.Y, 0, 0, 0, TE_STAR);
			// �A�C�e�����̂͏���
			e->Life = 0;
			Score += 10;
		}
	});

	// �G�Ƃ̏Փˏ���
	EnemyList.Apply([&](CMover* e) {
		if (Length(e->Position-Position)<0.05f) {
			// �g�U���鐯�G�t�F�N�g��20�\��
			for (int i = 0; i<20; i++)	New<CEffect>(Position.X, Position.Y, 0, 0, 0, TE_STAR);
			Life = 0;
		}
	});
	// �J�����̈ʒu�Ǐ]
	if (Life){
		CameraList.Apply([&](CMover* m) {
			if (m->Type == 0)
			m->Position = Position + CVector(0, 0, -10);
		});
	}
}

