#pragma once
class Scene
{
public:
	Scene() : gameObjectFile(""),
		sceneGraphFile(""),
		root(nullptr),
		ObjectFactory(GameObjectFactory::GetInstance()) {}

	Scene(const std::string& gameObjectFile, const std::string& sceneGraphFile)
		: gameObjectFile(gameObjectFile), 
		sceneGraphFile(sceneGraphFile), 
		root(nullptr), 
		ObjectFactory(GameObjectFactory::GetInstance()) {}

	virtual void LoadAssets();
	virtual void LoadGameObjects();
	virtual void BuildHierarchy();
	virtual void UnloadAssets();
	 
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();
	 
	virtual void Pause();
	virtual void Resume();

	virtual GameObject* GetGameObjectByName(const char* name) { return ObjectFactory->QuickFind(name); }
	virtual std::string GetGameObjectFile() { return gameObjectFile; }
private:
	void flushDeletedGameObjects();
	void recursiveLevelUpdate(Node* node);
	void recursiveProcessNewChildren(const rapidjson::Value& nodeValue, Node* parentNode);
	void inputActivity();

protected:
	Root* root;
	GameObjectFactory* ObjectFactory;
	std::string gameObjectFile;
	std::string sceneGraphFile;

};

