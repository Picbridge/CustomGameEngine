#pragma once
class Level2 : public Scene
{
public:
	Level2();
	~Level2();

	void Init();
	void Update();
	void LateUpdate();
	void Pause();
	void Resume();
	void EntityControl();

private:
	Timer m_timer;
	int DURATION;
	double m_curTime;

	std::mt19937 m_rng;
	std::uniform_int_distribution<int> m_distFirst;
	std::uniform_int_distribution<int> m_distLast; 
	float m_firstDistrib;
	float m_secondDistrib;

	int m_cloneCountFirst;
	int m_cloneCountLast;

	int m_curCloneCountFirst;
	int m_curCloneCountLast;

	GameObject* firstObj;
	GameObject* secondObj;
};

