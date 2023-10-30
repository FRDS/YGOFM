#include <common.h>

// This is not a mod,
// this tests addresses
// in common.h to see if
// we make mistakes

struct x
{
	int a,b,c,d;
};

#define TEST16(x) { (int)x, 0,0,0 }

// by aligning everything to 16 bytes,
// it makes the binary easier to read
// in hex editors like HxD

struct x y[] =
{
	TEST16(&gp_static),
    TEST16(&gp_static.currentTurn),
    TEST16(&gp_static.currentScene),
    TEST16(&gp_static.DebugMenu.lastSoundID),
    TEST16(&gp_static.DebugMenu.sceneOrSoundID),
    TEST16(&gp_static.selectedCardID),
    TEST16(&gp_static.opponentID),
    TEST16(&gp_static.terrainType),
    TEST16(&gp_static.GamePad.ButtonHeld[0]),
    TEST16(&gp_static.GamePad.ButtonHeld[1]),
    TEST16(&gp_static.GamePad.ButtonUpdateCurrFrame[0]),
    TEST16(&gp_static.GamePad.ButtonUpdateCurrFrame[1]),
    TEST16(&gp_static.GamePad.ButtonTapped[0]),
    TEST16(&gp_static.GamePad.ButtonTapped[1]),
    TEST16(&gp_static.GamePad.ButtonHeldBackup[0]),
    TEST16(&gp_static.GamePad.ButtonHeldBackup[1]),
    TEST16(&gp_static.DuelScreen[0].LPDisplay),
    TEST16(&gp_static.DuelScreen[0].LPActual),
    TEST16(&gp_static.DuelScreen[0].viewCard),
    TEST16(&gp_static.DuelScreen[1].LPDisplay),
    TEST16(&gp_static.DuelScreen[1].LPActual),
    TEST16(&gp_static.DuelScreen[1].viewCard),
    TEST16(&gp_static.fusionResult),
    TEST16(&gp_static.prngSeed),
    TEST16(&gp_static.playerDeckShuffle),
    TEST16(&gp_static.cpuDeckShuffle),
    TEST16(&gp_static.playerShuffledDeck),
    TEST16(&gp_static.cpuShuffledDeck),
    TEST16(&gp_static.cpuDeckPool),
    TEST16(&gp_static.cardDrops_SA_POW),
    TEST16(&gp_static.cardDrops_BCD),
    TEST16(&gp_static.cardDrops_SA_TEC),
    TEST16(&gp_static.rankTable),
    TEST16(&gp_static.cardDropID),
    TEST16(&gp_static.fusionTable),
    TEST16(&gp_static.menuID),
    TEST16(&gp_static.PlayerHand),
    TEST16(&gp_static.cardPasswordsAndCosts),
    TEST16(&gp_static.PlayerProfile[0].playerDeck),
    TEST16(&gp_static.PlayerProfile[0].cardsInChest),
    TEST16(&gp_static.PlayerProfile[0].duelistCode),
    TEST16(&gp_static.PlayerProfile[0].freeDuelUnlocks),
    TEST16(&gp_static.PlayerProfile[0].last10CardsDrop),
    TEST16(&gp_static.PlayerProfile[0].numStarchips),
    TEST16(&gp_static.PlayerProfile[1].playerDeck),
    TEST16(&gp_static.cardDropID2)
};