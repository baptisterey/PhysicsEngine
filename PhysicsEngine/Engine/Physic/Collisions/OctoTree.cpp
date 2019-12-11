#include "OctoTree.h"
#include "ICollider.h"

struct VertexCollider {
	Vector3 worldPosition;
	ICollider* collider;

	bool operator== (VertexCollider const& vertexCollider) {
		return worldPosition == vertexCollider.worldPosition && collider == vertexCollider.collider;
	}
};

struct FaceCollider {
	Face face;
	ICollider* collider;

	bool operator== (FaceCollider const& faceCollider) {
		return face == faceCollider.face && collider == faceCollider.collider;
	}
};

OctoTree::OctoTree(int _level, Vector3 _position, Vector3 _size) : level(_level), position(_position), size(_size)
{

}

OctoTree::~OctoTree()
{

}


std::vector<FaceCollider> OctoTree::RetrieveFromVert(Vector3 vert, ICollider* collider) {
	std::vector<FaceCollider> result;

	if (nodes.size() > 0) {
		int index = GetIndex(vert);
		if (index != -1) {
			result = nodes[index].RetrieveFromVert(vert, collider);
		}
	}

	for (auto f : facesCollider)
	{
		if (f.collider != collider) {
			result.push_back(f);
		}
	}

	return result;
}

std::vector<FaceCollider> OctoTree::RetrieveFromFace(Face face, ICollider* collider) {
	std::vector<FaceCollider> result;
	if (nodes.size() > 0) {
		int index = GetIndex(face);
		if (index > -1) {
			result = nodes[index].RetrieveFromFace(face, collider);
		}
	}

	for (auto f : facesCollider)
	{
		if (f.collider != collider) {
			result.push_back(f);
		}
	}

	return result;
}

void OctoTree::Clear()
{
	int size = nodes.size();
	for (int i = 0; i < size; i++)
		nodes[i].Clear();

	nodes.clear();

	verticesCollider.clear();
	facesCollider.clear();
}

void OctoTree::Insert(Face face, ICollider* collider) {
	int index = GetIndex(face);
	if (nodes.size() > 0) {
		if (index >= 0) {
			nodes[index].Insert(face, collider);
			return;
		}
	}
	else if (level == 0 && index == -1) {
		// The vertex is outside the root octree
		return;
	}

	facesCollider.push_back({ face, collider });

	if (facesCollider.size() > MAX_OBJECTS && level < MAX_LEVELS - 1) { // First level = 0
		Split();

		int size = facesCollider.size();
		for (int i = size - 1; i >= 0; i--) {
			int index = GetIndex(facesCollider[i].face);
			if (index != -1) {
				nodes[index].Insert(facesCollider[i].face, collider);
				facesCollider.erase(std::remove(facesCollider.begin(), facesCollider.end(), facesCollider[i]), facesCollider.end());
			}
		}
	}
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

	verticesCollider.push_back({vertex, collider});

	if (verticesCollider.size() > MAX_OBJECTS && level < MAX_LEVELS - 1) { // First level = 0
		Split();

		int size = verticesCollider.size();
		for (int i = size - 1; i >= 0; i--) {
			int index = GetIndex(verticesCollider[i].worldPosition);
			if (index != -1) {
				nodes[index].Insert(verticesCollider[i].worldPosition, collider);
				verticesCollider.erase(std::remove(verticesCollider.begin(), verticesCollider.end(), verticesCollider[i]), verticesCollider.end());
			}
		}
	}
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


int OctoTree::GetIndex(Face face) {

	if (face.vertices.size() > 0) {
		int index = GetIndex(face.vertices[0]);
		for (Vector3 v : face.vertices)
		{
			if (!(index == GetIndex(v)))
			{
				return -1;
			}
		}
		return index;
	}

	return -1;
}
