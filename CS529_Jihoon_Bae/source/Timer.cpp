/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Timer.cpp>
Purpose: <Adds time management to other classes>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <12/08/2023>
--------------------------------------------------------*/
#include "pch.h"

Timer::Timer() : m_duration(0), m_curTime(0), m_running(false)
{
}

Timer::~Timer()
{
}

void Timer::Reset()
{
	m_start = std::chrono::high_resolution_clock::now();
	m_running = true;
}

void Timer::Update()
{
	double elapsed = ElapsedSeconds();

	auto updatedTime = (m_duration.count() - elapsed);
	if (m_curTime != updatedTime)
		m_curTime = updatedTime;
}

void Timer::Pause()
{
	m_end = std::chrono::high_resolution_clock::now();
	m_running = false;
}

void Timer::Resume()
{
	m_start = m_end;
	m_running = true;
}

void Timer::SetDurationinSeconds(int duration)
{
	m_duration = std::chrono::seconds(duration);
}

double Timer::ElapsedSeconds() 
{
	auto elapsedSeconds = (m_running ? std::chrono::high_resolution_clock::now() : m_end) - m_start;

	return std::chrono::duration_cast<std::chrono::seconds>(elapsedSeconds).count();
}

double Timer::GetTimeLeft()
{
	return m_curTime;
}