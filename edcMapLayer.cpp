//
//  edcMapLayer.cpp
//  EatDogCat
//
//  Created by easegame on 15/8/4.
//
//

#include "edcMapLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance



bool edcMapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    _map = TMXTiledMap::create("TiledMap/snake02.tmx");
    _map->setAnchorPoint(Point(0.5,0.5));
    _map->setPosition(Point(0,0));
    addChild(_map);
    
    _collidePointArray = PointArray::create(_map->getMapSize().width * _map->getMapSize().width);
    _collidePointArray->retain();
    fillInCollideArray();
    
    
    return true;
}

void edcMapLayer::fillInCollideArray()
{
    TMXLayer *nowlayer = _map->getLayer("groundLayer");
    auto tileNum = _map->getMapSize().width;
    for (int i = 0 ; i < tileNum; i++) {
        for (int j = 0; j < tileNum; j++) {
            int gid = nowlayer->getTileGIDAt(Point(i ,j));
            Value properties = _map->getPropertiesForGID(gid);
            
            if (properties.isNull())
            {
                continue;
                
            }else if(properties.asValueMap()["collide"].asInt() == 1){
//                CCLOG("cjy : %d,%d",i,j);
                int x = i * _map->getTileSize().width;
                int y = (_map->getMapSize().width - j - 1) * _map->getTileSize().width;
                _collidePointArray->addControlPoint(Point(x,y));
                
//                CCLOG("cjy : %d,%d",x,y);
            }

        }
    }

    
}

bool edcMapLayer::isWallAtTileCoord(const Point &tileCoord)
{
    //先获取格子的gid值，再获取属性值
    TMXLayer *nowlayer = _map->getLayer("groundLayer");
    int gid = nowlayer->getTileGIDAt(tileCoord);
    Value properties = _map->getPropertiesForGID(gid);
    if (properties.isNull())
    {
        return false;
    }
    return properties.asValueMap().find("collide") != properties.asValueMap().end();
}

void edcMapLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}