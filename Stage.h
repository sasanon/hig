// ステージ
class CStage : public CMyMover {
public:
	void* operator new(size_t n) { return StageList.New(n); }
	void operator delete(void* p) { StageList.Delete(p); }
	CStage() : CMyMover(StageList) {}
	void Reset();
	void Move();
};

