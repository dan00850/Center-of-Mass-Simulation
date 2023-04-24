#ifndef GAME_H_
#define GAME_H_
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>


//Create a struct to create a window
struct Windoww{
    SDL_Window* window;
    SDL_Renderer* renderer;
};
typedef struct Windoww Windoww;

void draw_circle(int x, int y,Windoww * window,int color);
bool check_reload1();
Windoww  Create_game();
void Find_center_of_mass(int add,int x,int y, Windoww * window);
void rotateSquare(Windoww *window, int x ,int y,int cen_x,int cen_y ,double cos_alpha,double sin_alpha);
void rotate(int cen_x,int cen_y,Windoww * window, double cos_alpha,double sin_alpha);
void Take_input_from_user(Windoww * window);

#endif
