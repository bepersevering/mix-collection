#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point { int row, col, predecessor;};

struct point queue[512];
int head = 0, tail = 0;

void enqueue(struct point p) {
  queue[tail] = p;
  tail++;
}

struct point dequeue(void) {
  head++;
  return queue[head-1];
}

int isEmpty(void) {
  return head == tail;
}

int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0}
};

void printMaze(void) {
  int i, j;
  for (i = 0; i < MAX_ROW; i++) {
    for (j = 0; j < MAX_COL; j++) {
      printf("%d ", maze[i][j]);
    }
    putchar('\n');
  }
  printf("****************\n");
}

void visit(int row, int col) {
  struct point visit_point = {row, col, head - 1};
  maze[row][col] = 2;
  enqueue(visit_point);
}

int main(void) {
  struct point p = {0, 0, -1};
  maze[p.row][p.col] = 2;
  enqueue(p);

  while (!isEmpty()) {
    p = dequeue();
    // goal
    if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
      break;
    }

    // right
    if (p.col + 1 < MAX_COL && maze[p.row][p.col+1] == 0) {
      visit(p.row, p.col +1);
    }

    // down
    if (p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0) {
      visit(p.row+1, p.col);
    }

    // left
    if (p.col-1 >= 0 && maze[p.row][p.col-1] == 0) {
      visit(p.row, p.col-1);
    }

    // up
    if (p.row-1 >= 0 && maze[p.row-1][p.col] == 0) {
      visit(p.row-1, p.col);
    }
    printMaze();
  }

  if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
    // printPath(p);
    // printf("(%d, %d)\n", p.row, p.col);

    printf("(%d, %d)\n", p.row, p.col);
    while (p.predecessor != -1) {
      p = queue[p.predecessor];
      printf("(%d, %d)\n", p.row, p.col);
    }
  } else {
    printf("No path!\n");
  }

  return 0;
}
