#include "Path.h"
#include <queue>
#include <iostream>;

using namespace std;
Path::Path(Vector start, Vector target)
{
	this->currentPos = start;
	this->targetPos = target;
	initMap();
	generatePath();
}

void Path::initMap() {
	for (int x = 0; x < n; x++)
		for (int z = 0; z < m; z++)
			map[x][z] = 0;
}
std::vector<Vector> Path::getPath() {
	return path;
}
void Path::generatePath() {
	priority_queue<node, std::vector<node>, LessThan> pq[2];
	int pqi;//pqindex
	node* n0;
	node* m0;
	int i, j, x, z, xdx, zdz;
	pqi = 0;

	for (z = 0; z < m; z++) {
		for (x = 0; x < n; x++) {
			closed_nodes_map[x][z] = 0;
			open_nodes_map[x][z] = 0;
		}
	}

	n0 = new node(currentPos.getX(), currentPos.getZ(), 0, 0);
	n0->updatePriority(targetPos.getX(), targetPos.getZ());
	pq[pqi].push(*n0);
	open_nodes_map[x][z] = n0->getPriority();

	while (!pq[pqi].empty()) {
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getzPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());
		x = n0->getxPos(); z = n0->getzPos();

		pq[pqi].pop();
		open_nodes_map[x][z] = 0;
		closed_nodes_map[x][z] = 1;

		if (x == targetPos.getX() && z == targetPos.getZ()) {
			while (!(x == currentPos.getX() && z == currentPos.getZ())) {
				j = dir_map[x][z];
				path.push_back(Vector(x, 1, z));
				x += dx[j];
				z += dz[j];
			}
			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			
		}

		for (i = 0; i < dir; i++) {
			xdx = x + dx[i];
			zdz = z + dz[i];

			if (!(xdx < 0 || xdx > n - 1 || zdz < 0 || zdz > m - 1 || map[xdx][zdz] == 1 || closed_nodes_map[xdx][zdz] == 1)) {
				m0 = new node(xdx, zdz, n0->getLevel(), n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(targetPos.getX(), targetPos.getZ());

				if (open_nodes_map[xdx][zdz] == 0) {
					open_nodes_map[xdx][zdz] = m0->getPriority();
					pq[pqi].push(*m0);
					dir_map[xdx][zdz] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][zdz] > m0->getPriority()) {
					open_nodes_map[xdx][zdz] = m0->getPriority();
					dir_map[xdx][zdz] = (i + dir / 2) % dir;

					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getzPos() == zdz)) {
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();

					if (pq[pqi].size() > pq[1 - pqi].size())
						pqi = 1 - pqi;
					while (!pq[pqi].empty()) {
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0);
				}
				else delete m0;
			}
		}
		delete n0;
	}
	cout << "No path" << endl;
}

Path::~Path()
{
}
