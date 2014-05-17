// ƒJƒƒ‰
class CCamera : public CMyMover {
public:
	void* operator new(size_t n) { return CameraList.New(n); }
	void operator delete(void* p) { CameraList.Delete(p); }
	CCamera() : CMyMover(CameraList) {}
	void Reset();
	void Move();
};

