#pragma once
class EnemyBehavior : public Component
{
public:

	EnemyBehavior();
	~EnemyBehavior();

	void Init();
	void Update();
	void Shutdown();
	void OnCollisionEnter(const Event& e);
	void OnClone(const Event& e);
	void SetHits(int hits);

	glm::vec3 getRandomPosition();
private:
	EventHandler m_onCollisionCallback;
	int m_collisionEventId;
	EventHandler m_cloneEventCallback;
	int m_cloneEventId;
	Timer m_cooldown;

	float m_windowHalfSize;
	float m_radius;
	int m_hits;
	std::string m_name;
};

