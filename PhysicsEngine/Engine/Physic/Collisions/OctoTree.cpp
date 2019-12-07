#include "OctoTree.h"

OctoTree::OctoTree(int _level, Vector3 _position, Vector3 _size) : level(_level), position(_position), size(_size)
{
}

OctoTree::~OctoTree()
{
}

void OctoTree::Insert(Vector3 vertex) {
	if (nodes.size() > 0) {
		int index = GetIndex(vertex);
			nodes[index].Insert(vertex);
		return;
	}
	else if (level == 0 && GetIndex(vertex) == -1)
		return;

	vertexs.push_back(vertex);

	if (vertexs.size() > MAX_OBJECTS && level < MAX_LEVELS - 1) { // First level = 0
		Split();

		for (int i = 0; i < vertexs.size(); i++) {
			int index = GetIndex(vertexs[i]);
			nodes[index].Insert(vertexs[i]);
		}

		vertexs.clear();
	}
}


void OctoTree::Insert(Face face) {
	if (nodes.size() > 0) {
		int index = GetIndex(face);
		if (index > -1)
		{
			nodes[index].Insert(face);
			return;
		}
	}
	else if (level == 0 && GetIndex(face) == -1)
		return;

	faces.push_back(face);




	if (faces.size() > MAX_OBJECTS&& level < MAX_LEVELS - 1) { // First level = 0
		Split();

		std::vector<Face> _faces;
		for (Face f : faces) {
			int index = GetIndex(f);
			if (index > -1)
			{
				nodes[index].Insert(f);
			}
			if (index == -2)
			{
				_faces.push_back(f);
			}
		}
		faces = _faces;
	}
	return;

}




std::vector<Face> OctoTree::Retrieve(Vector3 vert) {
	std::vector<Face> result;
	if (nodes.size() > 0) {
		int index = GetIndex(vert);
		result = nodes[index].Retrieve(vert);
	}

	for (Face f : faces)
	{
		result.push_back(f);
	}

	return result;
}

std::vector<Face> OctoTree::Retrieve(Face face) {
	std::vector<Face> result;
	if (nodes.size() > 0) {
		int index = GetIndex(face);
		if (index > -1) {
			result = nodes[index].Retrieve(face);
		}
	}

	for (Face f : faces)
	{
		result.push_back(f);
	}

	return result;
}

void OctoTree::Clear()
{
	vertexs.clear();

	for (int i = 0; i < nodes.size(); i++)
		nodes[i].Clear();

	nodes.clear();
}

void OctoTree::Split()
{
	Vector3 subSize = size * .5f;

	nodes.push_back(OctoTree(level + 1, Vector3(position.x,				position.y,				position.z			  ), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x,				position.y,				position.z + subSize.z), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x,				position.y + subSize.y, position.z			  ), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x,				position.y + subSize.y, position.z + subSize.z), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x + subSize.x, position.y,				position.z			  ), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x + subSize.x, position.y,				position.z + subSize.z), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x + subSize.x, position.y + subSize.y, position.z			  ), subSize));
	nodes.push_back(OctoTree(level + 1, Vector3(position.x + subSize.x, position.y + subSize.y, position.z + subSize.z), subSize));
}

int OctoTree::GetIndex(Vector3 vertex) {


	if (vertex.x < position.x || position.x + size.x < vertex.x ||
		vertex.y < position.y || position.y + size.y < vertex.y ||
		vertex.z < position.z || position.z + size.z < vertex.z)
		return -1;

	Vector3 midPoint = position + size * .5f;
	bool
		xNear = vertex.x < midPoint.x,
		xFar  = midPoint.x < vertex.x,
		yNear = vertex.y < midPoint.y,
		yFar  = midPoint.y < vertex.y,
		zNear = vertex.z < midPoint.z,
		zFar  = midPoint.z < vertex.z;

	if (xNear) {
		if (yNear) {
			if (zNear) {
				return 0;
			}
			if (zFar) {
				return 1;
			}
		}
		if (yFar) {
			if (zNear) {
				return 2;
			}
			if (zFar) {
				return 3;
			}
		}
	}
	if (xFar) {
		if (yNear) {
			if (zNear) {
				return 4;
			}

			if (zFar) {
				return 5;
			}
		}

		if (yFar) {
			if (zNear) {
				return 6;
			}
			if (zFar) {
				return 7;
			}
		}
	}
}


int OctoTree::GetIndex(Face face) {

	int index = GetIndex(face.vertexs[0]);
	for (Vector3 v : face.vertexs)
	{ 
		if (!(index == GetIndex(v)))
		{
			return -2;
		}
	}
	return index;
}
