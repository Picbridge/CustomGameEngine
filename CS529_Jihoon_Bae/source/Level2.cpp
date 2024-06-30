#include "pch.h"

Level2::Level2() : DURATION(60), 
m_curTime(DURATION), 
m_firstDistrib(2*DURATION/3),
m_secondDistrib(DURATION - m_firstDistrib),
m_distFirst(0, m_firstDistrib),
m_distLast(0, m_secondDistrib)
{
	gameObjectFile = "data/ObjectData.json";
	sceneGraphFile = "data/Level1_Hierarchy.json";
	m_timer.SetDurationinSeconds(DURATION);

	m_cloneCountFirst = 40;
	m_cloneCountLast = 30;
	m_rng.seed(std::random_device{}());
}

Level2::~Level2()
{

}

void Level2::Init()
{
	std::cout << "Survive for " << DURATION << " seconds" << std::endl;
	Scene::Init();
	m_timer.Reset();
}

void Level2::Update()
{
	Scene::Update();
	m_timer.Update();
	EntityControl();
	auto leftTime = m_timer.GetTimeLeft();
	if (leftTime != m_curTime)
	{
		std::cout << "Time left: " << leftTime << " seconds" << std::endl;
		m_curTime = leftTime;
	}
}

void Level2::LateUpdate()
{
	Scene::LateUpdate();
	if (m_timer.IsTimeOver())
	{
		auto win = std::make_shared<int>(LevelsConstants::WIN);
		EventManager::GetInstance()->TriggerEvent(Event(EventType::SceneChangeEvent, win));
	}

}

void Level2::Pause()
{
	m_timer.Pause();
}

void Level2::Resume()
{
	m_timer.Resume();
}

void Level2::EntityControl()
{
	auto dt = FrameRateController::GetInstance()->GetDT();
	float elapsedTime = m_timer.ElapsedSeconds();

	if (elapsedTime <= m_firstDistrib) {
		float remainingTimeFirst = m_firstDistrib - elapsedTime;
		float cloneRateFirst = static_cast<float>(m_cloneCountFirst - m_curCloneCountFirst) / remainingTimeFirst;
		float cloneProbability = cloneRateFirst * dt;

		std::uniform_real_distribution<float> distrib(0.0f, 1.0f);
		if (m_curCloneCountFirst < m_cloneCountFirst && distrib(m_rng) < cloneProbability)
		{
			auto name = std::make_shared<std::string>("Object3");
			EventManager::GetInstance()->TriggerEvent(Event(EventType::CloneEvent, name));
			m_curCloneCountFirst++;
		}
	}
	else {
		float remainingTimeLast = DURATION - elapsedTime;
		float cloneRateLast = static_cast<float>(m_cloneCountLast - m_curCloneCountLast) / remainingTimeLast;
		float cloneProbability = cloneRateLast * dt;

		std::uniform_real_distribution<float> distrib(0.0f, 1.0f);
		if (m_curCloneCountLast < m_cloneCountLast && distrib(m_rng) < cloneProbability)
		{
			auto name = std::make_shared<std::string>("Object2");
			EventManager::GetInstance()->TriggerEvent(Event(EventType::CloneEvent, name));
			m_curCloneCountLast++;
		}
	}
}