#pragma once
#include "../../Math/Vector3.h"

#include <iostream> 
#include <vector> 

class Face;
class ICollider;

struct VertexCollider; 
struct FaceCollider;

class OctoTree {
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_level"></param>
	/// <param name="_position"></param>
	/// <param name="_size"></param>
	OctoTree(int _level, Vector3 _position, Vector3 _size);

	/// <summary>
	/// Destructor
	/// </summary>
	~OctoTree();

	/// <summary>
	/// Clears the content
	/// </summary>
	void Clear();

	/// <summary>
	/// Insert the object into the quadtree. If the node
	/// exceeds the capacity, it will split and add all
	/// objects to their corresponding nodes.
	/// </summary>
	void Insert(Vector3 vertex, ICollider* collider);

	/// <summary>
	/// Insert the object into the quadtree. If the node
	/// exceeds the capacity, it will split and add all
	/// objects to their corresponding nodes.
	/// </summary>
	void Insert(Face face, ICollider* collider);

	/// <summary>
	/// Return all objects that could collide with the given object
	/// </summary>
	std::vector<FaceCollider> RetrieveFromVert(Vector3 vert, ICollider* collider);

	/// <summary>
	/// Return all objects that could collide with the given object
	/// </summary>
	std::vector<FaceCollider> RetrieveFromFace(Face face, ICollider* collider);

private:
	/// <summary>
	/// Splits the node into 8 subnodes
	/// </summary>
	void Split();

	/// <summary>
	/// Determine which node the object belongs to. -1 means
	/// object cannot completely fit within a child node and is part
	/// of the parent node
	/// </summary>
	int GetIndex(Vector3 vertex);

	/// <summary>
	/// Determine which node the object belongs to. -1 means
	/// object cannot completely fit within a child node and is part
	/// of the parent node
	/// </summary>
	int GetIndex(Face face);

	const int MAX_OBJECTS = 5;
	const int MAX_LEVELS = 10;

	int level;

	Vector3 size;
	Vector3 position;

	std::vector<VertexCollider> verticesCollider; // vertices located in the current node
	std::vector<FaceCollider> facesCollider; // face located in the current node

	std::vector<OctoTree> nodes; // Subnodes
};