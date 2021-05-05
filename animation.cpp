#include "animation.h"
//tạo hiệu ứng cho việc xuất hiện của các thành phần

Animation::Animation(string name, int duration):name(name),duration(duration) {}

Animation::Animation(string name, int duration,int waitTime):name(name),duration(duration),waitTime(waitTime) {}

Animation::Animation(string name, int duration, double angleRotate, int waitTime):name(name),duration(duration),angleRotate(angleRotate),waitTime(waitTime){
    if(name!="Rotate"){
        cerr << "Invalid " << name << " animation" << endl;
    }
}

Animation::Animation(string name, int duration,SDL_Point transformVector,int waitTime):name(name),duration(duration),transformVector(transformVector),waitTime(waitTime){}

Animation::Animation(string name, int duration,SDL_Texture* tmpTexture,int waitTime):name(name),duration(duration),tmpTexture(tmpTexture),waitTime(waitTime){
    if(name!="Switch Texture"){
        cerr << "Invalid" << name << " animation" << endl;
    }
}
Animation::~Animation(){}
