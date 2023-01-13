# Snake with Pathfinding
## The goal
The goal of this research was to compare different pathfinding algorithms used on the classic arcade game Snake.
The different types of pathfinding that i will be using are the AStar pathfinding algorithm and influence maps  

## Astar
### Introduction
AStar pathfinding uses a graph of nodes, where one node is the start and another is the goal.
The algorithm will start by making two lists, a closed list and an open list, the closed list are the nodes that have been checked and the open list consists of the nodes tat still need to be checked.  
First the startnode is added to the openlist and the closed list, then the algorithm loops over the openlist until it is empty.
In the start of each loop, the neighbours of the current node are added to the open list.
Each node is evaluated by 2 costs, the G-cost, which is the cost form the start node to the current node, and the H-cost, which is the estimated cost from the current node to the goal. We'll call the sum of these costs the F-cost.  
The algorithm will loop over all the neighbos and look for the neighbor with the lowest F-cost, this neighbor will be added to the closed list and his neighbors will be added to the open list.  
This will repeat until the open list is empty, if the goalnode is found, you have a path, but it is currently inverted. To get the final path, simply inverse the closedlist. If the goalnode isn't found, that means it is obstructed somehow and can't be reached.


### Pros
AStar is very good in the early stages of the game because it always finds the quickest way to the fruit
  
![AStar](https://user-images.githubusercontent.com/75164311/212279291-56c704e8-cbdf-47b3-9968-59b98a631af9.gif)

### Cons
The problem with AStar is that if the head of the snake is doesn't have a direct path to the fruit, it will most certaily run into it's own tail, therefore it will consitantly get medium scores, but never make it very far
  
![AStarCon](https://user-images.githubusercontent.com/75164311/212279673-9bdba194-8a80-4f10-b015-a5e56a5ad457.gif)


## Influence Maps
### Introduction
Influence maps use a grid or graph of the playfield and adds values or 'influences' in important areas, a positive influence for positive areas and a negative influence for negative areas. The influence spreads to the cells or nodes around it. The snake will always go to the area of the highest influence near the head.
The fruit will have a big positive influence, while the snake's tail and the walls will always have a big negative influence

### Problems during programming
-The influence of always only spreads to adjacent cells in a single update, so the graph has to be updated multiple times per fram.
-Because of the way the influence spreads, the point of origin of an influence will often have less influence than the cells around it, this causes the snake to not prioritize the apple. This was solved by increasing the influence of important points after the influence was updated.

### Pros
When the snake gets relatively close to the apple, he will always find it and never run into itself.

## Cons
When the snake is outisde of the apple's influence, it will often not find it.
When multiple cells have the same influence, the snake can get stuck in a loop.
  
![InfluenceMaps](https://user-images.githubusercontent.com/75164311/212280105-e24cd45f-b1bb-4037-bf6d-174cb4452b8b.gif)
