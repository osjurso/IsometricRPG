
#ifndef ISORPG_PATHFINDING_H
#define ISORPG_PATHFINDING_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <include/components/Comp_State.h>
#include <include/components/PathfindingNode.h>


class PathFiding : anax::System<anax::Requires<PositionComponent, SizeComponent>> {
    const int n; // horizontal size of the map
    const int m; // vertical size size of the map
    static int map[n][m];
    static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
    static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
    static int dir_map[n][m]; // map of directions
    static int dx[dir]={1, 0, -1, 0};
    static int dy[dir]={0, 1, 0, -1};
public:
    PathFiding(int whith, int height) : n(whith), m(height)
    {}

    std::string findPath(const int &xStart, const int &yStart,
                         const int &xFinish, const int &yFinish) {
        static std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
        static int pqi; // pq index
        static node *n0;
        static node *m0;
        static int i, j, x, y, xdx, ydy;
        static char c;
        pqi = 0;

        // reset the node maps
        for (y = 0; y < m; y++) {
            for (x = 0; x < n; x++) {
                closed_nodes_map[x][y] = 0;
                open_nodes_map[x][y] = 0;
            }
        }

        // create the start node and push into list of open nodes
        n0 = new node(xStart, yStart, 0, 0);
        n0->updatePriority(xFinish, yFinish);
        pq[pqi].push(*n0);
        open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map

        // A* search
        while (!pq[pqi].empty()) {
            // get the current node w/ the highest priority
            // from the list of open nodes
            n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                          pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

            x = n0->getxPos();
            y = n0->getyPos();

            pq[pqi].pop(); // remove the node from the open list
            open_nodes_map[x][y] = 0;
            // mark it on the closed nodes map
            closed_nodes_map[x][y] = 1;

            // quit searching when the goal state is reached
            //if((*n0).estimate(xFinish, yFinish) == 0)
            if (x == xFinish && y == yFinish) {
                // generate the path from finish to start
                // by following the directions
                std::string path = "";
                while (!(x == xStart && y == yStart)) {
                    j = dir_map[x][y];
                    c = '0' + (j + dir / 2) % dir;
                    path = c + path;
                    x += dx[j];
                    y += dy[j];
                }

                // garbage collection
                delete n0;
                // empty the leftover nodes
                while (!pq[pqi].empty()) pq[pqi].pop();
                return path;
            }

            // generate moves (child nodes) in all possible directions
            for (i = 0; i < dir; i++) {
                xdx = x + dx[i];
                ydy = y + dy[i];

                if (!(xdx < 0 || xdx > n - 1 || ydy < 0 || ydy > m - 1 || map[xdx][ydy] == 1
                      || closed_nodes_map[xdx][ydy] == 1)) {
                    // generate a child node
                    m0 = new node(xdx, ydy, n0->getLevel(),
                                  n0->getPriority());
                    m0->nextLevel(i);
                    m0->updatePriority(xFinish, yFinish);

                    // if it is not in the open list then add into that
                    if (open_nodes_map[xdx][ydy] == 0) {
                        open_nodes_map[xdx][ydy] = m0->getPriority();
                        pq[pqi].push(*m0);
                        // mark its parent node direction
                        dir_map[xdx][ydy] = (i + dir / 2) % dir;
                    } else if (open_nodes_map[xdx][ydy] > m0->getPriority()) {
                        // update the priority info
                        open_nodes_map[xdx][ydy] = m0->getPriority();
                        // update the parent direction info
                        dir_map[xdx][ydy] = (i + dir / 2) % dir;

                        // replace the node
                        // by emptying one pq to the other one
                        // except the node to be replaced will be ignored
                        // and the new node will be pushed in instead
                        while (!(pq[pqi].top().getxPos() == xdx &&
                                 pq[pqi].top().getyPos() == ydy)) {
                            pq[1 - pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
                        pq[pqi].pop(); // remove the wanted node

                        // empty the larger size pq to the smaller one
                        if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
                        while (!pq[pqi].empty()) {
                            pq[1 - pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
                        pqi = 1 - pqi;
                        pq[pqi].push(*m0); // add the better node instead
                    } else delete m0; // garbage collection
                }
            }
            delete n0; // garbage collection
        }
        return ""; // no route found
    }
};

#endif //ISORPG_PATHFINDING_H
