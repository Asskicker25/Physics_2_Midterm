#include <Physics/Thread/PhysicsEngineThread.h>
#include <Graphics/Panels/EditorLayout.h>

#include "PhysicsApplication.h"
#include "Scene/Scene_One.h"

void PhysicsApplication::SetUp()
{
	physicsThread = InitializePhysicsThread(0.01f);


	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 500.0f, 45.0f);
	viewportCamera->transform.SetPosition(glm::vec3(15.65, 10, 96));
	viewportCamera->transform.SetRotation(glm::vec3(-2, 90, 0));
	viewportCamera->applyPostProcessing = true;

	EditorLayout::GetInstance().SetMaximizeState(false);

	PhysicsEngine::GetInstance().gravity.y = -9.8f / 3.0f;
	PhysicsEngine::GetInstance().fixedStepTime = 0.01f;

	Scene_One* sceneOne = new Scene_One(this);

	SceneManager::GetInstance().AddScene("SceneOne", sceneOne);
	SceneManager::GetInstance().ChangeScene("SceneOne");


	physicsThread->isRunning = true;
}

void PhysicsApplication::Update()
{
	PhysicsEngine::GetInstance().Update(Timer::GetInstance().deltaTime);
}

void PhysicsApplication::Render()
{
}

void PhysicsApplication::Shutdown()
{
	if (physicsThread != nullptr)
	{
		physicsThread->isAlive = false;
		WaitForSingleObject(physicsThread->threadHandle, INFINITE);
		CloseHandle(physicsThread->threadHandle);
		DeleteCriticalSection(&physicsThread->softBodyUpdateModelData);
	}
}

void PhysicsApplication::ProcessInput(GLFWwindow* window)
{
}

void PhysicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void PhysicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
