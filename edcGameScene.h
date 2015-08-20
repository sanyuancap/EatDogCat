//
//  edcGameScene.h
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#ifndef __EatDogCat__edcGameScene__
#define __EatDogCat__edcGameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "edcMapLayer.h"
#include "edcHeroLayer.h"

enum mapSpeed
{
    mapSpeedNull = 0,
    mapSpeedLeft,
    mapSpeedRight,
    mapSpeedUp,
    mapSpeedDown,
};


class edcGameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(edcGameScene);
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void setSpeed(mapSpeed tempSpeed);
    bool isTouchWall();
    bool isTeamMumber();
    bool isRectIn();
    void checkCollide();
    void setHeroTeamAnim(animType tempAnim);
    void initData();
    Point screenToTile(Point screenPos);
    Rect screenToTile(Rect screenRect);
    
    edcMapLayer *_mapLayer;
    edcHeroLayer *_hero;
    edcHeroLayer *_pickedTempHero;
    Array *_heroArray;
    Array *_mapHeroArray;
    bool isPaused;
    float _mapSpeedX;
    float _mapSpeedY;
    float _mapspeed;
    
};


#endif /* defined(__EatDogCat__edcGameScene__) */
