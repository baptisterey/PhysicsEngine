#include "CubeCollider.h"

CubeCollider::CubeCollider(float _width, float _height, float _depth) : width(_width), height(_height), depth(_depth), ICollider()
{


}

CubeCollider::~CubeCollider()
{

}

std::vector<Vector3> CubeCollider::getVertexs() {

	std::vector<Vector3> result;
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));
	return result;
}

std::vector<Face> CubeCollider::getFaces() {

	std::vector<Face> result;
	Face a, b, c, d, e, f;
	a.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(1, 0, 0));
	a.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	a.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	a.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	a.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	b.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(-1, 0, 0));
	b.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	b.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	b.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	b.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));

	c.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 1, 0));
	c.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	c.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	c.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	c.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	d.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, -1, 0));
	d.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	d.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	d.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	d.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));

	e.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 0, 1));
	e.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	e.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	e.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	e.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	f.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 0, -1));
	f.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	f.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	f.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	f.vertexs.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));


	result.push_back(a);
	result.push_back(b);
	result.push_back(c);
	result.push_back(d);
	result.push_back(e);
	result.push_back(f);

	return result;
}

bool CubeCollider::related(Face f) {

	std::vector<Face> faces = getFaces();

	for (Face face : faces)
	{
		if (f.norm == face.norm) //  && f.vertexs == face.vertexs
		{
			return true;
		}
	}
	
	return false;
}