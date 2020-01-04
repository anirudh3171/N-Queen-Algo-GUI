#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<graphics.h>

#define TRUE 1
#define FALSE 0
#define MAXBOARDSIZE 11
#define BLOCKSIZE 40

int board[MAXBOARDSIZE];
int n; //n is boardsize

void DrawBoard()
{
    int x1, y1, x2, y2, i;

    x1=30, y1=30, y2=30+n*BLOCKSIZE;
    cleardevice();
    setcolor(WHITE);
   for(i=0; i<=n; i++)
    {
       line(x1, y1, x1, y2);
       x1 = x1+ BLOCKSIZE;
    }

    x1=30, y1=30, x2=30+n*BLOCKSIZE;
    for(i=0; i<=n; i++)
    {
       line(x1, y1, x2, y1);
       y1 += BLOCKSIZE;
    }
}

void DrawQueen(int x, int y)
{
    int midx=x+BLOCKSIZE/2, midy=y+10;
    setcolor(RED);
    pieslice(midx, midy, 250, 290, 20);
    pieslice(midx-8, midy+4, 258, 282, 16);
    pieslice(midx+8, midy+4, 258, 282, 16);
}

void DisplaySolution()
{
    int i, k, x, y=30;
    static int solno=1;
    char str[20];

    cleardevice();
    sprintf(str, "Solution %d:", solno++);

    DrawBoard();
    outtextxy(4, 4, str);

    for (i = 0; i < n; i++)
    {
        x=30;
        for (k=0; k<board[i]; k++)
            x += BLOCKSIZE;
        DrawQueen(x, y);
        y += BLOCKSIZE;
    }
    getch();
}

int IsPlaceSafe(int row, int col)
{
    int i;

    for(i=0; i<row; i++)
    {
        if( (board[i] == col) || (abs(board[i]-col) == abs(i-row)) )
            return FALSE;
    }
    return TRUE;
}

void NQueens(int row)
{
    int col;

    for(col=0; col<n; col++)
    {
        if(IsPlaceSafe(row, col))
        {
            board[row] = col;
            if(row == n-1)
                {DisplaySolution();
                return;}
            if(row<n)
                NQueens(row+1);
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    cleardevice();
    printf("Enter board size: ");
    scanf("%d", &n);
    if(n>MAXBOARDSIZE) exit(1);

    NQueens(0);

    closegraph();
    return 0;
}
