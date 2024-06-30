#pragma once
class Root : public GameObject
{
public:
	Root() {}
	
	void loadPhysics();
	void Init();
	void UpdatePhysics();
	void Draw();

	std::vector<GameObject*> GetRoots();

	glm::vec3 GetPosition() { return GetTransform()->GetPosition(); }
private:
};

