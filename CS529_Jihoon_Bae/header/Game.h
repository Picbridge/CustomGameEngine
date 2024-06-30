#pragma once
class Game
{
public:
	static Game* GetInstance();


	void Init();
	void Run();
	void Reset();
	void Quit();

	template <typename DataType>
	typename std::enable_if_t<std::is_base_of<Scene, DataType>::value, DataType*> AddLevel()
	{
		DataType* level = new DataType();
		m_pEngine->AddLevelToWorld(level);
		MAX_LEVEL++;
		return level;
	}

private:
	Game();
	static Game* instance;
	Engine* m_pEngine;
	int m_curLevel;
	int MAX_LEVEL;
};

