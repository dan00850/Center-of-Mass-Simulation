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

// the function which is used to draw circle in the window
void draw_circle(int x, int y,Windoww * window,int color);

// The function used to check if user click into the reload botton
bool check_reload1();

/* The function which is used to create window*/
Windoww  Create_game();

/*The function which is used to find the center of the object which is created by user*/
void Find_center_of_mass(int add,int x,int y, Windoww * window);

/* The function used to rotate the square*/
void rotateSquare(Windoww *window, int x ,int y,int cen_x,int cen_y ,double cos_alpha,double sin_alpha);

/*Function rotate an alpha angle the object around the cen_x, cen_y axit*/
void rotate(int cen_x,int cen_y,Windoww * window, double cos_alpha,double sin_alpha);

/*Function rotate the object physically*/
void SmoothRotate(int x,int y, Windoww * window);

/*Function drop the object if the nail does not pin to the object*/
void Drop_the_object(Windoww * window,int drop_change);

/*Function make action based on user's action*/
void action(int x ,int y,Windoww * window);

/*Function take input from user*/
void Take_input_from_user(Windoww * window);

#endif
