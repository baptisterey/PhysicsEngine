#include "OctoTree.h"

OctoTree::OctoTree(int _level, Vector3 _position, Vector3 _size) : level(_level), position(_position), size(_size)
{
}

OctoTree::~OctoTree()
{
}

void OctoTree::Insert(ICollider* collider) {
	if (nodes.size() > 0) {
		std::vector<int> index = GetIndex(collider);
		for(int i = 0; i < index.size(); i++)
			nodes[index[i]].Insert(collider);
		return;
	}
	else if (level == 0 && GetIndex(collider).size() == 0)
		return;

	objects.push_back(collider);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS - 1) { // First level = 0
		Split();

		for (int i = 0; i < objects.size(); i++) {
			std::vector<int> indexs = GetIndex(objects[i]);
			for (int j = 0; j < indexs.size(); j++) {
				nodes[indexs[j]].Insert(objects[i]);
			}
		}

		objects.clear();
	}
}

std::vector<ICollider*> OctoTree::Retrieve(ICollider* collider) {
	if (nodes.size() > 0) {
		std::vector<ICollider*> ret;
		std::vector<int> indexs = GetIndex(collider);
		for (int i = 0; i < indexs.size(); i++) {
			std::vector<ICollider*> possibleCols = nodes[indexs[i]].Retrieve(collider);
			for (int j = 0; j < possibleCols.size(); j++)
				ret.push_back(possibleCols[j]);
		}
		return ret;
	}

	return objects;
}

void OctoTree::Clear()
{
	objects.clear();

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

std::vector<int> OctoTree::GetIndex(ICollider* collider) {
	std::vector<int> index;

	Vector3 cPos = collider->GetOwner()->GetTransform()->GetPosition();
	float cRad = collider->GetBroadRadius();
	if (cPos.x + cRad < position.x || position.x + size.x < cPos.x - cRad ||
		cPos.y + cRad < position.y || position.y + size.y < cPos.y - cRad || 
		cPos.z + cRad < position.z || position.z + size.z < cPos.z - cRad)
		return index;

	Vector3 midPoint = position + size * .5f;
	bool
		xNear = cPos.x - cRad < midPoint.x,
		xFar  = midPoint.x < cPos.x + cRad,
		yNear = cPos.y - cRad < midPoint.y,
		yFar  = midPoint.y < cPos.y + cRad,
		zNear = cPos.z - cRad < midPoint.z,
		zFar  = midPoint.z < cPos.z + cRad;

	if (xNear) {
		if (yNear) {
			if (zNear) {
				index.push_back(0);
			}
			if (zFar) {
				index.push_back(1);
			}
		}
		if (yFar) {
			if (zNear) {
				index.push_back(2);
			}
			if (zFar) {
				index.push_back(3);
			}
		}
	}
	if (xFar) {
		if (yNear) {
			if (zNear) {
				index.push_back(4);
			}

			if (zFar) {
				index.push_back(5);
			}
		}

		if (yFar) {
			if (zNear) {
				index.push_back(6);
			}
			if (zFar) {
				index.push_back(7);
			}
		}
	}

	return index;
}
