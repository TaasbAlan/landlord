//
//  Constant.h
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "cocos2d.h"

USING_NS_CC;
// ChooseMapScene
#define BTN_RANDOM_POS  ccp(320, 245)
#define BTN_BACK_POS    ccp(49, 46)
#define NUMBER_MAPS     10
#define MAP_CENTER_POS  ccp(320, 357)
#define MAP_CENTER_X    320
#define MAP_CENTER_Y    779
#define MAP_WIDTH       328
#define DISTANCE_BETWEEN_MAPS   444
#define GREEN_DOT_Y     419

enum eGround
{
  GR_BACKGROUND,
  GR_MIDDLEGROUND,
  GR_FOREGROUND
};

#endif
