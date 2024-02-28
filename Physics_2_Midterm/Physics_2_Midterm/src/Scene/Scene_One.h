#pragma once
#include <Graphics/Scene/BaseScene.h>
#include <Graphics/ApplicationWindow.h>
#include "../Flag/Flag.h"


using namespace Scene;

class Scene_One : public BaseScene
{
public:
	~Scene_One();

	Scene_One(ApplicationWindow* window);

	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;


private:
	Flag* flag = nullptr;

	ApplicationWindow* mWindow = nullptr;
};

