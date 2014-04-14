//
//  GameManager Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/14/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "GameManager.h"
//#import "Constant.h"

@interface GameManager_Tests : SenTestCase

@end

@implementation GameManager_Tests

- (void) testGetAndSetMusicState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getMusicState(), @"initial music state is true");
  
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state to false");
  
  gameManager.setMusicState();
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state twice");
}

- (void) testGetAndSetSoundState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getSoundState(), @"initial sound state is true");
  
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state to false");
  
  gameManager.setSoundState();
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state twice");
}

- (void) testGetAndSetTreeModeState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getTreeModeState(), @"initial tree mode state is true");
  
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state to false");
  
  gameManager.setTreeModeState();
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state twice");
}

- (void) testGetAndSetPlayerOneID
{
  GameManager gameManager;
  STAssertEquals(1, gameManager.getPlayerOneID(), @"initial player one ID is 1");
  
  gameManager.setPlayerOneID(4);
  STAssertEquals(4, gameManager.getPlayerOneID(), @"set player one ID of 4");
}

- (void) testGetAndSetPlayerTwoID
{
  GameManager gameManager;
  STAssertEquals(1, gameManager.getPlayerTwoID(), @"initial player two ID is 1");
  
  gameManager.setPlayerTwoID(7);
  STAssertEquals(7, gameManager.getPlayerTwoID(), @"set player two ID of 7");
}

- (void) testIncreaseAndGetPlayerScore
{
  GameManager gameManager;
  STAssertEquals(0, gameManager.getPlayerScore(1), @"initial player one score is 0");
  STAssertEquals(0, gameManager.getPlayerScore(2), @"initial player two score is 0");
  
  gameManager.increaseScore(1);
  STAssertEquals(1, gameManager.getPlayerScore(1), @"increase player one score to 1");
  
  gameManager.increaseScore(2);
  gameManager.increaseScore(2);
  STAssertEquals(2, gameManager.getPlayerScore(2), @"increase player two score to 2");
}

- (void) testInitPlayersInfo
{
  GameManager gameManager;
  gameManager.initPlayersInfo();
  
  STAssertEquals(0, gameManager.getPlayerScore(1), @"initial player one score is 0");
  STAssertEquals(0, gameManager.getPlayerScore(2), @"initial player two score is 0");
  STAssertEquals(1, gameManager.getCurrentPlayer(), @"initial current player is player one");
}

- (void) testGetAndChangeCurrentPlayer
{
  GameManager gameManager;
  STAssertEquals(1, gameManager.getCurrentPlayer(), @"initial current player is 1");
  
  gameManager.changeCurrentPlayer();
  STAssertEquals(2, gameManager.getCurrentPlayer(), @"change current player to 2");
  
  gameManager.changeCurrentPlayer();
  gameManager.changeCurrentPlayer();
  STAssertEquals(2, gameManager.getCurrentPlayer(), @"change current player twice");
}

- (void) testGetAndSetWinPlayer
{
  GameManager gameManager;
  gameManager.setWinPlayer(1);
  STAssertEquals(1, gameManager.getWinPlayer(), @"set win player is player one");
  
  gameManager.setWinPlayer(2);
  STAssertEquals(2, gameManager.getWinPlayer(), @"set win player is player two");
}



@end
