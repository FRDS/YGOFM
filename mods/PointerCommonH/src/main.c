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
	TEST16(&sdata_static),
    TEST16(&sdata_static.currentTurn),
    TEST16(&sdata_static.currentScene),
    TEST16(&sdata_static.DebugMenu.lastSoundID),
    TEST16(&sdata_static.DebugMenu.sceneOrSoundID),
    TEST16(&sdata_static.selectedCardID),
    TEST16(&sdata_static.opponentID),
    TEST16(&sdata_static.terrainType),
    TEST16(&sdata_static.DuelScreen[0].LPDisplay),
    TEST16(&sdata_static.DuelScreen[0].LPActual),
    TEST16(&sdata_static.DuelScreen[0].viewCard),
    TEST16(&sdata_static.DuelScreen[1].LPDisplay),
    TEST16(&sdata_static.DuelScreen[1].LPActual),
    TEST16(&sdata_static.DuelScreen[1].viewCard),
    TEST16(&sdata_static.fusionResult),
    TEST16(&sdata_static.prngSeed),
    TEST16(&sdata_static.playerDeckShuffle),
    TEST16(&sdata_static.cpuDeckShuffle),
    TEST16(&sdata_static.playerShuffledDeck),
    TEST16(&sdata_static.cpuShuffledDeck),
    TEST16(&sdata_static.cpuDeckPool),
    TEST16(&sdata_static.cardDrops_SA_POW),
    TEST16(&sdata_static.cardDrops_BCD),
    TEST16(&sdata_static.cardDrops_SA_TEC),
    TEST16(&sdata_static.rankTable),
    TEST16(&sdata_static.cardDropID),
    TEST16(&sdata_static.fusionTable),
    TEST16(&sdata_static.menuID),
    TEST16(&sdata_static.playerHand),
    TEST16(&sdata_static.cardPasswordsAndCosts),
    TEST16(&sdata_static.mainPlayerDeck),
    TEST16(&sdata_static.cardsInChest),
    TEST16(&sdata_static.freeDuelUnlocks),
    TEST16(&sdata_static.last10CardsDrop),
    TEST16(&sdata_static.numStarchips),
    TEST16(&sdata_static.cardDropID2)
};