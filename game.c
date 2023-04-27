#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "game.h"       

#define WIDTH 800
#define HEIGHT 600
#define GRID_SIZE 25
#define SQUARE_SIZE (WIDTH / GRID_SIZE)

int center_x=0;
int center_y=0;
int nail_x=780;
int nail_y=20;
int check_click_nail=0;
int count_o=0;
int matrix[24][32];// Define a matrix which is used to determine which block will be lighted
int alpha_change=0;
int drop_change =0;
int re_load_x=780;
int re_load_y=580;
int check_reload=1;


//function to determine the center of mass ();
bool check_reload1(){
    return (check_reload=1);
}
// Define a function to draw a circle at a given point on a window
void draw_circle(int x, int y, Windoww * window, int color){
    // Define the color to be used for rendering the circle
    if (color==1){
        SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255); // Red
    } else if(color==2){
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255); // Blue
    } else if(color==3){
        SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255); // Green
    } else if(color==4){
        SDL_SetRenderDrawColor(window->renderer, 255, 255, 0, 255); // Yellow
    } else {
        SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255); // White
    }
    
    // Loop over all points within a square of 17x17 pixels around the center point
    for (int i = x - 8; i <= x + 8; i++){
        for (int j = y - 8; j <= y + 8; j++){
            // Check that the current point is within the window's bounds
            if (i > 0 && i < 800 && j > 0 && j < 600){
                // Calculate the distance from the current point to the center point
                int a = sqrt((i - x) * (i - x) + (j - y) * (j - y));
                // If the distance is less than or equal to 8 (the circle radius), draw a pixel at the current point
                if (a <= 8){
                    SDL_RenderDrawPoint(window->renderer, i, j);
                }
            }
        }
    }
}

//function which is used to delete the old center of mass


// Define a function called "Create_game()" that returns a variable of type "Windoww"
Windoww Create_game(){
    // Declare a variable "a" of type "Windoww"
    Windoww a;    

    // Initialize the SDL video subsystem
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        // If an error occurred, print the error message and exit the program
        SDL_GetError( );
        exit(EXIT_FAILURE);
    }

    // Create a window called "My game" with the specified width and height, and show it on screen
    a.window=SDL_CreateWindow("My game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(NULL==a.window){
        // If an error occurred, print the error message and exit the program
        printf("could not create window\n");
        SDL_GetError( );       
        exit(EXIT_FAILURE);
    }

    // Create a renderer for the window
    a.renderer = SDL_CreateRenderer(a.window, -1, 0);
    if(NULL == a.renderer){
        // If an error occurred, print the error message and exit the program
        printf("could not create window\n");
        SDL_GetError( ); 
        exit(EXIT_FAILURE);
    }

    // Return the "a" variable containing the window and renderer
    return a;
};
void Find_center_of_mass(){
    //if add more block we will change the center by add the coordinate of the center of block int by the following fomular
    
    if (count_o!=0){
            center_x=center_x / count_o;
            center_y=center_y / count_o;
        }else{
            center_x=0;
            center_y=0;
        }
};

/*
This function have 6 parameters . This function will rotate a aquare around a axit with an alpha angle
int x: the x coordinate of axit
int y: the y coordinate of axit
int cen_x : the x coordinate of the square
int cen_y :  the y coordinate of the square
double cos_alpha : the value of cos_alpha
double sin_alpha :  the value of sin_alpha
*/
void rotateSquare(Windoww *window, int x ,int y,int cen_x,int cen_y ,double cos_alpha,double sin_alpha){
    int x_top_left=cen_x-12; //  coordinate x of the upper left corner 
    int y_top_left=cen_y-12; //  coordinate y of the upper left corner

    // the size of square is 25
    int newX,newY;
    for (int i = x_top_left; i < x_top_left + SQUARE_SIZE; i++) {
        for (int j = y_top_left; j < y_top_left + SQUARE_SIZE; j++) {
            /*move the point to the Cartesian coordinate system*/
            int x2 = i - x;
            int y2 = j - y;
            /*rotate the point by using rotate matrix*/
            newX = round(x2 * cos_alpha + y2 * sin_alpha);
            newY = round(-x2 * sin_alpha + y2 * cos_alpha);
            /*Move the point to the expected place*/
            newX += x;
            newY += y;
            /*light the pixel*/
            SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255);
            SDL_RenderDrawPoint(window->renderer, newX, newY);
        }
    }
   
}   
/*
This function will rotate the object an alpha angle
int cen_x : the coordinate x of the axist
int cen_y : the coordinate y of the axist
double cos_alpha : the value of cos() of alpha angle
double sin_alpha  : the value of sin() of the alpha angle
*/
void rotate(int cen_x,int cen_y,Windoww * window, double cos_alpha,double sin_alpha){
    // 
    for (int i=0; i<24; i++){
        for(int j=0; j<32; j++){
            if (matrix[i][j]==1){
                rotateSquare(window,cen_x,cen_y,j*SQUARE_SIZE+13,i*SQUARE_SIZE+13,cos_alpha,sin_alpha);
            }
        }
    }
    // rotate the center by using transfomation linear:
    int center_x2= center_x-cen_x;
    int center_y2= center_y-cen_y;
    int center_x1 = round(center_x2 * cos_alpha + center_y2 * sin_alpha);
    int center_y1 = round(-center_x2 * sin_alpha + center_y2 * cos_alpha);
    center_x1=center_x1+cen_x;
    center_y1=center_y1+cen_y;
    draw_circle(center_x1,center_y1,window,1);
    
}
/* The function will rotate the object physically
The function have 3 parameter :
int x: the x coordinate of the nail
int y : the y coordinate of the nail
window the pointer to the address of a window*/
void SmoothRotate(int x,int y, Windoww * window){
    
    /*Calculate the final alpha angle that the created object will approach to*/
    double cos_alpha, sin_alpha;
    double hypotenuse =sqrt((center_x-x)*(center_x-x)+(center_y-y)*(center_y-y));
    sin_alpha= 1.0 * (x-center_x)/hypotenuse;
    cos_alpha= 1.0 * (center_y-y)/hypotenuse;
    double alpha = acos(cos_alpha);

    /*alpha_change is grobal variable which is used to calculate the gradual changing of
     angle of the object when it rotate it can be considered as the time quantity in physis
     The condition alpha_change make sure the angle do not exceeding the expected place*/
    if (alpha_change* alpha_change <250){
        /* calculate the gradual chaning of the angle*/
        double alpha1= alpha-alpha*(250-alpha_change* alpha_change)/250;
        double cos_alpha1=cos(alpha1);
        double sin_alpha1=sin(alpha1);

        /*If the center of the object  on the left of the  nail -> rotate clockwise other wise turn back clockwise*/
        if(center_x<x){
            rotate(x,y,window,cos_alpha1,sin_alpha1);
        } else{
            rotate(x,y,window,cos_alpha1,-sin_alpha1);
        }           
    }/* In the case the alpha_change exeeding the limit , just show a expected place of the object on the window*/ 
    else{
        rotate(x,y,window,cos_alpha,sin_alpha);
    }
}
/*
The function will drop the object 
THe function have 2 parameters:
window the pointer to the address of a window
int drop_change : can be consider as time quantity in physic */
void Drop_the_object(Windoww * window,int drop_change){
    /* calculate the change distance follow by y axit , drop_change can be considered as time quatity*/
    int Delta_y=drop_change*drop_change/2;  

    /*check if the square is lighted, we will drop it */
    for(int j=0; j<24; j++){
        for(int k=31; k>=0; k--){
            if(matrix[j][k]==1){
                /* if the value y coordinate exceeding the the width of the window ,show it by same color with the color of the window*/
                if (j* SQUARE_SIZE +Delta_y >600){
                    SDL_Rect rect = { k * SQUARE_SIZE, 600-SQUARE_SIZE-1, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                
                } /*other wise show the object in changed place*/
                else{
                    SDL_Rect rect = { k * SQUARE_SIZE, j * SQUARE_SIZE + Delta_y, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                  
                }            
            }
        }
    }          
};

/*This function will take action base on the location of the nail
3 parameter:
int x : x coordinate of the nail
int y : y coordinate of the nail
window the pointer to the address of the window*/
void action(int x ,int y,Windoww * window){
    int chec_action=0;
    /*Check if the nail is attached on the object*/
    for(int i=0; i<24; i++){
        for (int j=0; j<32; j++){
            if(matrix[i][j]==1){
            if (i*SQUARE_SIZE <= y    && 
                (i+1)*SQUARE_SIZE > y && 
                j*SQUARE_SIZE <= x    && 
                (j+1)*SQUARE_SIZE >x   ){
                    chec_action=1;
                    
                    break;
                }
        }}
            
        if(chec_action==1) break;
    }
    /*if nail is attached on the object -> rotate it, otherwise drop it*/
    if(chec_action==1){
        SmoothRotate( x, y, window);
    } else {
        Drop_the_object(window,drop_change);
    }
}
// function to take input
void Take_input_from_user(Windoww * window){
    count_o=0; //set number of square on the screen to 0
    int x,y; // variables to store the x and y coordinates of the mouse click

    SDL_Event event;
    int running = 1;
   
    // Set the render draw color to white and clear the screen
    SDL_SetRenderDrawColor(window->renderer,255,255,255,255);
    SDL_RenderClear(window->renderer);
    
    // set reload to 0
    check_reload=0;
    
    // Run a loop to take input from the user until the user quits the program
    while (running) {
        // Run a loop to handle all events
        while (SDL_PollEvent(&event)) {
            /*change check_click_nail to be 0 (mean do not click into the nail)*/
            check_click_nail=0; 
            switch (event.type) {
                // If the user clicks on the close window button
                case SDL_QUIT:
                    running = 0;
                    break;
                // If the user clicks on the close window button
                case SDL_MOUSEBUTTONDOWN:
                //x and y is coordinate of mouse click and divide  by the "SQUARE_SIZE "to find the grid which will be displayed 
                    
                    x = event.button.x ;
                    y = event.button.y ;
                    // if the user click on the nail
                    if((nail_x-10<x) && (x<nail_x+10) && (nail_y-10 < y)&&(y < nail_y +10)){
                         // Set the check click nail variable to true
                        check_click_nail=1;
                        break;

                    }
                    // Divide the x and y coordinates by the SQUARE_SIZE to get the grid which will be displayed
                    x = x / SQUARE_SIZE;
                    y = y / SQUARE_SIZE;
                    // If the square is not displayed -> display the square and increase the number of displayed grid by 1 .
                    if(matrix[y][x] ==0){
                        matrix[y][x] = 1; 
                        count_o++;  //number of square increase by 1
                    }  
                    // If the square is already displayed -> turn off it and decrease the number of displayed grid by 1
                    else{ 
                        matrix[y][x] = 0; 
                        count_o--; // number of square decrease by 1
                        printf("centerx : %d \n", center_x);
                        printf("center_y: %d \n", center_y);
                    }        
                    break;
                default:
                    break;
            }
        
        }
        // Reset the center_x and center_y variables to calculate the center of  the object
        center_x=0;
        center_y=0;
        for (int y = 0; y <24; y++) {
            for (int x = 0; x < 32; x++) {
                // If the square is displayed
                if (matrix[y][x]==1) {
                    // Calculate the total value of squares's center
                    center_x=center_x+x*SQUARE_SIZE+13;
                    center_y=center_y+y*SQUARE_SIZE+13;
                    // Draw a filled rectangle to display square
                    SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                }
                // If the square is not displayed
                else {
                    // Draw a rectangle whose color is same with the background
                    SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                }
            }
        }
        //
        Find_center_of_mass();
        /*Draw the center of the center and nail botton*/
        draw_circle(center_x,center_y,window,1);
        draw_circle(nail_x,nail_y,window,2);
        /*display all in the window*/
        SDL_RenderPresent(window->renderer);
        
        // IN the case click in to the nail
        if (check_click_nail==1){
            break;
        } 
    }
    /* Reset the click location to zero*/
    x=0;
    y=0;
    while (true){
        // Run a loop to handle all events
        while (SDL_PollEvent(&event)) {        
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    //x and y is coordinate of mouse click and divide  by the "SQUARE_SIZE "to find the grid which will be displayed                     
                    x = event.button.x ;
                    y = event.button.y ;
                    /*Reset alpha_change and drop_change to zero to if user click mouse so computer can use it to rotate or drop the object*/
                    alpha_change=0;
                    drop_change=0;
                    /* if user click on reload botton-> reload all program*/
                    if((re_load_x-10<x) && (x<re_load_x+10) && (re_load_y-10 < y)&&(y < re_load_y +10)){
                        check_reload=1;
                        
                    }
            }
        }
        if(check_reload==1){
            break;//Break to reload all the program
        }
        // Reset the center_x and center_y variables to calculate the center of  the object
        center_x=0;
        center_y=0;

        for (int y = 0; y <24; y++) {
            for (int x = 0; x < 32; x++) {
                // If the square is displayed
                if (matrix[y][x]) {
                    // Calculate the total value of squares's center
                    center_x=center_x+x*SQUARE_SIZE+13;
                    center_y=center_y+y*SQUARE_SIZE+13;
                    // Draw a filled rectangle to display square
                    SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                }
                // If the square is not displayed
                else {
                    // Draw a rectangle whose color is same with the background
                    SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255);
                    SDL_RenderFillRect(window->renderer, &rect);
                }
            }
        }
        /*find center of the object*/
        Find_center_of_mass();

        // rotateSquare(window,x,y,112,112,0.3,0.954);

        // if user click on the botton ->take action(rotate or drop)
        if (x!=0 && y!=0){
            action(x,y,window);
        }        
        // Draw reload botton, center of object, and the nail
        draw_circle(re_load_x,re_load_y,window,4);
        draw_circle(center_x,center_y,window,1);
        draw_circle(x,y,window,2);
        /*delay the displayed window in 20ms*/
        SDL_Delay(30);
        SDL_RenderPresent(window->renderer);
        /*increase the change of alpha and  the change of drop (the two have function as time quantity)*/
        alpha_change++;
        drop_change++;
    }   
    /*Reset all Square before quit the window*/
    for(int y=0; y<24;y++){
        for(int x=0;x<32; x++){  
            matrix[y][x]=0;
        }
    }
    SDL_Quit();   
};
