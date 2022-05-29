#pragma once

#include <vector>

class cylinder
{
public:
	std::vector<float> top;
	std::vector<float> bottom;
	std::vector<float> shaft;
	std::vector<float> fullCylinder;
	std::vector<int> vertices;
	std::vector<float> origin = {0.0f, 0.0f, 0.0f};

	float r;
	float l;
	float d;

	void getTop();
	void getBottom();
	void getShaft();
	void getFullCylinder();

	cylinder(float x, float y, float z, float radius, float length, float direction);
};



