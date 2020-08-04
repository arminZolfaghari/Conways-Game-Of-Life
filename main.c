#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct cell
{
    int cur_value;
    int next_value;
};
typedef struct cell cell;


void shift_down(int size,int n,int *m,cell selool[2*size][2*size]);
void shift_right(int size,int *n,int m,cell selool[2*size][2*size]);
void print(int size,int n, int m, cell selool[2*size][2*size]);
int fcalculate(int size,int x,int y,int n, int m,cell selool[2*size][2*size]);
void fcheck(int size,int j,int i,int *n, int *m,int t,cell selool[2*size][2*size]);
void fgrowth(int size,int *n,int *m,cell selool[2*size][2*size]);
void FG(int size,int *n,int *m,cell selool[2*size][2*size]);

int main()
{
    int n , m , t;
    int x = 0 , y = 0 , size = 0;
    printf("Please enter N and T:\n");
    scanf("%d %d" , &n , &t);
    size = n;
    m = n;
    cell selool[2*n][2*n];

    int i , j;
    for (i = 0 ; i < 2 * n; i++)
        for (j = 0 ; j < 2 * n; j++)
        {
            selool[i][j].cur_value = 0;
            selool[i][j].next_value = 0;
        }

    printf("Please enter cells:\n(Coordinates outside the barrier result end of input)\n");

    while (x < n && y < n)
    {
        scanf("%d %d" , &x , &y);
        if (x >= n && y >= n)
            break;
        selool[y][x].cur_value = 1;
    }

    print(size,n,m,selool);
    Sleep(1000);
    FG(size,&n,&m,selool);
    fcheck(size,j,i,&n,&m,t,selool);
    return 0;
}


void print(int size,int n,int m,cell selool[2*size][2*size])
{
    int i , j;
    for (j = 0 ; j < m; j++)
    {
        for (i = 0 ; i < n ; i++)
        {
            if (selool[j][i].cur_value == 1 && i != n - 1)
                printf("|*");
            else if (selool[j][i].cur_value == 1 && i == n-1)
                printf("|*|");
            else if (selool[j][i].cur_value == 0 && i != n-1)
                printf("| ");
            else if (selool[j][i].cur_value== 0 && i == n-1)
                printf("| |");
        }
        printf("\n");
    }
    printf("\n=======================================================================================\n");
}


int fcalculate(int size,int x,int y,int n,int m,cell selool[2*size][2*size])
{
    int sum=0;
    if (x > 0 && y > 0)
            if (selool[y-1][x-1].cur_value == 1)
                sum++;
    if (y > 0)
        if (selool[y-1][x].cur_value == 1)
            sum++;
    if (y > 0 && x < m-1)
        if (selool[y-1][x+1].cur_value == 1)
            sum++;
    if (x > 0)
        if (selool[y][x-1].cur_value == 1)
            sum++;
    if (x < m-1)
        if (selool[y][x+1].cur_value == 1)
            sum++;
    if (x > 0 && y < n-1)
        if (selool[y+1][x-1].cur_value == 1)
            sum++;
    if (y < n-1)
        if (selool[y+1][x].cur_value == 1)
            sum++;
    if (y < n-1 && x < m-1)
        if (selool[y+1][x+1].cur_value == 1)
            sum++;
    return sum;
}
void shift_right(int size,int *n,int m,cell selool[2*size][2*size])
{
    *n+=1;
    int i,j;
    for(j=0;j<m;j++)
    {
        for(i=*n;i>=1;i--)
        {
            selool[j][i]=selool[j][i-1];
        }
    }
    for(j=0;j<m;j++)
    {
        selool[j][0].cur_value=0;
        selool[j][0].next_value=0;
    }
}
void shift_down(int size,int n,int *m,cell selool[2*size][2*size])
{
    *m+=1;
    int i,j;
    for(j=*m;j>=1;j--)
    {
        for(i=0;i<n;i++)
        {
            selool[j][i]=selool[j-1][i];
        }
    }
    for(i=0;i<n;i++)
    {
        selool[0][i].cur_value=0;
        selool[0][i].next_value=0;
    }
}
void fgrowth(int size,int *n,int *m,cell selool[2*size][2*size])
{
    int i;
    for (i=0;i<*n;i++)
    {
        if(selool[0][i].next_value == 1)
        {
            shift_down(size,*n,m,selool);
            break;
        }
    }
    for (i=0;i<*n;i++)
    {
        if(selool[(*m)-1][i].next_value == 1)
        {
            *m+=1;
            break;
        }
    }
    for (i=0;i<*m;i++)
    {
        if(selool[i][0].next_value == 1)
        {
            shift_right(size,n,*m,selool);
            break;
        }
    }
    for (i=0;i<*m;i++)
    {
        if(selool[i][(*n)-1].next_value == 1)
        {
            *n+=1;
            break;
        }
    }
}

void FG(int size,int *n,int *m,cell selool[2*size][2*size])
{
    int i;
    for (i=0;i<*n;i++)
    {
        if(selool[0][i].cur_value == 1)
        {
            shift_down(size,*n,m,selool);
            break;
        }
    }
    for (i=0;i<*n;i++)
    {
        if(selool[(*m)-1][i].cur_value == 1)
        {
            *m+=1;
            break;
        }
    }
    for (i=0;i<*m;i++)
    {
        if(selool[i][0].cur_value == 1)
        {
            shift_right(size,n,*m,selool);
            break;
        }
    }
    for (i=0;i<*m;i++)
    {
        if(selool[i][(*n)-1].cur_value == 1)
        {
            *n+=1;
            break;
        }
    }
}

void fcheck(int size,int j,int i,int *n,int *m,int t,cell selool[2*size][2*size])
{
    int k;
    for(k=1;k<=t;k++)
    {
        print(size,*n,*m,selool);
        for(j=0;j<*m;j++)
        {
            for(i=0;i<*n;i++)
            {
                int Condition = fcalculate(size,i,j,*n,*m,selool);
                if(selool[j][i].cur_value==1)
                {
                    if((Condition==2)||(Condition==3))
                    {
                        selool[j][i].next_value=1;
                    }
                    else
                    {
                        selool[j][i].next_value=0;
                    }
                }
                else
                {
                    if(Condition==3)
                    {
                        selool[j][i].next_value=1;
                    }
                    else
                    {
                        selool[j][i].next_value=0;
                    }
                }
            }
        }
        fgrowth(size,n,m,selool);
        for(j=0;j<*m;j++)
        {
            for(i=0;i<*n;i++)
            {
                selool[j][i].cur_value=selool[j][i].next_value;
                selool[j][i].next_value=0;
            }
        }
        Sleep(1000);
    }
}
