#pragma once
class Level3 : public Scene
{
public:
	Level3();
	~Level3();

	void Init();
	void Update();

private:
	Timer m_timer;
};

