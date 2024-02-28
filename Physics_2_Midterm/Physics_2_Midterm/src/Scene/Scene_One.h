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
	Flag* mFlag = nullptr;
	GameCamera* mMainCamera = nullptr;

	ApplicationWindow* mWindow = nullptr;

	glm::vec3 mCameraInitPos = glm::vec3(-15.5f, 19.0f, 96.43f);
	glm::vec3 mCameraFinalPos = glm::vec3(34.1f, 20.0f,96.43f);

	bool mLerpDone = false;

	float mTimeStep = 0;
	float mCameraLerpSpeed = 0.2f;
};

