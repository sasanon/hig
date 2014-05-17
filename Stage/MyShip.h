// モーション定義
typedef enum{
	M_WAIT_R,		// 待機(右)
	M_WALK_R,		// 歩行(右)
	M_JUMPUP_R,		// ジャンプ上昇(右)
	M_JUMPDOWN_R,	// ジャンプ下降(右)
	M_WAIT_L,		// 待機(左)
	M_WALK_L,		// 歩行(左)
	M_JUMPUP_L,		// ジャンプ上昇(左)
	M_JUMPDOWN_L,	// ジャンプ下降(左)
	M_MAX,			// 総モーション数
}MOTION_ID;

// 自機
class CMyShip : public CMyMover {
public:
	void* operator new(size_t n) { return MyShipList.New(n); }
	void operator delete(void* p) { MyShipList.Delete(p); }
	CMyShip() : CMyMover(MyShipList) {}
	void Reset();
	void Move();
private:
	BYTE frameid;
	MOTION_ID motid;
	BYTE framemax[10];
};

