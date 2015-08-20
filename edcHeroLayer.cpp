//
//  edcHeroLayer.cpp
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#include "edcHeroLayer.h"

#define kFileNameZwoptexChickSnake "Hero/chick_snake_default.plist"

USING_NS_CC;

// on "init" you need to initialize your instance

void edcHeroLayer::onEnter()
{
    Layer::onEnter();
}

void edcHeroLayer::onExit()
{
    Layer::onExit();
    CCSpriteFrameCache::getInstance()->removeSpriteFramesFromFile(kFileNameZwoptexChickSnake);
}

bool edcHeroLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(kFileNameZwoptexChickSnake);
    
    _hero = Sprite::create();
    _hero->setPosition( ccp( 0,0) );
    addChild(_hero);

    char szNameUp[100] = {0};
    sprintf(szNameUp, "snake_chick_up_");
    _actionUp = setHeroAnim(szNameUp, 4, 0.6);
    char szNameDown[100] = {0};
    sprintf(szNameDown, "snake_chick_down_");
    _actionDown = setHeroAnim(szNameDown, 4, 0.6);
    char szNameLeft[100] = {0};
    sprintf(szNameLeft, "snake_chick_left_");
    _actionLeft = setHeroAnim(szNameLeft, 4, 0.6);
    char szNameRight[100] = {0};
    sprintf(szNameRight, "snake_chick_right_");
    _actionRight = setHeroAnim(szNameRight, 4, 0.6);
    
    _actionUp->retain();
    _actionDown->retain();
    _actionLeft->retain();
    _actionRight->retain();
    
    _afterHero = NULL;
    _preHero = NULL;
    return true;
}

void edcHeroLayer::playAnim(animType whatType)
{
    _hero->stopAllActions();
    switch (whatType) {
        case animType_null:
            break;
        case animType_up:
            _hero->runAction(_actionUp);
            break;
        case animType_down:
            _hero->runAction(_actionDown);
            break;
        case animType_left:
            _hero->runAction(_actionLeft);
            break;
        case animType_right:
            _hero->runAction(_actionRight);
            break;
        default:
            _hero->runAction(_actionUp);
            break;
    }
}


Action *edcHeroLayer::setHeroAnim(char *aaname,int aaframes,float delayTime)
{
    auto animation = Animation::create();
    for( int i = 1;i <= aaframes ;i++)
    {
        char szName[100] = {0};
//        sprintf(szName, "snake_chick_up_%04d.png", i);
        sprintf(szName,"%s%04d%s",aaname,i,".png");
//        CCLOG("%s",szName);
        auto temp = Sprite::createWithSpriteFrameName(szName);
        animation->addSpriteFrame(temp->getSpriteFrame());
    }
    // should last 0.6 seconds. And there are 4 frames.
    animation->setDelayPerUnit(delayTime / (float)(aaframes));
    animation->setRestoreOriginalFrame(true);
    Action *temp = RepeatForever::create(Animate::create(animation));

    return temp;
}

void edcHeroLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}