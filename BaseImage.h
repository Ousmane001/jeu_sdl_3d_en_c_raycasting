//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <string.h>

bool loadImage(char* p,picture* pict,int w,int h);
void ImageQuit();
void ImageInit();
void freeImage(picture* pict);
void draw(picture* pict,SDL_Renderer* renderer,double angle);
void resize(int w,int h,picture* pict);

typedef struct{
SDL_Surface* image;
SDL_Rect pos;
}picture;