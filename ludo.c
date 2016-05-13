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
#define pcor(X) pf((X)==0?(ANSI_COLOR_RESET):((X)==1?(ANSI_COLOR_GREEN):((X)==2?(ANSI_COLOR_RED):((X)==3?(ANSI_COLOR_BLUE):(ANSI_COLOR_YELLOW)))))

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
    iNIPOS_X[2] = 12;
    iNIPOS_Y[2] = 12;
    iNIPOS_X[3] = 3;
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
    pf("|                       |   |   |   |                       | ");
    searchfor(15);ln;
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

void bmove(int plr, int blk)
{
    int xend[PNUM] = {0},
        yend[PNUM] = {0};
    xend[0]
}
