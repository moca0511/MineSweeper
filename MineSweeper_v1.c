#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef enum tile_MODE{tile_NONE,tile_MINE,tile_MODE_MAX}tile_MODE;
typedef enum tile_STATE{tile_CLOSE,tile_OPEN,tile_FLAG,tile_STATE_MAX}tile_STATE;
typedef struct TILE
{
    int mode; //爆弾？空？
    int state;//空いてる？しまってる？
    int around;//周りの爆弾の数
}TILE;

#define MINE_MAX 50
#define X_MAX 20
#define Y_MAX 20

void Set_Tile_Mode(TILE BORD[Y_MAX][X_MAX]);
void Print_Play_Bord(TILE BORD[Y_MAX][X_MAX]);

int main(void){
    TILE PLAY_BORD[Y_MAX][X_MAX];
    int selected_Y,selected_X;
    int x,y;
    srand((unsigned int)time(NULL));
    Set_Tile_Mode(PLAY_BORD);
    Print_Play_Bord(PLAY_BORD);
    return 0;
}

void Print_Play_Bord(TILE BORD[Y_MAX][X_MAX]){
    int x,y;
    system("CLS");
    for(y=0;y<Y_MAX;y++){
        for(x=0;x<X_MAX;x++){
            printf("%2d",BORD[y][x].around);
        }
        putchar('\n');
    }
    putchar('\n');
    for(y=0;y<Y_MAX;y++){
        for(x=0;x<X_MAX;x++){
            printf("%2d",BORD[y][x].mode);
        }
        putchar('\n');
    }

}


void Set_Tile_Mode(TILE BORD[Y_MAX][X_MAX]){
    int x,y;
    int count;
    for(y=0;y<Y_MAX;y++){
        for(x=0;x<X_MAX;x++){
            BORD[y][x].mode=tile_NONE;
            BORD[y][x].state=tile_CLOSE;
            BORD[y][x].around=0;
        }
    }
    for(count=MINE_MAX;count>0;count--){
        x=rand()%X_MAX;
        y=rand()%Y_MAX;
        if(BORD[y][x].mode!=tile_MINE){
            BORD[y][x].mode=tile_MINE;
        }else{
            count++;
        }
    }
    for(y=0;y<Y_MAX;y++){
        for(x=0;x<X_MAX;x++){
            if(y-1>=0){
                BORD[y][x].around+=BORD[y-1][x].mode;
                if(x-1>=0){
                    BORD[y][x].around+=BORD[y-1][x-1].mode;
                }
                if(x+1<X_MAX){
                    BORD[y][x].around+=BORD[y-1][x+1].mode;
                }
            }
            if(y+1<Y_MAX){
                BORD[y][x].around+=BORD[y+1][x].mode;
                if(x-1>=0){
                    BORD[y][x].around+=BORD[y+1][x-1].mode;
                }
                if(x+1<X_MAX){
                    BORD[y][x].around+=BORD[y+1][x+1].mode;
                }
            }
            if(x-1>=0){
                BORD[y][x].around+=BORD[y][x-1].mode;
            }
            if(x+1<X_MAX){
                BORD[y][x].around+=BORD[y][x+1].mode;
            }
        }
    }
    return;
}