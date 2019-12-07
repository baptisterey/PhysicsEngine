#pragma once

#include "../../Math/Vector3.h"
#include <vector>
#include "CubeCollider.h"

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
	void Insert(Vector3 vertex);
	void Insert(Face face);

	/// <summary>
	/// Return all objects that could collide with the given object
	/// </summary>
	std::vector<Face> Retrieve(Vector3 vert);
	std::vector<Face> Retrieve(Face face);

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
	int GetIndex(Face face);


	const int MAX_OBJECTS = 10;
	const int MAX_LEVELS = 2;

	int level;
	Vector3 size;
	Vector3 position;
	std::vector<Vector3> vertexs; // vertexs located in the current node
	std::vector<Face> faces; // face located in the current node
	std::vector<OctoTree> nodes; // Subnodes
};