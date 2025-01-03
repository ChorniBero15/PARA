#include "graph_of_life.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

void NodesInit(int num_nodes);
void NodesDestroy();
void SetNeighbors(int id, int k, int* n);

int main(int argc, char** argv) {
  NodesInit(5);
  int n0[] = {1, 2, 4};
  int n1[] = {0, 3};
  int n2[] = {0, 3, 4};
  int n3[] = {1, 2};
  int n4[] = {0, 2};

  SetNeighbors(0, 3, n0);
  SetNeighbors(1, 2, n1);
  SetNeighbors(2, 3, n2);
  SetNeighbors(3, 2, n3);
  SetNeighbors(4, 2, n4);

  SetIsAlive(0, true);
  SetIsAlive(1, false);
  SetIsAlive(2, false);
  SetIsAlive(3, true);
  SetIsAlive(4, false);

  SimulateGraphOfLife(4, 3);
  printf("DOOONE\n");
  NodesDestroy();
  return 0;
}
