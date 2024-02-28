#pragma once

#include <Graphics/ApplicationWindow.h>
#include <Physics/Thread/PhysicsEngineThreadInfo.h>


class PhysicsApplication : public ApplicationWindow
{

private:

	// Inherited via ApplicationWindow
	void SetUp() override;
	void Update() override;
	void Render() override;
	void Shutdown() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;


	PhysicsEngineThreadInfo* physicsThread = nullptr;
};

