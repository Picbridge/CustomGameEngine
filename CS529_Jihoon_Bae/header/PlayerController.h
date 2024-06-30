#pragma once
class PlayerController : public Component
{
	enum CurDirection {
		RIGHT,
		LEFT,
		IDLE
	};
public:
	PlayerController();
	~PlayerController();

	void Init();
	void Update();
	void Shutdown();
	void HandleEvent(const Event& event);
	void ChangeDirection();
	void Move();
private:
	float m_speed;
	CurDirection m_curDir;
};

