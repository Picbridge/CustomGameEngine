/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Timer.h>
Purpose: <Adds time management to other classes>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/08/2023>
--------------------------------------------------------*/
#pragma once
class Timer
{
public:
	Timer();
	~Timer();
	void Update();
	void Pause();
	void Resume();
	void Reset();
	void SetDurationinSeconds(int duration);
	double ElapsedSeconds();

	double GetTimeLeft();
	bool IsTimeOver() { return (ElapsedSeconds() >= m_duration.count()); }
private:
	std::chrono::high_resolution_clock::time_point m_start, m_end;
	std::chrono::seconds m_duration;
	bool m_running;
	double m_curTime;
};

