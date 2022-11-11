#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point {
  int row;
  int col;
};

struct point stack[512];

int top = 0;

void push(struct point p) {
  stack[top] = p;
  top++;
}

struct point pop(void) {
  top--;
  return stack[top];
};

int isEmpty(void) {
  return top == 0;
}

int maze[MAX_ROW][MAX_COL] = {
  0, 1, 0, 0, 0,
  0, 1, 0, 1, 0,
  0, 0, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
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

struct point predecessor[MAX_ROW][MAX_COL] = {
  {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}},
  {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}},
  {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}},
  {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}},
  {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}},
};

void visit(int row, int col, struct point pre) {
  struct point visit_point = {row, col};
  maze[row][col] = 2;
  predecessor[row][col] = pre;
  push(visit_point);
}

void printPath(struct point p) {
  if (predecessor[p.row][p.col].row != -1) {
    p = predecessor[p.row][p.col];
    printPath(p);
    printf("(%d, %d)\n", p.row, p.col);
  }
  
}

int main(void) {
  struct point p = {0, 0};
  maze[p.row][p.col] = 2;
  push(p);

  while (!isEmpty()) {
    p = pop();
    // goal
    if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
      break;
    }

    // right
    if (p.col + 1 < MAX_COL && maze[p.row][p.col+1] == 0) {
      visit(p.row, p.col +1, p);
    }

    // down
    if (p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0) {
      visit(p.row+1, p.col, p);
    }

    // left
    if (p.col-1 >= 0 && maze[p.row][p.col-1] == 0) {
      visit(p.row, p.col-1, p);
    }

    // up
    if (p.row-1 >= 0 && maze[p.row-1][p.col] == 0) {
      visit(p.row-1, p.col, p);
    }
    printMaze();
  }

  if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
    printPath(p);
    printf("(%d, %d)\n", p.row, p.col);
    // printf("(%d, %d)\n", p.row, p.col);
    // while (predecessor[p.row][p.col].row != -1) {
    //   p = predecessor[p.row][p.col];
    //   printf("(%d, %d)\n", p.row, p.col);
    // }
  } else {
    printf("No path!\n");
  }

  return 0;
}
