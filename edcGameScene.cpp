//
//  edcGameScene.cpp
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#include "edcGameScene.h"

USING_NS_CC;

Scene* edcGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = edcGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool edcGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    _mapLayer = edcMapLayer::create();
    addChild(_mapLayer);
    
    _hero = edcHeroLayer::create();
    _mapLayer->_map->addChild(_hero);
    
    _heroArray = Array::create();
    _heroArray->retain();
    
    _mapHeroArray = Array::create();
    _mapHeroArray->retain();
    
    initData();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(edcGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(edcGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(edcGameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void edcGameScene::initData()
{
    isPaused = false;
    _mapspeed = 4;
    _mapLayer->setPosition(ccp(Director::getInstance()->getVisibleSize().width / 2 ,
                               Director::getInstance()->getVisibleSize().height / 2 ));
    
    _hero->_preHero = NULL;
    _hero->_afterHero = NULL;
    _hero->setPosition(ccp(_mapLayer->_map->getContentSize().width / 2,
                           _mapLayer->_map->getContentSize().height / 2));
    
    
    setSpeed(mapSpeedDown);
    
    _heroArray->removeAllObjects();
    _heroArray->addObject(_hero);
    
    _mapHeroArray->removeAllObjects();
    
    unscheduleUpdate();
    scheduleUpdate();
    
    for (int i = 0; i < _mapHeroArray->count(); i++) {
        edcHeroLayer *heroTemp = (edcHeroLayer *)_mapHeroArray->objectAtIndex(i);
        _mapHeroArray->removeObjectAtIndex(i);
        heroTemp->removeFromParentAndCleanup(true);
    }
    
    edcHeroLayer *hero1 = edcHeroLayer::create();
    hero1->setPosition(ccpAdd(_hero->getPosition(), Point(200,200)));
    _mapLayer->_map->addChild(hero1);
    hero1->playAnim(animType_down);
    _mapHeroArray->addObject(hero1);
    
    edcHeroLayer *hero2 = edcHeroLayer::create();
    hero2->setPosition(ccpAdd(_hero->getPosition(), Point(-200,-200)));
    _mapLayer->_map->addChild(hero2);
    hero2->playAnim(animType_down);
    _mapHeroArray->addObject(hero2);
}

bool edcGameScene::isRectIn()
{

}
void edcGameScene::update(float dt)
{
    //碰撞检测
    checkCollide();
    
    //地图移动
    _mapLayer->setPosition(ccpAdd(_mapLayer->getPosition(), Point(_mapSpeedX,_mapSpeedY)) );
    
    edcHeroLayer *tempHero;
    for (int i = 0; i < _heroArray->count(); i++) {
        tempHero = (edcHeroLayer *)_heroArray->objectAtIndex(i);
        tempHero->setPosition(ccpAdd(tempHero->getPosition(),
                                     Point(-_mapSpeedX,-_mapSpeedY)));
    }
    
}

void edcGameScene::checkCollide()
{
    //墙
    if (isTouchWall()) {
        unscheduleUpdate();
        CCLOG("game over");
    }
    
    //队友
    if (isTeamMumber()) {
        _mapHeroArray->removeObject(_pickedTempHero);
        _pickedTempHero->setPosition(ccpAdd(_hero->getPosition(), Point(-64 * _heroArray->count(),0)));
        _heroArray->addObject(_pickedTempHero);

    }
    
}

bool edcGameScene::isTeamMumber()
{
    for (int i = 0; i < _mapHeroArray->count(); i++) {
        _pickedTempHero = (edcHeroLayer *)_mapHeroArray->objectAtIndex(i);
        Rect collideRect = Rect(_pickedTempHero->getPositionX(),
                                _pickedTempHero->getPositionY(),
                                _pickedTempHero->getContentSize().width,
                                _pickedTempHero->getContentSize().width);
        
        Rect heroRect = Rect(_hero->getPositionX() - 32,
                             _hero->getPositionY() - 32,
                             64,64);
        
        if (collideRect.intersectsRect(heroRect)) {
            return true;
        }else {
            continue;
        }
    }
    return false;
}

Rect edcGameScene::screenToTile(Rect screenRect)
{
    screenRect.origin.x;
    
    
    
}

Point edcGameScene::screenToTile(Point screenPos)
{
    //屏幕位置
    Point nowPos = _mapLayer->getPosition();
//    CCLOG("nowPos:%f,%f",nowPos.x,nowPos.y);
    Point winCenter = Point(Director::getInstance()->getVisibleSize().width / 2,
                            Director::getInstance()->getVisibleSize().height / 2);
    Point delta = ccpSub(nowPos, winCenter);//(320,480)
//    CCLOG("delta:%f,%f",delta.x,delta.y);
    
    //地图位置
    auto mapWidth = _mapLayer->_map->getTileSize().width * _mapLayer->_map->getMapSize().width;//块长64，块个数38个
//    CCLOG("--------tile:%f,map:%f",_mapLayer->_map->getTileSize().width,_mapLayer->_map->getMapSize().width);
    Point mapPos = Point(mapWidth / 2 - delta.x,
                         mapWidth / 2 + delta.y);
//    CCLOG("mapPos:%f,%f",mapPos.x,mapPos.y);
    Point blockPos = Point(mapPos.x / 64,
                           mapPos.y / 64);
    
//    CCLOG("blockPos:%f,%f",blockPos.x,blockPos.y);
    blockPos.x = floorf(blockPos.x);
    blockPos.y = floorf(blockPos.y);
//    CCLOG("blockPos:%f,%f",blockPos.x,blockPos.y);
    
    return blockPos;
}



bool edcGameScene::isTouchWall()
{
//    Point blockPos = screenToTile(_mapLayer->getPosition());
//    //碰撞检测
//    if (_mapLayer->isWallAtTileCoord(blockPos)) {
//        CCLOG("cjy yes");
//        return true;
//    }else {
//        CCLOG("cjy no");
//        return false;
//    }
//            CCLOG("******************** :%d",_mapLayer->collidePointArray->count());
    for (int i = 0; i < _mapLayer->_collidePointArray->count(); i++) {

        Point tempPoint = _mapLayer->_collidePointArray->getControlPointAtIndex(i);
        
        //地图上矩形的Rect
        Rect collideRect = Rect(tempPoint.x,
                                tempPoint.y,
                                _mapLayer->_map->getTileSize().width,
                                _mapLayer->_map->getTileSize().width);
//        CCLOG("collideRect:%f,%f,%f,%f",tempPoint.x,tempPoint.y,
//              _mapLayer->_map->getTileSize().width,
//              _mapLayer->_map->getTileSize().width);
        
        //地图上英雄的Rect
//        Point tempMap = Point(_mapLayer->_map->getTileSize().width * _mapLayer->_map->getMapSize().width / 2,
//                              _mapLayer->_map->getTileSize().width * _mapLayer->_map->getMapSize().width / 2);
//        Point tempHero = ccpAdd(ccpSub(_hero->getPosition(), _mapLayer->getPosition()),
//                                tempMap) ;
//        Rect heroRect = Rect(tempHero.x - 32 ,
//                             tempHero.y - 32,
//                             64,
//                             64);
//        CCLOG("heroRect:%f,%f,%d,%d",tempHero.x - 32,
//              tempHero.y - 32,
//              64,
//              64);
        Rect heroRect = Rect(_hero->getPositionX() - 32,
                             _hero->getPositionY() - 32,
                             64,64);
        
        if (collideRect.intersectsRect(heroRect)) {
            return true;
        }else {
            continue;
        }
    }
    
    return false;
}
void edcGameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



bool edcGameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Rect replayRect = Rect(0,0,100,100);
    if (replayRect.containsPoint(touch->getLocation())) {
        initData();
    }
    Rect pauseRect = Rect(540,0,100,100);
    if (pauseRect.containsPoint(touch->getLocation())) {
        if (isPaused) {
            isPaused = false;
            scheduleUpdate();
        }else{
            isPaused = true;
            unscheduleUpdate();
        }
    }
//    CCLOG("began");
    return true;
}

void edcGameScene::onTouchMoved(Touch *touch, Event *event)
{
    auto nowlocation = touch->getLocation();
    auto prelocation = touch->getPreviousLocation();
    
    auto delta = ccpSub(nowlocation, prelocation);
//    CCLOG("%f,%f",delta.x,delta.y);
    
    mapSpeed tempspeed = mapSpeedDown;
    if (delta.x > 0 && (fabs(delta.x) > fabs(delta.y))) {
//        CCLOG("right");
        tempspeed = mapSpeedLeft;
    }
    if (delta.x < 0 && (fabs(delta.x) > fabs(delta.y))) {
//        CCLOG("left");
        tempspeed = mapSpeedRight;
    }
    if (delta.y < 0 && (fabs(delta.x) < fabs(delta.y))) {
//        CCLOG("down");
        tempspeed = mapSpeedUp;
    }
    if (delta.y > 0 && (fabs(delta.x) < fabs(delta.y))) {
//        CCLOG("up");
        tempspeed = mapSpeedDown;
    }
//    CCLOG("move");
    setSpeed(tempspeed);
    
}
void edcGameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
//    CCLOG("end");
    
}

void edcGameScene::setHeroTeamAnim(animType tempAnim)
{
//    _hero->playAnim(animType_right);
    edcHeroLayer *tempHero;
    for (int i = 0; i < _heroArray->count(); i++) {
        tempHero = (edcHeroLayer *)_heroArray->objectAtIndex(i);
        tempHero->playAnim(tempAnim);
    }
}

void edcGameScene::setSpeed(mapSpeed tempSpeed)
{
    switch (tempSpeed) {
        case mapSpeedNull:
            _mapSpeedX = 0;
            _mapSpeedY = 0;
            break;
        case mapSpeedLeft:
            _mapSpeedX = -_mapspeed;
            _mapSpeedY = 0;
            setHeroTeamAnim(animType_right);
            break;
        case mapSpeedRight:
            _mapSpeedX = _mapspeed;
            _mapSpeedY = 0;
            setHeroTeamAnim(animType_left);
            break;
        case mapSpeedUp:
            _mapSpeedY = _mapspeed;
            _mapSpeedX = 0;
            setHeroTeamAnim(animType_down);
            break;
        case mapSpeedDown:
            _mapSpeedY = -_mapspeed;
            _mapSpeedX = 0;
            setHeroTeamAnim(animType_up);
            break;
            
        default:
            _mapSpeedX = 0;
            _mapSpeedY = 0;
            break;
    }
}




