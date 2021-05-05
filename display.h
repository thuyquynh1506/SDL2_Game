#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include "animation.h"

using namespace std;

class Display{
public:
    string path;
    //Tọa độ diện tích của Display
    int xRender = 0;
    int yRender = 0;
    int wRender = 0;
    int hRender = 0;
    int alpha = 255;
    int angle = 0;
    SDL_Point centerRender = {0,0};
    bool textureNull = false;
    //Xử lý annimation
    vector <Animation*> animationQueue;
    //Các biến  sao lưu đưa về hiển thị ban đầu sau animation
    int xRenderCopy = 0;
    int yRenderCopy = 0;
    int wRenderCopy = 0;
    int hRenderCopy = 0;
    int angleCopy = 0;
    SDL_Point centerRenderCopy = {0,0};
    SDL_Texture* textureCopy = NULL;
    //display background
    const Display* displayBackground = NULL;
    double xRelativeRatio = 0;
    double yRelativeRatio = 0;
    double wRelativeRatio = 1;
    double hRelativeRatio = 1;
    //RGB
    int Red = 0;
    int Green = 0;
    int Blue = 0;
    //kích thước của texture
    int widthTexture = 0;
    int heightTexture = 0;

    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

    //mốc tọa độ để render
    SDL_Point originPoint = {0,0};

    //xác định diện tích, tọa độ vùng của ảnh để đưa vào texture
    SDL_Rect* clip = NULL;
    SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;

    Display();

    Display(SDL_Renderer* gRenderer);
    Display(string path, int x=0,int y=0);
    ~Display();

    int getX();
    int setX(int x);
    int getY();
    int setY(int y);
    int setW(int w);
    int setH(int h);
    int setAlpha (int alpha);
    int setRect(SDL_Rect rect);
    int setCenterPoint (SDL_Point centerPoint);
    int setKeyColor (SDL_Color keyColor);
    int setRenderer (SDL_Renderer* renderer);
    int setTexture (SDL_Texture* texture);
    SDL_Rect getOriginalTextureSize();
    //Hàm trả về false khi Texture = NULL
    bool loadTexture(string path, bool colorKey = false);
    int clipImage(int x, int y, int width, int height);
    SDL_BlendMode getBlendMode();
    SDL_BlendMode setBlendMode(SDL_BlendMode blendMode);
    bool animate();
    void update();
    void setAnimation(string animation, Uint32 duration, Uint32 waitTime=0,SDL_Point transformVector={NULL,NULL});
    void setAnimation(string animation, Uint32 duration, SDL_Texture* tmpTexture,Uint32 waitTime=0);
    void setAnimation(Animation* animation);
    int render(bool renderWithCenterPoint = false);
    void handleMouseEvent (SDL_Event* event);
    void setDisplayBackGround (const Display& background);
};

//font chữ
class TextDisplay : public Display{
public:
    TTF_Font* tFont=NULL;
    int font_size;
    TextDisplay();
    TextDisplay(TTF_Font* tFont, int font_size);
    bool makeTextTexture(const char* text, int size,SDL_Color color);
    void render (bool renderWithCenterPoint = false);
};

class Button: public Display{
public:
    std::map<string,SDL_Texture*> buttonTexture;
    string currentStatus = "Mouse Out";
    string previousStatus = "Mouse Down";
    Button();
    ~Button();
    void loadTexture (string MouseOver,string MouseOut);
    void handleMouseEvent(SDL_Event* event);
    void update();
    void render(bool renderWithCenterPoint=false);
    bool Click();
};

class Sprite : public Display{
public:
    int framesNumber = 0;
    int sheetRows = 0;
    int sheetColumns = 0;
    int currentFrame = 0;
    SDL_Rect frameRect = {0,0,0,0};
    int framesPerSecond = 60;
    Uint32 preFrame = NULL;
    Sprite (int framesNumber, int sheetRows, int sheetColumns, SDL_Rect frameRect, int framesPerSecond=60);
    void render();
};

