#pragma once
class Follow : public Component
{
public:
	Follow();
	~Follow();

	void Init();
	void Update();
	void Shutdown();
	void HandleEvent(const Event& event);
	void Move();
private:
	float m_speed;
};

