#include "Scene_One.h"
#include "../AppSettings.h"

Scene_One::~Scene_One()
{
	delete flag;
}

Scene_One::Scene_One(ApplicationWindow* window)
{
	mWindow = window;
}

void Scene_One::Start()
{
	GameCamera* mainCamera = new GameCamera();
	mainCamera->name = "MainCamera";
	mainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 45.0f);
	mainCamera->transform.SetPosition(glm::vec3(20.0f, 20.3f, 96.43f));
	mainCamera->transform.SetRotation(glm::vec3(-2.0f, 90.0f, 0.0f));
	/*mainCamera->applyPostProcessing = true;
	mainCamera->postProcessing->bloom.isEnabled = true;
	mainCamera->postProcessing->chromaticAberration.isEnabled = true;*/

	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	dirLight->transform.SetRotation(glm::vec3(10, 40, 0));
	dirLight->InitializeLight(Directional);
	dirLight->intensity = 0.6;


	Model* terrain = new Model("Assets/Model/TerrianFinal_UV_XZ.ply");
	terrain->name = "Terrain";
	terrain->transform.SetRotation(glm::vec3(0,17,0));
	terrain->meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Model/TerrainTex.jpg");
	terrain->meshes[0]->material->AsMaterial()->textureTiling = glm::vec2(10, 10);

	flag = new Flag();
}

void Scene_One::Update()
{
}

void Scene_One::Render()
{
}
