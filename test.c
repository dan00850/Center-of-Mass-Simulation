// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <SDL2/SDL.h>


// #define WIDTH 800
// #define HEIGHT 600
// #define GRID_SIZE 25
// #define SQUARE_SIZE (WIDTH / GRID_SIZE)

// int center_x=0;
// int center_y=0;
// int nail_x=780;
// int nail_y=20;
// int check_click_nail=0;
// int count_o=0;
// int matrix[24][32];// Define a matrix which is used to determine which block will be lighted
// int alpha_change=0;
// int re_load_x=780;
// int re_load_y=580;
// int check_reload=1;

// struct Windoww{
//     SDL_Window* window;
//     SDL_Renderer* renderer;
// };
// typedef struct Windoww Windoww;


// //function to determine the center of mass ();
// void draw_circle(int x, int y,Windoww * window,int color){
//     // red :1 , blue :2;
    
//     if (color==1){
//         SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255); 
//     } else if(color==2){
//         SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255); 
//     } else if(color==3){
//         SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255);
//     } else if(color==4){
//         SDL_SetRenderDrawColor(window->renderer, 255, 255, 0, 255);
//     } else {
//         SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
//     }
    
//     for( int i=x-8;i<=x+8; i++){
        
//         for(int j=y-8; j<=y+8; j++){
//             if(i>0 && i <800 && j >0 && j< 600){
//                 int a=sqrt((i-x)*(i-x)+(j-y)*(j-y));
//                 if(a<=8){            
//                     SDL_RenderDrawPoint(window->renderer, i, j);}
            
//             }
//         }
//     }
// };

// //function which is used to delete the old center of mass


// // function to create a game
// Windoww  Create_game(){
//     Windoww a;    
//     if(SDL_Init(SDL_INIT_VIDEO)!=0){
//         SDL_GetError( );
//         exit(EXIT_FAILURE);
//     }

//     a.window=SDL_CreateWindow("My game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//     if(NULL==a.window){
//         printf("could not create window\n");
//         SDL_GetError( );       
//         exit(EXIT_FAILURE);
//     }

//     a.renderer = SDL_CreateRenderer(a.window, -1, 0);
//     if(NULL == a.renderer){
//         printf("could not create window\n");
//         SDL_GetError( ); 
//         exit(EXIT_FAILURE);
//     }
//     return a;
// };
// void Find_center_of_mass(int add,int x,int y, Windoww * window){
//     //if add more block we will change the center by add the coordinate of the center of block int by the following fomular
    
//     if(add==1){
//         if (count_o>1){
//             center_x=(center_x*(count_o-1)+x)/count_o;
//             center_y=(center_y*(count_o-1)+y)/count_o;
//         }
//     }
//     else if (add==0){
//         if(count_o>0){
//         center_x=(center_x*(count_o+1)-x)/count_o;
//         center_y=(center_y*(count_o+1)-y)/count_o;
//         }
//     }
    
//     draw_circle(center_x,center_y, window,1);
    
// };

// /*
// This function have 6 parameters . This function will rotate a aquare around a axit with an alpha angle
// int x: the x coordinate of axit
// int y: the y coordinate of axit
// int cen_x : the x coordinate of the square
// int cen_y :  the y coordinate of the square
// double cos_alpha : the value of cos_alpha
// double sin_alpha :  the value of sin_alpha
// */
// void rotateSquare(Windoww *window, int x ,int y,int cen_x,int cen_y ,double cos_alpha,double sin_alpha){
//     int x_top_left=cen_x-12; //  coordinate x of the upper left corner 
//     int y_top_left=cen_y-12; //  coordinate y of the upper left corner

//     // the size of square is 25
//     int newX,newY;
//     for (int i = x_top_left; i < x_top_left + SQUARE_SIZE; i++) {
//         for (int j = y_top_left; j < y_top_left + SQUARE_SIZE; j++) {
//             /*move the point to the Cartesian coordinate system*/
//             int x2 = i - x;
//             int y2 = j - y;
//             /*rotate the point by using rotate matrix*/
//             newX = round(x2 * cos_alpha + y2 * sin_alpha);
//             newY = round(-x2 * sin_alpha + y2 * cos_alpha);
//             /*Move the point to the expected place*/
//             newX += x;
//             newY += y;

//             SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255);
//             SDL_RenderDrawPoint(window->renderer, newX, newY);
//         }
//     }
   
// }   
// /*
// This function will rotate the system
// int cen_x : the coordinate x of the axist
// int cen_y : the coordinate y of the axist
// */
// void rotate(int cen_x,int cen_y,Windoww * window, double cos_alpha,double sin_alpha){
   
//     /*Calculate cos alpha and sin(alpha) that need to be rotate*/
//     // double cos_alpha, sin_alpha;
//     // double hypotenuse =sqrt((center_x-cen_x)*(center_x-cen_x)+(center_y-cen_y)*(center_y-cen_y));
//     // sin_alpha= 1.0 * (cen_x-center_x)/hypotenuse;
//     // cos_alpha= 1.0 * (center_y-cen_y)/hypotenuse;
//     for (int i=0; i<24; i++){
//         for(int j=0; j<32; j++){
//             if (matrix[i][j]==1){
//                 rotateSquare(window,cen_x,cen_y,j*SQUARE_SIZE+13,i*SQUARE_SIZE+13,cos_alpha,sin_alpha);
//             }
//         }
//     }
//     // rotate the center:
//     int center_x2= center_x-cen_x;
//     int center_y2= center_y-cen_y;
//     int center_x1 = round(center_x2 * cos_alpha + center_y2 * sin_alpha);
//     int center_y1 = round(-center_x2 * sin_alpha + center_y2 * cos_alpha);
//     center_x1=center_x1+cen_x;
//     center_y1=center_y1+cen_y;
//     draw_circle(center_x1,center_y1,window,1);
    
// }

// // function to take input
// void Take_input_from_user(Windoww * window){
    
//     count_o=0;
//     int x,y;
//     SDL_Event event;
//     int running = 1;
    
//     SDL_SetRenderDrawColor(window->renderer,255,255,255,255);
//     SDL_RenderClear(window->renderer);
//     check_reload=0;
//     while (running) {
        
//         while (SDL_PollEvent(&event)) {
//             check_click_nail=0;
//             switch (event.type) {
//                 case SDL_QUIT:
//                     running = 0;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                 //x and y is coordinate of mouse click and divide  by the "SQUARE_SIZE "to find the grid which will be displayed 
                    
//                     x = event.button.x ;
//                     y = event.button.y ;
//                     // if the user click on the nail
//                     if((nail_x-10<x) && (x<nail_x+10) && (nail_y-10 < y)&&(y < nail_y +10)){

//                         check_click_nail=1;
//                         break;

//                     }
                    
//                     x = x / SQUARE_SIZE;
//                     y = y / SQUARE_SIZE;
//                     if(matrix[y][x] ==0){
//                         matrix[y][x] = 1;     
//                         count_o++;  
//                     }  
//                     else{
//                         matrix[y][x] = 0;
//                         count_o--;
//                         printf("centerx : %d \n", center_x);
//                         printf("center_y: %d \n", center_y);
//                     }        
//                     break;
//                 default:
//                     break;
//             }
        
//         }
//         center_x=0;
//         center_y=0;
//         for (int y = 0; y <24; y++) {
//             for (int x = 0; x < 32; x++) {
//                 if (matrix[y][x]) {
                    
//                     center_x=center_x+x*SQUARE_SIZE+13;
//                     center_y=center_y+y*SQUARE_SIZE+13;
                    
//                     SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
//                     SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
//                     SDL_RenderFillRect(window->renderer, &rect);
//                 }
//                 else {
//                     SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
//                     SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255);
//                     SDL_RenderFillRect(window->renderer, &rect);
//                 }
//             }
//         }
//         if (count_o!=0){
//             center_x=center_x / count_o;
//             center_y=center_y / count_o;
//         }else{
//             center_x=0;
//             center_y=0;
//         }
//         draw_circle(center_x,center_y,window,1);
//         draw_circle(nail_x,nail_y,window,2);

//         SDL_RenderPresent(window->renderer);
        
//         // IN the case click in to the nail
//         if (check_click_nail==1){
//             break;
//         } 
//     }
//     running=1;
//     x=0;
//     y=0;
//     while (running){
//         while (SDL_PollEvent(&event)) {
            
//             switch (event.type) {
//                 case SDL_QUIT:
//                     running = 0;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                 //x and y is coordinate of mouse click and divide  by the "SQUARE_SIZE "to find the grid which will be displayed 
                    
//                     x = event.button.x ;
//                     y = event.button.y ;
//                     alpha_change=0;
//                     if((re_load_x-10<x) && (x<re_load_x+10) && (re_load_y-10 < y)&&(y < re_load_y +10)){
//                         check_reload=1;
                        
//                     }
//             }
//         }
//         if(check_reload==1){
//             break;
//         }
//         // printf("x,y : %d %d \n",x,y);
//         center_x=0;
//         center_y=0;
//         for (int y = 0; y <24; y++) {
//             for (int x = 0; x < 32; x++) {
//                 if (matrix[y][x]) {
                    
//                     center_x=center_x+x*SQUARE_SIZE+13;
//                     center_y=center_y+y*SQUARE_SIZE+13;
                    
//                     SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
//                     SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
//                     SDL_RenderFillRect(window->renderer, &rect);
//                 }
//                 else {
//                     SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
//                     SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255);
//                     SDL_RenderFillRect(window->renderer, &rect);
//                 }
//             }
//         }
//         if (count_o!=0){
//             center_x=center_x / count_o;
//             center_y=center_y / count_o;
//         }else{
//             center_x=0;
//             center_y=0;
//         }

//         // rotateSquare(window,x,y,112,112,0.3,0.954);

//         // calculate the alpha angle that need to be rotated
//         double cos_alpha, sin_alpha;
//         double hypotenuse =sqrt((center_x-x)*(center_x-x)+(center_y-y)*(center_y-y));
//         sin_alpha= 1.0 * (x-center_x)/hypotenuse;
//         cos_alpha= 1.0 * (center_y-y)/hypotenuse;
//         double alpha = acos(cos_alpha);
//         if (alpha_change <50){
//             double alpha1= alpha-alpha*(50-alpha_change)/50;
//             double cos_alpha1=cos(alpha1);
//             double sin_alpha1=sin(alpha1);
//             if(center_x<x){
//                 rotate(x,y,window,cos_alpha1,sin_alpha1);
//             } else{
//                 rotate(x,y,window,cos_alpha1,-sin_alpha1);
//             }           
//         } else{
//             rotate(x,y,window,cos_alpha,sin_alpha);
//         }
//         // rotate the center
//         draw_circle(re_load_x,re_load_y,window,4);
//         draw_circle(center_x,center_y,window,1);
//         draw_circle(x,y,window,2);
//         SDL_Delay(20);
//         SDL_RenderPresent(window->renderer);
//         alpha_change++;
//     }   
//     for(int y=0; y<24;y++){
//         for(int x=0;x<32; x++){  
//             matrix[y][x]=0;
//         }
//     }
//     SDL_Quit();   
// };

// int SDL_main(int argc, char *argv[]){
//     while(check_reload==1){

//         Windoww *a;
//         Windoww window;
//         window=Create_game();
//         a=&window;  
//         Take_input_from_user(a);
//         SDL_DestroyRenderer(window.renderer);
//         SDL_DestroyWindow(window.window);
//         SDL_Quit();

//     }  
//     return 0;
// }



// //  SDL_SetRenderDrawColor(window->renderer,255,255,255,255);
// //     SDL_RenderClear(window->renderer);

// //     for(int i=0; i<24 ; i++){
// //         for(int j =0; j<32 ; j++){
// //             if(matrix[i][j]==1){
// //                 SDL_Rect rect={i* SQUARE_SIZE, j *SQUARE_SIZE ,SQUARE_SIZE,SQUARE_SIZE};
// //                 SDL_SetRenderDrawColor(window->renderer ,0,0,0,255);
// //                 SDL_RenderFillRect(window->renderer ,&rect);
// //             }
// //         }
// //     }
// //     SDL_RenderPresent(window->renderer);    
// //     }
// // void delete_circle(int x, int y,Windoww * window,int color){
// //     // find the square which contain the circle
// //     int square_contain_x= x/SQUARE_SIZE;
// //     int square_contain_y=y/SQUARE_SIZE;
// //     // if that square is being shown change into to black otherwise change it into white 
// //     if(matrix[square_contain_y][square_contain_x]==1){
// //         SDL_SetRenderDrawColor(window->renderer, 200, 200, 200, 255); // black
// //     }else{
// //         SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);        // white
// //     }
    
// //     for( int i=x-10;x+10; i++){
// //         for(int j=y-10; y+10; j++){
// //             if(i>0 && i <800 && j >0 && j< 600){
// //                 int a=sqrt((i-x)*(i-x)+(j-y)*(j-y));
// //                 if(a<=10){
// //                     SDL_RenderDrawPoint(window->renderer, i, j);
// //                 }
// //             }
// //         }
// //     }
// // };