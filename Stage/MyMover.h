// 移動物体の拡張
class CMyMover : public CMover {
public:
	CMyMover(CMoverList& list) : CMover(list) {}
	CVector PosNext;
};

