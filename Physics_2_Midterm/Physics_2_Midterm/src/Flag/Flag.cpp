#include <Graphics/Panels/ImguiDrawUtils.h>
#include <Graphics/Debugger.h>
#include <Graphics/MathUtils.h>

#include "Flag.h"
#include <Graphics/Timer.h>

using namespace MathUtilities;

void Flag::OnPropertyDraw()
{
	SoftBodyForVertex::OnPropertyDraw();

	if (!ImGui::TreeNodeEx("Flag", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGuiUtils::DrawFloat("MaxWind", mMaxWindForce);
	ImGuiUtils::DrawFloat("WindIncreaseSpeed", mWindIncreaseSpeed);
	ImGuiUtils::DrawFloat("SinValue", mSinValue);
	ImGuiUtils::DrawVector2ImGui("FlapRange", mFlapRange, 0, mColumnWidth);
	ImGuiUtils::DrawVector2ImGui("FlapInterval", mFlapChangeIntervalRange, 0, mColumnWidth);
	ImGuiUtils::DrawVector3ImGui("Gravity", mGravity, 0, mColumnWidth);
	ImGuiUtils::DrawVector3ImGui("FlapForce", mFlapNodesForce, 0, mColumnWidth);

	ImGui::TreePop();
}




Flag::Flag()
{
	name = "Flag";
	mGravity = glm::vec3(0.5, -5, -0.5f);
	//mGravity = glm::vec3(0.0, 0, 00.0f);
	mFlapNodesForce = mGravity;
	mTightness = 0.5f;
	showDebugModels = false;

	mPole = new Model("Assets/Model/Pole.fbx");
	mPole->name = "Pole";
	mPole->transform.SetPosition(glm::vec3(4.24f, 0, 101.23f));
	mPole->transform.SetRotation(glm::vec3(-90.0f, 90, 0));
	mPole->transform.SetScale(glm::vec3(0.1f));
	mPole->meshes[0]->material->AsMaterial()->specularValue = 1;

	LoadModel("Assets/Model/Flag.ply");
	meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Model/SpaceMarine.png");

	transform.SetPosition(glm::vec3(3.44f, 15.56f, 100.0f));
	transform.SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	transform.SetScale(glm::vec3(35.0f, 20.0f, 1.0f));

	AddLockNode(glm::vec3(0, 0.0f, 0.0f), 0.4f);
	//AddLockNode(glm::vec3(0, 0.75f, 0.0f), 0.4f);
	AddLockNode(glm::vec3(0, 3.0f, 0.0f), 0.4f);
	//AddLockNode(glm::vec3(0, 2.25f, 0.0f), 0.4f);
	AddLockNode(glm::vec3(0, 6.0f, 0.0f), 0.4f);


	/*LoadModel("Assets/Model/Plane.ply");

	transform.SetPosition(glm::vec3(3.7f, 10.0f, 97.0f));
	transform.SetRotation(glm::vec3(0.0f, 0.0f, 90.0f));
	transform.SetScale(glm::vec3(10.0f, 1.0f, 20.0f));*/

	/*AddLockNode(glm::vec3(0,1.5f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,0.75f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,0,3.0f), 0.4f);
	AddLockNode(glm::vec3(0,-1.5f,3.0f), 0.4f);
	AddLockNode(glm::vec3(0, -0.75f, 3.0f), 0.4f);*/

	InputManager::GetInstance().AddListener(this);
}

Flag::~Flag()
{
	mListOfNodes.clear();
	mListOfSticks.clear();
}

void Flag::Start()
{
	InitializeSoftBody();
	//InitFlapNodes();

	mFlapChangeInterval = MathUtils::GetRandomFloatNumber(mFlapChangeIntervalRange.x, mFlapChangeIntervalRange.y);
}


void Flag::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_RIGHT)
	{
		AddWindForce();
	}
	else if (key == GLFW_KEY_LEFT)
	{
		ReduceWindForce();
	}
	else if (key == GLFW_KEY_SPACE)
	{
		RandomBulletHole();
	}
}

void Flag::Update(float deltaTime)
{
	HandleFlap(deltaTime);
}

void Flag::Render()
{
	BaseSoftBody::Render();

	//if (!showDebugModels) return;

	//Renderer::GetInstance().DrawSphere(transform.position + maxFlagPos, 0.4f, glm::vec4(1, 0, 0, 1));

	//for (glm::vec3& pos : mListOfBulletHolePos)
	//{
	//	
	//	Renderer::GetInstance().DrawSphere(pos, mBulletHoleRadius, glm::vec4(1, 0, 0, 1));
	//}

}

void Flag::AddWindForce()
{
	mGravity.z -= mWindIncreaseSpeed;

	if (mGravity.z < mMaxWindForce)
	{
		mGravity.z = mMaxWindForce;
	}
}

void Flag::ReduceWindForce()
{
	mGravity.z += mWindIncreaseSpeed;

	if (mGravity.z > mMinWindForce)
	{
		mGravity.z = mMinWindForce;
	}
}

void Flag::HandleFlap(float deltaTime)
{
	AddForceToFlapNodes();

	if (mGravity.z == mMinWindForce) return;

	//mSinValue = sin(Timer::GetInstance().elapsedTime);
	//mFlapNodesForce.x = mSinValue;


	mFlapTimeStep += deltaTime;

	if (mFlapTimeStep > mFlapChangeInterval)
	{
		mFlapTimeStep = 0;
		mFlapChangeInterval = MathUtils::GetRandomFloatNumber(mFlapChangeIntervalRange.x, mFlapChangeIntervalRange.y);
		mFlapNodesForce.x = MathUtils::GetRandomFloatNumber(mFlapRange.x, mFlapRange.y);

		int flapDir = MathUtils::GetRandomIntNumber(0, 1);

		mFlapNodesForce.x *= flapDir == 0 ? 1 : -1;
	}

}

void Flag::AddForceToFlapNodes()
{
	for (Node* node : mListOfNonGravityNodes)
	{
		node->velocity = mFlapNodesForce;
	}
}

void Flag::InitFlapNodes()
{
	mListOFlapNodesSpheres.push_back({ transform.position + glm::vec3(0, 0, -6), 1.0f });
	mListOFlapNodesSpheres.push_back({ transform.position + glm::vec3(0, 1.5f, -6), 1.0f });
	mListOFlapNodesSpheres.push_back({ transform.position + glm::vec3(0,3, -6), 1.0f });

	for (Node* node : mListOfNodes)
	{
		for (LockNode& lockNode : mListOFlapNodesSpheres)
		{
			float length = glm::length(node->mCurrentPosition - lockNode.center);

			if (length > lockNode.radius) continue;

			mListOfNonGravityNodes.push_back(node);
		}

	}

}


void Flag::RandomBulletHole()
{
	Node* randomNode = mListOfNodes[MathUtils::GetRandomIntNumber(0, mListOfNodes.size() - 1)];

	for (Node* node : mListOfNodes)
	{
		glm::vec3 diff = node->mCurrentPosition - randomNode->mCurrentPosition;

		float sqDist = glm::dot(diff, diff);

		if (sqDist > mBulletHoleRadius * mBulletHoleRadius) continue;

		mListOfBulletHoleNode.push_back(node);

	}

	for (Node* node : mListOfBulletHoleNode)
	{
		for (Stick* stick : node->mListOfConnectedSticks)
		{
			DisconnectStick(stick);
		}
	}

}

