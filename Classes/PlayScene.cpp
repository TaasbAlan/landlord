//
//  PlayScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/24/14.
//
//

#include "PlayScene.h"
#include "WinScene.h"
#include "GameManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* PlayScene::scene()
{
  // 'scene' is an autorelease object
  CCScene *scene = CCScene::create();
  
  // 'layer' is an autorelease object
  PlayScene *layer = PlayScene::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !CCLayer::init() )
  {
    return false;
  }
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  setTouchEnabled(true);
  
//  addPlayGroud();
  makeMapScroll();
//  addFrameImg();
//  addPauseButton();
//  addPLayerOne();
//  addPlayerTwo();
//  addScoreLbn();
  
  return true;
}

void PlayScene::addPauseButton()
{
  CCSprite* btn = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* btnPause = CCMenuItemSprite::create(btn, btn, this, menu_selector(PlayScene::pauseButtonTouched));
  CCMenu* pMenu = CCMenu::create(btnPause, NULL);
  pMenu->setPosition(BTN_PAUSE_POS);
  addChild(pMenu);
}

void PlayScene::addPlayGroud()
{
  CCSprite *ground = CCSprite::create("PlayScene/background-playscene.png");
  ground->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(ground);
}

void PlayScene::addPLayerOne()
{
  playerOneTag = GameManager::getPlayerOneID();
  CCLog("getPlayerOneID = %d", GameManager::getPlayerOneID());
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne);
}

void PlayScene::addPlayerTwo()
{
  playerTwoTag = GameManager::getPlayerTwoID();
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo);
}

void PlayScene::makeMapScroll()
{
//  mIsScrolling = false;
  tileMap = CCTMXTiledMap::create("PlayScene/map01.tmx");
//  setTouchEnabled(true);
CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
  this->addChild(tileMap);
//  CCLog("%f %f", tileMap->getContentSize().width, tileMap->getContentSize().height);
  tileMap->setPosition(ccp(0, 0));
  mapLayer = tileMap->layerNamed("map01");

  
}

void PlayScene::addScoreLbn()
{
  CCSprite* scoreP1 = CCSprite::create("PlayScene/scoreP1.png");
  scoreP1->setPosition(LBN_SCORE_PLAYER1_POS);
  lbnScorePlayer1 = CCLabelTTF::create("0", "ordin", 50);
  lbnScorePlayer1->setHorizontalAlignment(kCCTextAlignmentCenter);
  lbnScorePlayer1->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  lbnScorePlayer1->setColor(ccRED);
  lbnScorePlayer1->setPosition(ccp(scoreP1->getPositionX()+scoreP1->getContentSize().width/2, scoreP1->getPositionY()));
//  scoreP1->addChild(lbnScorePlayer1);
  this->addChild(scoreP1);
  
  CCSprite* scoreP2 = CCSprite::create("PlayScene/scoreP2.png");
  scoreP2->setPosition(LBN_SCORE_PLAYER2_POS);
  lbnScorePlayer2 = CCLabelTTF::create("0", "ordin", 50);
  lbnScorePlayer2->setHorizontalAlignment(kCCTextAlignmentCenter);
  lbnScorePlayer2->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  lbnScorePlayer2->setColor(ccRED);
  lbnScorePlayer2->setPosition(ccp(scoreP2->getPositionX()+scoreP2->getContentSize().width/2, scoreP2->getPositionY()));
//  scoreP2->addChild(lbnScorePlayer2);
  this->addChild(scoreP2);
}

void PlayScene::pauseButtonTouched()
{
  CCLog("paused touched");
  CCScene* newScene = CCTransitionSlideInR::create(0.5, WinScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
}

void PlayScene::addFrameImg()
{
  CCSprite *frame = CCSprite::create("PlayScene/frame-01.png");
  frame->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(frame);
}

bool PlayScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  //  CCTouch *touch = (CCTouch*)pTouches->anyObject();
  mIsScrolling = false;
//  CCSetIterator it = pTouches->begin();
//  CCTouch *touch = (CCTouch*)(*it);
  
  beginLocation = pTouch->getLocation();
  beginLocation = this->convertToNodeSpace(beginLocation);
  beginLocationToMap = tileMap->convertToNodeSpace(beginLocation);
  
  return true;
  
//  CCLog("touch pos %f %f", beginLocation.x, beginLocation.y);
}

void PlayScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  mIsScrolling = true;
//  CCSetIterator it = pTouches->begin();
//  CCTouch *touch = (CCTouch*)(*it);
  
  CCPoint touchLocation = pTouch->getLocation();
  touchLocation = this->convertToNodeSpace(touchLocation);
  CCPoint touchLocationToMap = tileMap->convertToNodeSpace(touchLocation);
  
  float offsetX = touchLocation.x - beginLocation.x;
  float offsetY = touchLocation.y - beginLocation.y;
  moveMap(offsetX, offsetY);

  beginLocation = touchLocation;
  beginLocationToMap = touchLocationToMap;
}

void PlayScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  CCSprite *sp = CCSprite::create();
  CCSize s = mapLayer->getLayerSize();
  for (int i = 0; i < s.width; ++i)
  {
    for (int j = 0; j < s.height; ++j)
    {
      sp = mapLayer->tileAt(ccp(i, j));
      if (!mIsScrolling && sp && sp->boundingBox().containsPoint(beginLocationToMap))
      {
        CCLog("tile At %d %d", i, j);
        sp->setColor(ccRED);
      }
    }
  }
}

void PlayScene::registerWithTouchDispatcher() {
//  CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, -128);
//  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PlayScene::moveMap(float offsetX, float offsetY)
{
  float posX = tileMap->getPosition().x + offsetX;
  float posY = tileMap->getPosition().y + offsetY;
  if (posX > 0)
    posX = 0;
  if (posX < getBound().x)
    posX = getBound().x;
  if (posY > 0)
    posY = 0;
  if (posY < getBound().y)
  {
    posY = getBound().y;
  }
  tileMap->setPosition(ccp(posX, posY));
//  CCLog("map pos: %f %f", posX, posY);
}

CCPoint PlayScene::getBound()
{
  float mapWidth = tileMap->getTileSize().width * tileMap->getMapSize().width;
  float mapHeight = tileMap->getTileSize().height * tileMap->getMapSize().height;
  
  // should caculate the bounding of map position
  return ccp(screenSize.width - mapWidth, screenSize.height - mapHeight);
}

void PlayScene::addGlowEffect(CCSprite* sprite,
                   const ccColor3B& colour,
                   const CCSize& size)
{
  CCPoint pos = ccp(sprite->getPositionX(),
                    sprite->getPositionY());

  CCSprite* glowSprite = CCSprite::create("PlayScene/edge.png");
  glowSprite->setColor(colour);
  glowSprite->setPosition(pos);
  glowSprite->setRotation(sprite->getRotation());
  _ccBlendFunc f = {GL_ONE, GL_ONE};
  glowSprite->setBlendFunc(f);
  addChild(glowSprite, GR_FOREGROUND);
  // Run some animation which scales a bit the glow
  
  CCSequence* s1 =
    CCSequence::create(
      CCScaleTo::create(0.9f, size.width, size.height),
      CCScaleTo::create(0.9f, size.width*0.75f, size.height*0.75f),
      NULL);
  
  CCRepeatForever* r = CCRepeatForever::create(s1);
  glowSprite->runAction(r);
}
