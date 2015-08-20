//
//  edcMapLayer.h
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#ifndef __EatDogCat__edcMapLayer__
#define __EatDogCat__edcMapLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class edcMapLayer : public cocos2d::Layer
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool isWallAtTileCoord(const Point &tileCoord);
    
    // implement the "static create()" method manually
    CREATE_FUNC(edcMapLayer);
    
    TMXTiledMap *_map;
    
    PointArray *_collidePointArray;
    void fillInCollideArray();
    

};


#endif /* defined(__EatDogCat__edcMapLayer__) */
