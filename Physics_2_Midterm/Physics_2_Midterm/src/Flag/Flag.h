#pragma once
#include <Physics/Softbody/SoftBodyForVertex.h>
#include <Graphics/InputManager/InputManager.h>
#include "../Shader/FlagShader.h"

using namespace Verlet;

class Flag : public SoftBodyForVertex, public iInputListener
{
public:

	Flag();
	~Flag();

	virtual void Start();
	virtual void OnPropertyDraw();

	virtual void OnKeyPressed(const int& key);
	virtual void Update(float deltaTime);
	virtual void Render();

	float mBulletHoleRadius = 0.5f;

	FlagShader* flagShader = nullptr;
	std::vector<Node*> mListOfBulletHoleNode;

private:

	void LoadShader();
	void LoadPole();
	void AddWindForce();
	void ReduceWindForce();
	void InitFlapNodes();
	void HandleFlap(float deltaTime);
	void AddForceToFlapNodes();
	void RandomBulletHole();
	void DisconnectFromPole();
	void Reset();

	Model* mPole = nullptr;
	Mesh localMeshData;


	float mColumnWidth = 175;

	float mWindIncreaseSpeed = 5.0f;
	float mCurrentWindForce = 0.0f;
	float mMaxWindForce = -30.0f;
	float mMinWindForce = -0.5f;

	float mFlapTimeStep = 0;
	float mFlapChangeInterval = 0;

	float mSinValue = 0;

	glm::vec2 mFlapRange = glm::vec2(3,6);
	glm::vec2 mFlapChangeIntervalRange = glm::vec2(0.5,2);
	glm::vec3 mFlapNodesForce = glm::vec3(0);

	glm::vec3 minFlagPos = glm::vec3(0, 0, 0);
	glm::vec3 maxFlagPos = glm::vec3(0, 6, -10.5f);

	std::vector<LockNode> mListOFlapNodesSpheres;

};

