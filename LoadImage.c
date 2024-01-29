#include <BaseImage>


bool loadImage(char* p,picture* pict,int w,int h){
    if(pict->image != NULL){
        SDL_FreeSurface(image);
    }
    pict->image = SDL_CreateRGBSurface(0,w,l,32,0,0,0,0);
    pos.w=image->clip_rect.w;
    pos.h=image->clip_rect.h;
    pict->image = IMG_Load(p);
    if(pict->image!=NULL){
        return true;
    }
    return false;
}

void draw(picture* pict,SDL_Renderer* renderer,double angle){
    if(pict->image!=NULL){
        SDL_Point pt;
        pt.x=pict->pos.w/2;
        pt.x=pict->pos.h/2;
        pt.x+=pict->pos.x;
        pt.y+=pict->pos.y;
        SDL_RenderCopyEx(renderer,pict->image,NULL,pict->&pos,angle,pt,SDL_FLIP_NONE);
    }
}

void ImageInit(){
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void ImageQuit(){
    IMG_Quit();
}

void freeImage(picture* pict){
    if(pict->image!=NULL){
        SDL_FreeSurface(pict->image);
    }
}

void resize(int w,int h,picture* pict){
    pict->pos.w=w;
    pict->pos.h=h;
}
