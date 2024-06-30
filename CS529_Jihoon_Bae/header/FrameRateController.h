#pragma once
class FrameRateController
{
public:
	static FrameRateController* GetInstance();

	void SetTargetFPS(const unsigned int target);

	void Update();
	void LateUpdate();

	float GetDT() { return m_deltaTime; }

private:
	FrameRateController() : m_deltaTime(0.0f), m_targetFPS(60) {
		SetTargetFPS(m_targetFPS);
	}
	
	static FrameRateController* instance;
	unsigned int m_targetFPS;
	float m_deltaTime;
	std::chrono::high_resolution_clock::time_point frameStart;
	std::chrono::duration<double, std::ratio<1>> frameTime;
};

