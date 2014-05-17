typedef enum{
	TE_STAR,	// 星取得時パーティクル
	TE_DASH,	// ダッシュ中煙
}TYPE_EFFECT;


// 効果
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

