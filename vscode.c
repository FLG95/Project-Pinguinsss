#include "ncurses.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"


const int tilesSquare = 4;
const int l = 9; // y
const int c = 9; // x
const int pinguin_width = 2;
const int pinguin_height = 2;
const int height ;
const int width ;
const int startX = 0;
const int startY = 0;



typedef struct {

    char* name;
    int num;
    int tileX;
    int tilesY;

}Player;

typedef struct{

    int fish;
    int isTherePlayer;
    int isAlive;
    int posX;
    int posY;

}Tile;



typedef struct {
    int x;
    int y;
} PinguinCoords;


Player* createPlayers(){
    int n = 0, b = 0;
    unsigned long length;
    char name[100];

    Player* player;

    printf("How many players? between 2 and 6");
    scanf("%d", &n);

    while(n < 2 || n > 6){
        printf("between 2 and 6 please");
        scanf("%d", &n);
        if(b == 10) {
            printf("Too much try miss");
            exit(2);
        }
        b++;
    }

    player = malloc( n * sizeof(player));
    if(!player){
        exit(1);
    }


    for (int i = 0; i < n; ++i) {
        printf("Enter the name of the player %d", i+1);
        scanf("%s", name);
        length = strlen(name);

        player[i].name = malloc( length * sizeof(char));
        if(!player[i].name){
            exit(1);
        }
        player[i].name = name;
        player[i].num = i+1;
    }

    return player;

}

Tile creatTiles(int x, int y){

    Tile Tile;

    Tile.isAlive = 1;

    Tile.fish = (rand() % 3) + 1;

    Tile.isTherePlayer = 0;

    Tile.posX = x;
    Tile.posY = y;

    return Tile;
}

Tile** createBoard(int l, int c, int tilesSquare){

    Tile** board;

    board = malloc( c * sizeof(Tile*));
    if(!board){
        exit(2);
    }

    for (int i = 0; i < l; ++i) { // y
        board[i] = malloc( l * sizeof (Tile));
        if(!board[i]){
            exit(2);
        }
        for (int j = 0; j < c; ++j) { // x
            board[i][j] = creatTiles(j*tilesSquare, i*tilesSquare);
        }
    }

    return board;
}

WINDOW *createWindow(int height, int width, int startX, int startY){
    WINDOW *win = newwin(height, width, startX, startY);
    box(win , 0, 0);
    wrefresh(win);

    return win;
}


void printEmoji(int x, int y){ //affiche le pinguin
    move(x, y);
    printw("🐧");
    refresh();
}


void showTiles(){
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for(int i = 0; i < 11; i++){ //affiche la premiere colonne
        if(i == 0){
            printw("   #      #\n"); //tab-1 puis tab+2
        }
        else if(i == 10){
            printw("   #\n"); //tab-1
        }
        else if((i >= 4 && i < 7)){
            printw("   #     #\n"); //tab-1 puis tab+3
        }
        else{
            printw("#     #\n"); //tab+3
        }
    }
    attroff(COLOR_PAIR(1));
}

void showTile00(Tile tiles, int tilesSquareX, int tilesSquareY){

    move(tiles.posY, tiles.posX+3);
    printw("#");
}

void showTile0X(Tile tiles, int tilesSquare){

    int x;
    int y;

    move(tiles.posY, tiles.posX);

    for (int i = 0; i < tilesSquare; ++i) {// ligne
        for (int j = 0; j < tilesSquare; ++j) { // colone


        }

        refresh();
    }
}
void showTileY0(Tile tiles, int tilesSquare){

    int x;
    int y;

    move(tiles.posY, tiles.posX);

    for (int i = 0; i < tilesSquare; ++i) {// ligne
        for (int j = 0; j < tilesSquare; ++j) { // colone


        }

        refresh();
    }
}

void showTileYX(Tile tiles, int tilesSquare){

    int x;
    int y;

    move(tiles.posY, tiles.posX);

    for (int i = 0; i < tilesSquare; ++i) {// ligne
        for (int j = 0; j < tilesSquare; ++j) { // colone


        }

        refresh();
    }
}



void showIceFloe(){
    for(int i = 0; i < 1; i++){
        for(int j  = 0; j < 2; j++){
            showTiles();
        }
    }
}

void showBoard(Tile** board, WINDOW *window, int l, int c) {

    for (int i = 0; i < l; ++i) {  // ligne
        for (int j = 0; j < c; ++j) {  // colone
            if ((i % 2 == 1) && (j == 0)) {

            } else {
                if (i == 0) {
                    showTiles(board[i][j]);
                } else {
                    showTiles(board[i][j]);
                }
            }

        }
    }
}

void destroyWin(WINDOW *win){
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}




void makeWindow(){
    WINDOW* win;
    PinguinCoords p_coords;
    int startx = 0, starty = 0;

    int touch;

    initscr();
    start_color();
    cbreak(); // ??
    keypad(stdscr, TRUE);

    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw("Press echap to exit\n \n");
    refresh();
    attroff(COLOR_PAIR(1));
    curs_set(0); // desactive le curseur

    startx = (LINES - pinguin_height) / 2;
    starty = (COLS - pinguin_width) / 2;
    //printw("Press echap to exit");
    refresh();

    win = createWindow(pinguin_height, pinguin_width, startx, starty);
    showIceFloe();
    printEmoji(startx + pinguin_height / 2, starty + pinguin_width / 2);



    while((touch = getch()) != 27){
        switch(touch){
            case KEY_LEFT:
                if(starty > 0){ //verifie que le pinguin sort pas de l'écran
                    destroyWin(win);
                    win = createWindow(pinguin_height, pinguin_width, startx, starty--);
                    printEmoji(startx + pinguin_height / 2, starty + pinguin_width / 2);
                    p_coords.x = startx; //on met a jour les coordonnées du pinguin
                    p_coords.y = starty;
                }
                break;

            case KEY_RIGHT:
                if(starty < COLS - pinguin_width){ //verifie que le pinguin sort pas de l'écran
                    destroyWin(win);
                    win = createWindow(pinguin_height, pinguin_width, startx, starty++);
                    printEmoji(startx + pinguin_height / 2, starty + pinguin_width / 2);
                    p_coords.x = startx; //on met a jour les coordonnées du pinguin
                    p_coords.y = starty;
                }
                break;

            case KEY_UP:
                if(startx > 0){ //verifie que le pinguin sort pas de l'écran
                    destroyWin(win);
                    win = createWindow(pinguin_height, pinguin_height, startx--, starty);
                    printEmoji(startx + pinguin_height / 2, starty + pinguin_width / 2);
                    p_coords.x = startx; //on met a jour les coordonnées du pinguin
                    p_coords.y = starty;
                }
                break;

            case KEY_DOWN:
                if(startx < LINES - pinguin_height){ //verifie que le pinguin sort pas de l'écran
                    destroyWin(win);
                    win = createWindow(pinguin_height, pinguin_width, startx++, starty);
                    printEmoji(startx + pinguin_height / 2, starty + pinguin_width / 2);
                    p_coords.x = startx; //on met a jour les coordonnées du pinguin
                    p_coords.y = starty;
                }
                break;
        }
    }
    endwin();
}




int main(){

    Tile** board = NULL;
    Player* players;
    WINDOW* window;

    srand(time(NULL));

    //makeWindow();

    players = createPlayers();

    board = createBoard(l, c, tilesSquare);

    showBoard(board, l, c);


    //checkfish = checkFish(board, players);

    //showBoard(board, window);
    //showScore(players);




    //free(players);
    //free(board);
    return 0;

}