#ifndef Block_h
#define Block_h

// �u���b�N�����̒�`
typedef enum{
	TB_NORMAL,		// ��j��u���b�N
	TB_CLOUD,		// ��j��u���b�N(�_)
	TB_BREAK,		// �j��\�u���b�N
	TB_KEY_STAR,	// ���u���b�N(��)
	TB_KEY_CIRCLE,	// ���u���b�N(�~)
	TB_KEY_HEART,	// ���u���b�N(�n�[�g)
	TB_KEY_HEXAGRAM,	// ���u���b�N(�Z䊐�)
	TB_ITEM,		// �A�C�e���u���b�N
	TB_MAX,
}TYPE_BLOCK;

// �ړ������̒�`
typedef enum{
	MB_STOP,			// �����Ȃ�
	MB_X,				// �����ŉ��ɍs�����藈����
	MB_XSIN,			// ���������ĉ��ɍs�����藈����
	MB_Y,				// �����ŏc�ɍs�����藈����
	MB_YSIN,			// ���������ďc�ɍs�����藈����
	MB_PENDULUM,		// �U��q�^��
	MB_CIRCLE,			// �����~�^��
	MB_ABOVE_PLAYER,	// �Ǐ]���ď�Ƀv���C���[��
	MB_MAX,
}TYPE_MOVE;

// �u���b�N
class CBlock : public CMyMover {
public:
	void* operator new(size_t n) { return BlockList.New(n); }
	void operator delete(void* p) { BlockList.Delete(p); }
	CBlock() : CMyMover(BlockList) {}
	void Reset();
	void Move();
private:
	CVector MoveCenter;
};

#endif
