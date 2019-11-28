#include "../../Math/Vector3.h"
#include <vector>
#include "ICollider.h"

class OctoTree {
public:
	OctoTree(int _level, Vector3 _position, Vector3 _size);
	~OctoTree();

	/// <summary>
	/// Insert the object into the quadtree. If the node
	/// exceeds the capacity, it will split and add all
	/// objects to their corresponding nodes.
	/// </summary>
	void Insert(ICollider collider);

	/// <summary>
	/// Return all objects that could collide with the given object
	/// </summary>
	std::vector<ICollider> Retrieve(ICollider collider);

private:
	/// <summary>
	/// Clears the content
	/// </summary>
	void Clear();


	/// <summary>
	/// Splits the node into 8 subnodes
	/// </summary>
	void Split();

	/// <summary>
	/// Determine which node the object belongs to. -1 means
	/// object cannot completely fit within a child node and is part
	/// of the parent node
	/// </summary>
	std::vector<int> GetIndex(ICollider collider);


	const int MAX_OBJECTS = 10;
	const int MAX_LEVELS = 2;

	int level;
	Vector3 size;
	Vector3 position;
	std::vector<ICollider> objects;
	std::vector<OctoTree> nodes;
};