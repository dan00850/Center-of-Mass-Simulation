#include "game.h"
#include<stdio.h>
#include<SDL2/SDL.h>
#include <stdio.h>

int SDL_main(int argc, char *argv[]){
    while(check_reload1()){

        Windoww *a;
        Windoww window;
        window=Create_game();
        a=&window;  
        Take_input_from_user(a);
        SDL_DestroyRenderer(window.renderer);
        SDL_DestroyWindow(window.window);
        SDL_Quit();

    }  
    return 0;
}
