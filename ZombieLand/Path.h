#pragma once
#include "Vector.h"
#include <vector>
#include <algorithm>
class Path
{
public:
	Path(Vector start, Vector target);
	
	std::vector<Vector> getPath();
	~Path();
private:
	void generatePath();
	void initMap();
	const int n = 60;
	const int m = 80;
	static const int dir = 8;
	Vector currentPos;
	Vector targetPos;
	int map[60][80];
	int open_nodes_map[60][80];
	int closed_nodes_map[60][80];
	int dir_map[60][80];
	int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
	int dz[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	std::vector<Vector> path;
	
	class node
	{
		float xPos, zPos;
		float level, priority;

	public:
		node(float xp, float zp, float d, float p) {
			xPos = xp; zPos = zp; level = d; priority = p;
		}
		float getxPos() const { return xPos; }
		float getzPos() const { return zPos; }
		float getLevel() const { return level; }
		float getPriority() const { return priority; }

		void updatePriority(const float &xDest, const float &zDest) {
			priority = level + estimate(xDest, zDest) * 10;
		}

		void nextLevel(const int &i) {
			level += (dir==8?(i%2==0?10:14):10);
		}

		const float & estimate(const int &xDest, const int &zDest) const {
			float xd, zd;
			xd = xDest - xPos;
			zd = zDest - zPos;
			return static_cast<int>(sqrt(xd*xd + zd*zd));
		}
	};

	struct LessThan
	{
		bool operator()(const node & a, const node & b) const
		{
			return a.getPriority() > b.getPriority();
		}
	};
};

