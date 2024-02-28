#include "Scene_One.h"
#include "../AppSettings.h"

Scene_One::Scene_One(ApplicationWindow* window)
{
	mWindow = window;
}

void Scene_One::Start()
{
	GameCamera* mainCamera = new GameCamera();
	mainCamera->name = "MainCamera";
	mainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 45.0f);
	mainCamera->transform.SetPosition(glm::vec3(1.24f, 2.8f, 8.30f));
	mainCamera->transform.SetRotation(glm::vec3(-9.5f, 30.0f, 0.0f));
	/*mainCamera->applyPostProcessing = true;
	mainCamera->postProcessing->bloom.isEnabled = true;
	mainCamera->postProcessing->chromaticAberration.isEnabled = true;*/

	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	dirLight->transform.SetRotation(glm::vec3(10, 40, 0));
	dirLight->InitializeLight(Directional);
	dirLight->intensity = 0.8;

}

void Scene_One::Update()
{
}

void Scene_One::Render()
{
}
