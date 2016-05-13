#include <stdlib.h>
#include <stdio.h>

#define pf(X) printf((X))
#define ln printf("\n")
#define PNUM 4
#define BNUM 4
#define MAPSIZE 15
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define pcor(X) pf((X)==0?(ANSI_COLOR_RESET):((X)==1?(ANSI_COLOR_RED):((X)==2?(ANSI_COLOR_GREEN):((X)==3?(ANSI_COLOR_BLUE):(ANSI_COLOR_YELLOW)))))
#define pclr(X) pf((X)==0?(ANSI_COLOR_RESET):((X)==1?(ANSI_COLOR_GREEN):((X)==2?(ANSI_COLOR_RED):((X)==3?(ANSI_COLOR_BLUE):(ANSI_COLOR_YELLOW)))))
#define ABS(X) ((X)>0?((X)):(-(X)))

int iNIPOS_X[BNUM],
    iNIPOS_Y[BNUM];

typedef struct st_block
{
    unsigned x,
             y,
             end;
}block;
typedef struct st_player
{
    block b[BNUM];
}player;

player p[PNUM];

void printmap(void);
void searchfor(unsigned y);
void bmove(int plr, int blk);

int main(void)
{
    unsigned i, j;
    unsigned px = 1, py = 0;
    iNIPOS_X[0] = 12;
    iNIPOS_Y[0] = 3;
    iNIPOS_X[1] = 3;
    iNIPOS_Y[1] = 3;
    iNIPOS_X[2] = 3;
    iNIPOS_Y[2] = 12;
    iNIPOS_X[3] = 12;
    iNIPOS_Y[3] = 12;
    for(i=0;i<PNUM;i++)
        for(j=0;j<BNUM;j++)
        {
            px ^= 1;
            if(px) py ^= 1;
            p[i].b[j].x = iNIPOS_X[i] + px;
            p[i].b[j].y = iNIPOS_Y[i] + py;
            p[i].b[j].end = 0;
        }
    printmap();

    unsigned a;
    pf("Select Player:\n");
    pclr(1);pf("Player 1\n");pclr(0);
    pclr(2);pf("Player 2\n");pclr(0);
    pclr(3);pf("Player 3\n");pclr(0);
    pclr(4);pf("Player 4\n");pclr(0);
    pf(">>");
    scanf("%u", &a);
    a--;
    bmove(a,0);
    printmap();
    do
    {
        pf("Select the number of steps your pawn will take. (0 to exit)\n>>");
        scanf("%u", &i);
        for(j=0;j<i;j++)
            bmove(a,0);
        printmap();
    }while(i);
    return 0;
}

void printmap(void)
{
    pf(".-----------------------.---.---.---.-----------------------. ");ln;
    pf("|                       |   |   |   |                       | ");searchfor(1);ln;
    pf("|                       |---");pcor(1);pf("+---+---.");pcor(0);pf("                       | ");ln;
    pf("|                       |   ");pcor(1);pf("|   |   |");pcor(0);pf("                       | ");searchfor(2);ln;
    pf("|       --- ---         |---");pcor(1);pf("+---+---.");pcor(0);pf("       --- ---         | ");ln;
    pf("|      |   |   |        |   ");pcor(1);pf("|   |");pcor(0);pf("   |      |   |   |        | ");searchfor(3);ln;
    pf("|       ---+---         |---");pcor(1);pf("+---+");pcor(0);pf("---|       ---+---         | ");ln;
    pf("|      |   |   |        |   ");pcor(1);pf("|   |");pcor(0);pf("   |      |   |   |        | ");searchfor(4);ln;
    pf("|       --- ---         |---");pcor(1);pf("+---+");pcor(0);pf("---|       --- ---         | ");ln;
    pf("|                       |   ");pcor(1);pf("|   |");pcor(0);pf("   |                       | ");searchfor(5);ln;
    pf("|                       |---");pcor(1);pf("+---+");pcor(0);pf("---|                       | ");ln;
    pf("|                       |   ");pcor(1);pf("|   |");pcor(0);pf("   |                       | ");searchfor(6);ln;
    pf("|---");pcor(2);pf(".---.");pcor(0);pf("---.---.---.---+---");pcor(1);pf("+---+");pcor(0);pf("---+---.---.---.---.---.---| ");ln;
    pf("|   ");pcor(2);pf("|   |");pcor(0);pf("   |   |   |   |   ");pcor(1);pf("|   |");pcor(0);pf("   |   |   |   |   |   |   | ");searchfor(7);ln;
    pf("|---");pcor(2);pf("+---+---+---+---+---+---");pcor(0);pf("+");pcor(1);pf("---");pcor(0);pf("+");pcor(3);pf("---+---+---+---+---+---+");pcor(0);pf("---| ");ln;
    pf("|   ");pcor(2);pf("|   |   |   |   |   |   |");pcor(3);pf("   |   |   |   |   |   |   |");pcor(0);pf("   | ");searchfor(8);ln;
    pf("|---");pcor(2);pf("+---+---+---+---+---+---");pcor(0);pf("+");pcor(4);pf("---");pcor(0);pf("+");pcor(3);pf("---+---+---+---+---+---+");pcor(0);pf("---| ");ln;
    pf("|   |   |   |   |   |   |   ");pcor(4);pf("|   |");pcor(0);pf("   |   |   |   |   ");pcor(3);pf("|   |");pcor(0);pf("   | ");searchfor(9);ln;
    pf("|---^---^---^---^---^---+---");pcor(4);pf("+---+");pcor(0);pf("---+---^---^---^---");pcor(3);pf(".---.");pcor(0);pf("---| ");ln;
    pf("|                       |   ");pcor(4);pf("|   |");pcor(0);pf("   |                       | ");searchfor(10);ln;
    pf("|                       |---");pcor(4);pf("+---+");pcor(0);pf("---|                       | ");ln;
    pf("|                       |   ");pcor(4);pf("|   |");pcor(0);pf("   |                       | ");searchfor(11);ln;
    pf("|       --- ---         |---");pcor(4);pf("+---+");pcor(0);pf("---|       --- ---         | ");ln;
    pf("|      |   |   |        |   ");pcor(4);pf("|   |");pcor(0);pf("   |      |   |   |        | ");searchfor(12);ln;
    pf("|       ---+---         |---");pcor(4);pf("+---+");pcor(0);pf("---|       ---+---         | ");ln;
    pf("|      |   |   |        |   ");pcor(4);pf("|   |");pcor(0);pf("   |      |   |   |        | ");searchfor(13);ln;
    pf("|       --- ---         ");pcor(4);pf(".---+---+");pcor(0);pf("---|       --- ---         | ");ln;
    pf("|                       ");pcor(4);pf("|   |   |");pcor(0);pf("   |                       | ");searchfor(14);ln;
    pf("|                       ");pcor(4);pf(".---+---+");pcor(0);pf("---|                       | ");ln;
    pf("|                       |   |   |   |                       | ");searchfor(15);ln;
    pf("^-----------------------^---^---^---^-----------------------^ ");ln;
    return;
}

void searchfor(unsigned y)
{
    int i, j;
    int map[MAPSIZE+1] = {0};
    for(i=0;i<PNUM;i++)
        for(j=0;j<BNUM;j++)
            if(p[i].b[j].x != 0 && p[i].b[j].y == y)
                map[p[i].b[j].x] = i+1;
    for(i=MAPSIZE;i>0;i--)
    {
        for(j=0;j<4;j++)
            pf("\b");
        if(map[i])
        {
            pf("\b");
            pcor(map[i]);
            pf("O");
            pcor(0);
        }
    }
    return;
}

/* 
 * Player 1: GREEN
 * Player 2: RED 
 * Player 3: BLUE 
 * Player 4: YELOW
 * */
void bmove(int plr, int blk)
{
    int xend[PNUM] = {0},
        yend[PNUM] = {0},
        i,
        j,
        xi,
        yi,
        ei;
    xend[0] = 2;
    yend[0] = 7;
    xend[1] = 9;
    yend[1] = 2;
    xend[2] = 14;
    yend[2] = 9;
    xend[3] = 7;
    yend[3] = 14;

    xi = p[plr].b[blk].x;
    yi = p[plr].b[blk].y;
    ei = p[plr].b[blk].end;
    if(((8-xi) == 0 && ABS(8-yi) == 1) ||(ABS(8-xi) == 1 && (8-yi) == 0))
    {
        printf("ERROR: attempting to call bmove(%u,%u) with the pawn already at the center!!\n",plr,blk);
        return;
    }

    /* If block is inside the end lane */
    if(ei == 2)
    {
        if((8-xi) > 0)
            p[plr].b[blk].x++;
        if((8-xi) < 0)
            p[plr].b[blk].x--;
        if((8-yi) > 0)
            p[plr].b[blk].y++;
        if((8-yi) < 0)
            p[plr].b[blk].y--;
        xi = p[plr].b[blk].x;
        yi = p[plr].b[blk].y;
        printf("Only %d spaces left!!!\n",ABS(16-yi-xi)-1);
        if(ABS(16-yi-xi) == 1)
            printf("Player %u reached the center with one pawn!\n",plr);
        return;
    }
    /* If block is passing by the origin for the second time - UNDER CONSTRUCTION*/
    if(xi == xend[plr] && yi == yend[plr] && ei == 1)
    {
        p[plr].b[blk].end++;
        switch(plr)
        {
            case 0:
                p[plr].b[blk].x = 2;
                p[plr].b[blk].y = 8;
                break;
            case 1:
                p[plr].b[blk].x = 8;
                p[plr].b[blk].y = 2;
                break;
            case 2:
                p[plr].b[blk].x = 14;
                p[plr].b[blk].y = 8;
                break;
            case 3:
                p[plr].b[blk].x = 8;
                p[plr].b[blk].y = 14;
                break;
        }
        return;
    }
    /* If block is passing by the origin for the first time*/
    if(xi == xend[plr] && yi == yend[plr] && ei == 0)
        p[plr].b[blk].end++;
    /* If block is in graveyard */
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            if((xi == iNIPOS_X[plr] + i) && (yi == iNIPOS_Y[plr] + j))
            {
                p[plr].b[blk].x = xend[plr];
                p[plr].b[blk].y = yend[plr];
                return;
            }
    /* If block is in a corner */
    /* UR Corner */
    if(xi == 9 && yi == 1)
    {
        p[plr].b[blk].y++;
        return;
    }
    /* UL Corner */
    if((xi == 7 || xi == 8) && yi == 1)
    {
        p[plr].b[blk].x++;
        return;
    }
    /* RU Corner */
    if(xi == 1 && yi == 7)
    {
        p[plr].b[blk].x++;
        return;
    }
    /* RD Corner */
    if(xi == 1 && (yi == 9 || yi == 8))
    {
        p[plr].b[blk].y--;
        return;
    }
    /* DL Corner */
    if(xi == 7 && yi == 15)
    {
        p[plr].b[blk].y--;
        return;
    }
    /* DR Corner */
    if((xi == 9 || xi == 8) && yi == 15)
    {
        p[plr].b[blk].x--;
        return;
    }
    /* LD Corner */
    if(xi == 15 && yi == 9)
    {
        p[plr].b[blk].x--;
        return;
    }
    /* LU Corner */
    if(xi == 15 && (yi == 7 || yi == 8))
    {
        p[plr].b[blk].y++;
        return;
    }

    /* Corner 1 (6,7) -> (7,6)*/
    if(xi == 6 && yi == 7)
    {
        p[plr].b[blk].x = 7;
        p[plr].b[blk].y = 6;
        return;
    }
    /* Corner 2 (9,6) -> (10,7)*/
    if(xi == 9 && yi == 6)
    {
        p[plr].b[blk].x = 10;
        p[plr].b[blk].y = 7;
        return;
    }
    /* Corner 3 (10,9) -> (9,10)*/
    if(xi == 10 && yi == 9)
    {
        p[plr].b[blk].x = 9;
        p[plr].b[blk].y = 10;
        return;
    }
    /* Corner 4 (7,10) -> (6,9)*/
    if(xi == 7 && yi == 10)
    {
        p[plr].b[blk].x = 6;
        p[plr].b[blk].y = 9;
        return;
    }
    /* General movement rules*/
    /* Upwards (7,y) -> (7,y-1)*/
    if(xi == 7)
    {
        p[plr].b[blk].y--;
        return;
    }
    /* Downwards (9,y) -> (9,y+1)*/
    if(xi == 9)
    {
        p[plr].b[blk].y++;
        return;
    }
    /* Rightwards (x,7) -> (x-1,7)*/
    if(yi == 7)
    {
        p[plr].b[blk].x++;
        return;
    }
    /* Leftwards (x,9) -> (x+1,9)*/
    if(yi == 9)
    {
        p[plr].b[blk].x--;
        return;
    }
}
