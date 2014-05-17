typedef enum{
	TE_STAR,	// ���擾���p�[�e�B�N��
	TE_DASH,	// �_�b�V������
}TYPE_EFFECT;


// ����
class CEffect : public CMyMover {
public:
	void* operator new(size_t n) { return EffectList.New(n); }
	void operator delete(void* p) { EffectList.Delete(p); }
	CEffect() : CMyMover(EffectList) {}
	void Reset();
	void Move();
	CVector Position0;
	float   FadeAlpha;
};

