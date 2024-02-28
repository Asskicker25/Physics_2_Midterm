#include <Graphics/Panels/ImguiDrawUtils.h>

#include "Flag.h"

Flag::Flag()
{
	name = "Flag";
	mGravity = glm::vec3(0.7, -1, -2);
	mTightness = 1.0f;
	showDebugModels = false;
	mNodeMaxVelocity = glm::vec3(10,-10,-30);

	LoadModel("Assets/Model/Flag.ply");
	meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Model/SpaceMarine.png");

	transform.SetPosition(glm::vec3(3.74f, 8.5f, 100.0f));
	transform.SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	transform.SetScale(glm::vec3(20.0f, 10.0f, 1.0f));

	AddLockNode(glm::vec3(0, 0.0f, 0.0f), 0.4f);
	//AddLockNode(glm::vec3(0, 0.75f, 0.0f), 0.4f);
	AddLockNode(glm::vec3(0, 1.5f, 0.0f), 0.4f);
	//AddLockNode(glm::vec3(0, 2.25f, 0.0f), 0.4f);
	AddLockNode(glm::vec3(0, 3.0f, 0.0f), 0.4f);
	

	/*LoadModel("Assets/Model/Plane.ply");

	transform.SetPosition(glm::vec3(3.7f, 10.0f, 97.0f));
	transform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));
	transform.SetScale(glm::vec3(10.0f, 1.0f, 20.0f));*/

	/*AddLockNode(glm::vec3(0,1.5f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,0.75f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,0,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,-1.5f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0, -0.75f, 3.0f), 0.4f);*/
}

Flag::~Flag()
{
}

void Flag::Start()
{
	InitializeSoftBody();
}

void Flag::OnPropertyDraw()
{
	SoftBodyForVertex::OnPropertyDraw();

	if (!ImGui::TreeNodeEx("Flag", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGuiUtils::DrawVector3ImGui("Gravity", mGravity,0, mColumnWidth);
	
	ImGui::TreePop();
}

