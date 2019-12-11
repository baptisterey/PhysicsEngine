#pragma once
#include "../../Math/Vector3.h"

#include <iostream> 
#include <vector> 


class ICollider;

class OctoTree {
public:

	/// <summary>
	/// Constructor
	/// </summary>
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
	/// Return all objects that could collide with the given object based on the zone of the octotree wanted
	/// </summary>
	std::vector<ICollider*> Retrieve(Vector3 vert, ICollider* collider, bool top = true, bool left = true, bool bottom = true, bool right = true, bool front = true, bool back = true);

	// --- STATIC COLLIDERS THAT REPRESENT THE PLANE OF THE BOX ---
	static ICollider* LEFT_PLANE_COLLIDER;
	static ICollider* RIGHT_PLANE_COLLIDER;
	static ICollider* BOTTOM_PLANE_COLLIDER;
	static ICollider* TOP_PLANE_COLLIDER;
	// ------------------------------------------------------------

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
	/// How many objects can we store on one node, if we exceed this we split the node in sub-nodes
	/// </summary>
	const int MAX_OBJECTS = 1;

	/// <summary>
	/// How many levels can the octotree handle
	/// </summary>
	const int MAX_LEVELS = 25;


	int level;

	Vector3 size;
	Vector3 position;

	std::vector<Vector3> vertices; // vertices located in the current node
	std::vector<OctoTree> nodes; // Subnodes
};