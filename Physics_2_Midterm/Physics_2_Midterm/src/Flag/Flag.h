#pragma once
#include <Physics/Softbody/SoftBodyForVertex.h>

using namespace Verlet;

class Flag : public SoftBodyForVertex
{
public:

	Flag();
	~Flag();

	virtual void Start();
};

