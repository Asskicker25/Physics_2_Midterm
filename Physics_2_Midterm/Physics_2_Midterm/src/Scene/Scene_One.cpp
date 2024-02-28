#include "Scene_One.h"
#include "../AppSettings.h"
#include <Graphics/MathUtils.h>

using namespace MathUtilities;

Scene_One::~Scene_One()
{
	delete mFlag;
}

Scene_One::Scene_One(ApplicationWindow* window)
{
	mWindow = window;
}

void Scene_One::Start()
{
	mMainCamera = new GameCamera();
	mMainCamera->name = "MainCamera";
	mMainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 45.0f);
	mMainCamera->transform.SetPosition(glm::vec3(20.0f, 20.3f, 96.43f));
	mMainCamera->transform.SetRotation(glm::vec3(-2.0f, 90.0f, 0.0f));


	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	dirLight->transform.SetRotation(glm::vec3(10, 40, 0));
	dirLight->InitializeLight(Directional);
	dirLight->intensity = 0.6;


	Model* terrain = new Model("Assets/Model/TerrianFinal_UV_XZ.ply");
	terrain->name = "Terrain";
	terrain->transform.SetRotation(glm::vec3(0, 17, 0));
	terrain->meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Model/TerrainTex.jpg");
	terrain->meshes[0]->material->AsMaterial()->textureTiling = glm::vec2(10, 10);

	mFlag = new Flag();
}

void Scene_One::Update()
{
	if (mLerpDone) return;

	mTimeStep += Timer::GetInstance().deltaTime * mCameraLerpSpeed;

	if (mTimeStep > 1.0f)
	{
		mTimeStep = 1;
		mLerpDone = true;
	}

	mMainCamera->transform.position = MathUtils::Lerp(mCameraInitPos, mCameraFinalPos, mTimeStep);

}

void Scene_One::Render()
{
}
