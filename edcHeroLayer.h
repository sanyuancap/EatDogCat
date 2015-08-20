//
//  edcHeroLayer.h
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#ifndef __EatDogCat__edcHeroLayer__
#define __EatDogCat__edcHeroLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

//up snake_chick_up_0001.png - 4
//down snake_chick_down_0001.png - 4
//left snake_chick_left_0001.png - 4
//right snake_chick_right_0001.png - 4
//dog_1_up_01.png

enum heroType
{
    heroType_Dog_1 = 0,
    heroType_Dog_2,
    heroType_Dog_3,
    heroType_Cat_1,
    heroType_Cat_2,
    heroType_Cat_3,
};

enum animType
{
    animType_null= 0,
    animType_up,
    animType_down,
    animType_left,
    animType_right,
    
};
class edcHeroLayer : public cocos2d::Layer
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(edcHeroLayer);
    
    
    Action *setHeroAnim(char *name,int frames,float delayTime);
    void playAnim(animType whatType);

    edcHeroLayer *_preHero;
    edcHeroLayer *_afterHero;
    
    
    Sprite *_hero;
    heroType _myType;
    
    Action *_actionUp;
    Action *_actionDown;
    Action *_actionLeft;
    Action *_actionRight;
};

#endif /* defined(__EatDogCat__edcHeroLayer__) */
