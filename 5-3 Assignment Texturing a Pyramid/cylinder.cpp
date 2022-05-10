
#include "cylinder.h"

#include <iostream>
#include <utility>


cylinder::cylinder(float x, float y, float z, float radius, float length, float direction) : r(radius), l(length), d(direction)
{
	this->origin[0] = x;
	this->origin[1] = y;
	this->origin[2] = z;
	getTop();
	/*getBottom();
	getShaft();
	getFullCylinder();*/

	this->top.insert(this->top.end(), this->origin.begin(), this->origin.end());
	this->top.push_back(0.0f);
	this->top.push_back(1.0f);
	this->top.push_back(1.0f);
	this->top.push_back(1.0f);
}

void cylinder::getTop()
{
	// create a circle with radius (r) and number of segments / steps predefined
	const float PI = 3.14f;
	const float STEP = 36;
	float sectorStep = 2.0f * PI / STEP;
	int step = 0;
	int vert = 1;

	this->vertices.push_back(0);

	//std::vector<float>().swap(this->top);
	for (int i = 0; i <= STEP * 2 + 1; ++i)
	{
		

		float sectorAngle = i * sectorStep;
		this->top.push_back(r * cos(sectorAngle)); // x
		this->top.push_back(r * sin(sectorAngle)); // y
		this->top.push_back(0);                // z

		this->top.push_back(0.0f);
		this->top.push_back(1.0f);
		this->top.push_back(0.0f);
		this->top.push_back(1.0f);
		this->vertices.push_back(vert);
		vert++;
		step++;
		if(step == 2)
		{
			step = 0;
			vert--;
			this->vertices.push_back(0);
			
		}

	}

	this->top[0] = origin[0];

}
void cylinder::getBottom()
{
	// same as top but length (l) from top in correct direction (d)
}
void cylinder::getShaft()
{
	//will need the cross-product here
}
void cylinder::getFullCylinder()
{
	
}
