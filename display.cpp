#include "display.h"

Display::Display(){};

Display::Display(SDL_Renderer* gRenderer){
    this->renderer = gRenderer;
}
Display::Display (string path, int x, int y){
    this->xRender = x;
    this->yRender = y;
    this->path = path;
};
//vị trí hiển thị
Display::~Display(){}

int Display::getX(){
    return this->xRender;
};

int Display::getY(){
    return this->yRender;
};

int Display::setX(int x){
    this->xRender = x;
    return 1;
};

int Display::setY(int y){
    this->yRender = y;
    return 1;
};
int Display::setW(int w){
    this->wRender = w;
    return 1;
};
int Display::setH(int h){
    this->hRender = h;
    return 1;
};

//đặt chế độ blend cho alpha riêng
int Display::setAlpha (int alpha){
    if(this->getBlendMode()!=SDL_BLENDMODE_BLEND){
        this->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    else{
        SDL_SetTextureAlphaMod(this->texture,alpha);
        this->alpha = alpha;
    }
    return 1;
}

//đặt vị trí và kích thước cho một số hiển thị
int Display::setRect(SDL_Rect rect){
    this->xRender = rect.x;
    this->yRender = rect.y;
    this->wRender = rect.w;
    this->hRender = rect.h;
    return 1;
}

//đặt vị trí trung tâm cho một số hiển thị
int Display::setCenterPoint (SDL_Point centerPoint){
    this->centerRender.x = centerPoint.x;
    this->centerRender.y = centerPoint.y;
    this->xRender = centerPoint.x - this->wRender/2;
    this->yRender = centerPoint.y - this->hRender/2;
    return 0;
}

//color Key
int Display::setKeyColor(SDL_Color key){
    this->Red = key.r;
    this->Green = key.g;
    this->Blue = key.b;
    return 0;
}

//đặt render để hiển thị
int Display::setRenderer (SDL_Renderer* renderer){
    this->renderer = renderer;
    return 1;
}

//tải ảnh và xóa hiệu ứng trước đó
int Display::setTexture(SDL_Texture* texture){
    this->texture = texture;
    this->animationQueue.clear();
    return 0;
}

//kích thước ảnh được co về giá trị đã quy định
SDL_Rect Display::getOriginalTextureSize(){
    if(this->widthTexture == 0 || this->heightTexture == 0){
        SDL_QueryTexture(this->texture, NULL, NULL, &this->widthTexture,&this->heightTexture);
    }
    return SDL_Rect {0,0,widthTexture,heightTexture};
};

//vị trí hiển thị hình ảnh
int Display::clipImage(int x,int y,int width,int height){
    this->clip = new SDL_Rect;
    this->clip->x = x;
    this->clip->y = y;
    this->clip->w = width;
    this->clip->h = height;
    return 1;
}

//blend texture
SDL_BlendMode Display::getBlendMode(){
    SDL_GetTextureBlendMode(this->texture,&this->blendMode);
    return this->blendMode;
}

SDL_BlendMode Display::setBlendMode (SDL_BlendMode blendMode){
    SDL_SetTextureBlendMode(this->texture,blendMode);
    this->blendMode = blendMode;
    return this->blendMode;
}

//tạo hiệu ứng xuất hiện cho các thành phần
bool Display::animate(){
    bool done = true;
    for (int i=0;i<animationQueue.size();i++){
        if(animationQueue[i]->ended) continue;
        if(animationQueue[i]->tmpTime==NULL){
            animationQueue[i]->tmpTime = SDL_GetTicks();
        };
        if(SDL_GetTicks()-animationQueue[i]->tmpTime < animationQueue[i]->waitTime) continue;

        //hiệu ứng mở rộng
        if(animationQueue[i]->name.find("Scale Up")!=string::npos){
            double ratioScale = 2;
            SDL_Point centerPoint;
            if (animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            }
            centerPoint = this->centerRenderCopy;
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset >animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            }
            if(timeOffset < animationQueue[i]->duration/2){
                ratioScale = (ratioScale-1)*double(timeOffset)/double(animationQueue[i]->duration/2)+1;
            }
            else{
                ratioScale = (1-ratioScale)*(double(timeOffset)/double(animationQueue[i]->duration/2)-1)+ratioScale;
            }
            this->wRender = double(this->wRenderCopy)*ratioScale;
            this->hRender = double(this->hRenderCopy)*ratioScale;
            this->xRender = centerPoint.x - this->wRender/2;
            this->yRender = centerPoint.y - this->hRender/2;
        };

        //hiệu ứng xuất hiện
        if(animationQueue[i]->name.find("Appear")!=string::npos){
            double ratioScale = 1;
            SDL_Point centerPoint;
            if(animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            }
            centerPoint = this->centerRenderCopy;
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset > animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            }
            ratioScale = double(timeOffset)/double(animationQueue[i]->duration)*ratioScale;
            this->wRender = double(this->wRenderCopy)*ratioScale;
            this->hRender = double(this->hRenderCopy)*ratioScale;
            this->xRender = centerPoint.x - this->wRender/2;
            this->yRender = centerPoint.y - this->hRender/2;
        };

        //hiệu ứng biến mất
        if(animationQueue[i]->name.find("Disappear")!=string::npos){
            double ratioScale = 1;
            SDL_Point centerPoint;
            if(animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            }
            centerPoint = this->centerRenderCopy;
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset > animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            };
            ratioScale = ratioScale - double(timeOffset)/double(animationQueue[i]->duration);
            this->wRender = double(this->wRenderCopy)*ratioScale;
            this->hRender = double(this->hRenderCopy)*ratioScale;
            this->xRender = centerPoint.x - this->wRender/2;
            this->yRender = centerPoint.y - this->hRender/2;
        };

        //hiệu ứng biến đổi
        if(animationQueue[i]-> name.find("Transform")!=string::npos){
            if(animationQueue[i]->startTime==NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended=false;
            }
            if(animationQueue[i]->transformVector.x!=NULL||animationQueue[i]->transformVector.y!=NULL){
                Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
                double ratioTime = (double)timeOffset/(double)animationQueue[i]->duration;
                if(timeOffset>animationQueue[i]->duration){
                    animationQueue[i]->ended = true;
                    continue;
                };
                if(this->centerRenderCopy.x!=0&&this->centerRenderCopy.y!=0){
                    SDL_Point newCenterPoint;
                    newCenterPoint.x = this->centerRenderCopy.x + (double)animationQueue[i]->transformVector.x * ratioTime;
                    newCenterPoint.y = this->centerRenderCopy.y + (double)animationQueue[i]->transformVector.y * ratioTime;
                    this->setCenterPoint(newCenterPoint);
                }
                else{
                    this->xRender = this->xRenderCopy + animationQueue[i]->transformVector.x*ratioTime;
                    this->yRender = this->yRenderCopy + animationQueue[i]->transformVector.y*ratioTime;
                }
            }
            else{
                cout << "Could not do transform animation" <<endl;
            }
        }

        //hiệu ứng làm mờ dần vào trong
        if(animationQueue[i]->name.find("Fade In")!=string::npos){
            double ratio = 1;
            int alpha;
            if(animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            };
            if(this->getBlendMode()!=SDL_BLENDMODE_BLEND){
                this->setBlendMode(SDL_BLENDMODE_BLEND);
            };

            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset > animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            };
            ratio=(double)timeOffset/(double)animationQueue[i]->duration;
            alpha = ratio*255;
            this->setAlpha(alpha);
        };

        //hiệu ứng mờ dần
        if(animationQueue[i]->name.find("Fade Out")!=string::npos){
            double ratio=1;
            int alpha;
            if(animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            };
            if(this->getBlendMode()!=SDL_BLENDMODE_BLEND){
                this->setBlendMode(SDL_BLENDMODE_BLEND);
            }
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset > animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            };
            ratio=(double)timeOffset/(double)animationQueue[i]->duration;
            alpha = (1-ratio)*255;
            this->setAlpha(alpha);
        };
        //hiệu ứng chuyển đổi kết cấu
        if(animationQueue[i]->name.find("Switch Texture")!=string::npos){
            if(animationQueue[i]->startTime==NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
                this->texture=animationQueue[i]->tmpTexture;
            }
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            this->texture = animationQueue[i]->tmpTexture;
            if(timeOffset>animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                this->texture = this->textureCopy;
                continue;
            };
        };
        //hiệu ứng xoay
        if(animationQueue[i]->name.find("Rotate")!=string::npos){
            if(animationQueue[i]->startTime==NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
                this->angleCopy = this->angle;
            };
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset>animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            };
            this->angle = angleCopy + animationQueue[i]->angleRotate*(double)timeOffset/(double)animationQueue[i]->duration;
        };

        //hiệu ứng giảm
        if(animationQueue[i]->name.find("Cut Down")!=string::npos){
            if(animationQueue[i]->startTime == NULL){
                animationQueue[i]->startTime = SDL_GetTicks();
                animationQueue[i]->ended = false;
            }
            Uint32 timeOffset = SDL_GetTicks()-animationQueue[i]->startTime;
            if(timeOffset>animationQueue[i]->duration){
                animationQueue[i]->ended = true;
                continue;
            };
            SDL_Rect originalSize = this->getOriginalTextureSize();
            int newyRender = this->yRenderCopy + this->hRenderCopy*(double)timeOffset/(double)animationQueue[i]->duration;
            int newhRender = this->hRenderCopy - (newyRender - this->yRenderCopy);
            int newClipHeight = double(newhRender)/double(this->hRenderCopy)*originalSize.h;
            this->clipImage(0,0,originalSize.w,newClipHeight);
            this->setRect({this->xRenderCopy,newyRender,this->wRenderCopy,newhRender});
        };
    };
    for(auto it = animationQueue.begin();it<animationQueue.end();it++){
        if(!(*it)->ended){
            done=false;
            break;
        }
    };
    return done;
}

//tải vị trí và render cho background
void Display::update()
{
    if(this->displayBackground != NULL){
        this->originPoint.x = displayBackground->originPoint.x+displayBackground->xRender;
        this->originPoint.y = displayBackground->originPoint.y+displayBackground->yRender;
        this->xRender = this->displayBackground->wRender*this->xRelativeRatio;
        this->yRender = this->displayBackground->hRender*this->yRelativeRatio;
        this->wRender = this->displayBackground->wRender*this->wRelativeRatio;
        this->hRender = this->displayBackground->hRender*this->hRelativeRatio;
    };
    if(Display::animate()){
        this->animationQueue.clear();
        this->xRenderCopy = 0;
        this->yRenderCopy = 0;
        this->wRenderCopy = 0;
        this->hRenderCopy = 0;
        this->angleCopy = 0;
        this->centerRenderCopy = {0,0};
    };
};

//tạo hiệu ứng chuyển động cho các animation
void Display::setAnimation(string animation,Uint32 duration,Uint32 waitTime,SDL_Point transformVector){
    this->xRenderCopy = this->xRender;
    this->yRenderCopy = this->yRender;
    this->wRenderCopy = this->wRender;
    this->hRenderCopy = this->hRender;
    this->centerRenderCopy = {this->xRender + this->wRender/2,this->yRender+this->hRender/2};
    Animation* newAnimation = new Animation(animation,duration,transformVector,waitTime);
    this->animationQueue.push_back(newAnimation);
    if(animation.find("Fade In")!=string::npos){
        this->setAlpha(0);
    };
}

void Display::setAnimation(string animation, Uint32 duration,SDL_Texture* tmpTexture, Uint32 waitTime){
    Animation* newAnimation = new Animation(animation,duration,tmpTexture,waitTime);
    this->animationQueue.push_back(newAnimation);
    this->textureCopy = this->texture;
    this->texture = tmpTexture;
}

void Display::setAnimation(Animation* animation){
    this->animationQueue.push_back(animation);
}

int Display::render(bool renderWithCenterPoint){
    if(this->texture == NULL && !this->textureNull) cerr << "Load texture for Display" << endl;
    if(this->renderer == NULL) cerr << "Load renderer for Display" << endl;
    Display::update();
    if((this->centerRender.x!=0||this->centerRender.y!=0)&&renderWithCenterPoint){
        this->xRender = this->centerRender.x-this->wRender/2;
        this->yRender = this->centerRender.y-this->hRender/2;
    }
    this->angle = this->angle%360;
    SDL_Rect rectDes = {this->xRender + originPoint.x,this->yRender + originPoint.y,this->wRender,this->hRender};
    if(this->angle==0){
        SDL_RenderCopy(this->renderer, texture, this->clip,&rectDes);
    }
    else{
        if(angle<0)this->angle = -angle;
        SDL_RenderCopyEx(this->renderer,this->texture,this->clip,&rectDes, this->angle, NULL, SDL_FLIP_NONE);
    }
    if(alpha!=255){
        this->setAlpha(255);
    }
    return 1;
}

//hiển thị background
void Display::setDisplayBackGround(const Display& background){
    if(background.renderer == NULL){
        cerr << "Invalid Background" << endl;
    }
    else{
        this->originPoint.x = background.originPoint.x+background.xRender;
        this->originPoint.y = background.originPoint.y+background.yRender;
        this->xRelativeRatio = double(this->xRender)/double(background.wRender);
        this->yRelativeRatio = double(this->yRender)/double(background.hRender);
        this->wRelativeRatio = double(this->wRender)/double(background.wRender);
        this->hRelativeRatio = double(this->hRender)/double(background.hRender);
        this->displayBackground = &background;
    }
}

//hàm trả lại false khi texture = NULL
bool Display::loadTexture(string path, bool colorKey){
    SDL_Surface* tmp = IMG_Load(path.c_str());
    if(tmp==NULL){
        cout << "Could not to load image" << endl << "Error:" << SDL_GetError() << endl;
    }
    else{
        if(colorKey)SDL_SetColorKey(tmp,SDL_TRUE,SDL_MapRGB(tmp->format,this->Red,this->Green,this->Blue));
        SDL_Texture* newTexture=SDL_CreateTextureFromSurface(this->renderer,tmp);
        this->texture = newTexture;
        SDL_FreeSurface(tmp);
    };

    if(this->texture!=NULL && this->wRender==0 && this->hRender==0){
        SDL_QueryTexture(this->texture,NULL,NULL,&(this->wRender),&(this->hRender));
        SDL_QueryTexture(this->texture,NULL,NULL,&(this->widthTexture),&(this->heightTexture));
        return true;
    }
    else
        return false;
};

TextDisplay::TextDisplay(){}

TextDisplay::TextDisplay(TTF_Font* tFont,int font_size){
    this->font_size = font_size;
    this->tFont = tFont;
}

//tạo text trên texture
bool TextDisplay::makeTextTexture(const char* text, int size,SDL_Color color){
    if(this->texture!=NULL){
        SDL_DestroyTexture(this->texture);
        this->animationQueue.clear();
        this->texture=NULL;
    }
    SDL_Surface* tmpSurface = TTF_RenderText_Blended(this->tFont, text, color);
    if(tmpSurface==NULL){
        cerr << "Could not make Text Surface, TTF_Error: " << TTF_GetError();
        return false;
    }
    else{
        double ratio = double(size)/double(this->font_size);
        this->wRender=double(tmpSurface->w)*ratio;
        this->hRender=double(tmpSurface->h)*ratio;
        if(this->centerRender.x!=0&&this->centerRender.y!=0){
            this->xRender = this->centerRender.x-this->wRender/2;
            this->yRender = this->centerRender.y-this->hRender/2;
        }
        if(this->texture!=NULL){
            cout << "Text texture pointer isn't NULL to make Texture" << endl;
            return false;
        };
        this->texture = SDL_CreateTextureFromSurface(this->renderer,tmpSurface);
        if(this->texture==NULL){
            cout <<"Create Texture from Surface error: " << SDL_GetError() <<endl;
            return false;
        };
        SDL_FreeSurface(tmpSurface);
    }
    return true;
}

//render hiển thị text
void TextDisplay::render(bool renderWithCenterPoint){
    Display::render();
}

Button::Button(){}

Button::~Button(){
    if(buttonTexture["Mouse Over"]!=NULL) SDL_DestroyTexture(buttonTexture["Mouse Over"]);
    if(buttonTexture["Mouse Down"]!=NULL) SDL_DestroyTexture(buttonTexture["Mouse Down"]);
    if(buttonTexture["Mouse Up"]!=NULL) SDL_DestroyTexture(buttonTexture["Mouse Up"]);
    if(buttonTexture["Mouse Out"]!=NULL) SDL_DestroyTexture(buttonTexture["Mouse Out"]);
}

//tải button cho texture
void Button::loadTexture(string MouseOver, string MouseOut){
    Display::loadTexture(MouseOver);
    this->buttonTexture["Mouse Over"]=this->texture;
    this->buttonTexture["Mouse Down"]=this->texture;
    this->buttonTexture["Mouse Up"] = this->texture;

    Display::loadTexture(MouseOut);
    this->buttonTexture["Mouse Out"]=this->texture;
}

//sự kiện chuột
void Button::handleMouseEvent(SDL_Event* event){
    bool inside = true;
    if(event->type==SDL_MOUSEMOTION||event->type==SDL_MOUSEBUTTONUP||event->type==SDL_MOUSEBUTTONDOWN){
        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x,&mousePosition.y);
        //phím bên trái
        if(mousePosition.x<this->originPoint.x+this->xRender){
            inside=false;
        }
        //phím bên phải
        else if(mousePosition.x > this->originPoint.x+this->xRender+this->wRender){
            inside = false;
        }
        //phím bên trên
        else if(mousePosition.y < this->originPoint.y+this->yRender){
            inside = false;
        }
        //phím bên dưới
        else if(mousePosition.y > this->originPoint.y+this->yRender+this->hRender){
            inside = false;
        }
    }
    if(!inside) this->currentStatus = "Mouse Out";
    else{
        switch(event->type){
        case SDL_MOUSEMOTION:
            this->currentStatus = "Mouse Over";
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->currentStatus = "Mouse Down";
            break;
        case SDL_MOUSEBUTTONUP:
            this->currentStatus = "Mouse Up";
            break;
        }
    }
}

//cập nhật trạng thái sau khi click chuột
void Button::update(){
    previousStatus = currentStatus;
    this->texture = buttonTexture[currentStatus];
}

//tạo render hiển thị cập nhật
void Button::render(bool renderWithCenterPoint){
    Button::update();
    if((this->centerRender.x!=0||this->centerRender.y!=0)&&renderWithCenterPoint){
        this->xRender = this->centerRender.x-this->wRender/2;
        this->yRender = this->centerRender.y-this->hRender/2;
    }
    Display::render();
}
//click chuột để chuyển trạng thái
bool Button::Click(){
    return this->currentStatus=="Mouse Up"&&(this->previousStatus=="Mouse Down" || this->previousStatus=="Mouse Over");
};
//tải các frame
Sprite::Sprite(int framesNumber,int sheetRows, int sheetColumns,SDL_Rect frameRect, int framesPerSecond){
    this->framesNumber = framesNumber;
    this->sheetRows = sheetRows;
    this->sheetColumns = sheetColumns;
    this->frameRect = frameRect;
    this->framesPerSecond = framesPerSecond;
}
//tải render cho các frame và thời gian hiển thị
void Sprite::render(){
    if(this->preFrame == NULL){
        this->preFrame = SDL_GetTicks();
        this->clipImage (this->frameRect.x,this->frameRect.y,this->frameRect.w,this->frameRect.h);
    }
    else{
        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - this->preFrame>=1000/40){
            this->preFrame = currentTime;
            this->currentFrame = (this->currentFrame+1)%this->framesNumber;
        }

        int currentFrameRow = this->currentFrame/this->sheetColumns;
        int currentFrameColumn = this->currentFrame%this->sheetColumns;
        this->clipImage(this->frameRect.x+this->frameRect.w*currentFrameColumn,this->frameRect.y+this->frameRect.h*currentFrameRow,this->frameRect.w,this->frameRect.h);
    }
    Display::render();
}
