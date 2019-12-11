#include "OctoTree.h"
#include "ICollider.h"

#include <algorithm>

ICollider* OctoTree::LEFT_PLANE_COLLIDER;
ICollider* OctoTree::RIGHT_PLANE_COLLIDER;
ICollider* OctoTree::BOTTOM_PLANE_COLLIDER;
ICollider* OctoTree::TOP_PLANE_COLLIDER;

OctoTree::OctoTree(int _level, Vector3 _position, Vector3 _size) : level(_level), position(_position), size(_size)
{

}

OctoTree::~OctoTree()
{

}

void OctoTree::Clear()
{
	int size = nodes.size();
	for (int i = 0; i < size; i++)
		nodes[i].Clear();

	nodes.clear();
	vertices.clear();
}

void OctoTree::Insert(Vector3 vertex, ICollider * collider)
{

	int index = GetIndex(vertex);
	if (nodes.size() > 0) {
		if (index >= 0) {
			nodes[index].Insert(vertex, collider);
			return;
		}
	}
	else if (level == 0 && index == -1) {
		// The vertex is outside the root octree
		return;
	}

	vertices.push_back(vertex);

	if (vertices.size() > MAX_OBJECTS && level < MAX_LEVELS - 1) { // First level = 0
		Split();

		int size = vertices.size();
		for (int i = size - 1; i >= 0; i--) {
			int index = GetIndex(vertices[i]);
			if (index != -1) {
				nodes[index].Insert(vertices[i], collider);
				vertices.erase(std::remove(vertices.begin(), vertices.end(), vertices[i]), vertices.end());
			}
		}
	}
}

std::vector<ICollider*> OctoTree::Retrieve(Vector3 vert, ICollider * collider, bool top, bool left, bool bottom, bool right, bool front, bool back)
{
	std::vector<ICollider*> results;

	int index = GetIndex(vert);
	if (nodes.size() > 0) {
		if (index >= 0) {

			std::vector<int> tops = { 2, 3, 6, 7 };
			std::vector<int> lefts = { 0, 1, 2, 3 };
			std::vector<int> bottoms = { 0, 1, 4, 5 };
			std::vector<int> rights = { 4, 5, 6, 7 };
			std::vector<int> fronts = { 0, 2, 4, 6 };
			std::vector<int> backs = { 1, 3, 5, 7 };


			results = nodes[index].Retrieve(vert, collider, 
				std::find(tops.begin(), tops.end(), index) != tops.end(), 
				std::find(lefts.begin(), lefts.end(), index) != lefts.end(), 
				std::find(bottoms.begin(), bottoms.end(), index) != bottoms.end(),
				std::find(rights.begin(), rights.end(), index) != rights.end(),
				std::find(fronts.begin(), fronts.end(), index) != fronts.end(),
				std::find(backs.begin(), backs.end(), index) != backs.end()
			);
		}
	}
	else {

		if (top) {
			results.push_back(OctoTree::TOP_PLANE_COLLIDER);
		}

		if (left) {
			results.push_back(OctoTree::LEFT_PLANE_COLLIDER);
		}

		if (right) {
			results.push_back(OctoTree::RIGHT_PLANE_COLLIDER);
		}

		if (bottom) {
			results.push_back(OctoTree::BOTTOM_PLANE_COLLIDER);
		}

	}

	return results;
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

	return -1;
}