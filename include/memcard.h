
/*
    This represents the data structure in FM save file block
*/
struct MemCard
{

    // Offset: 0x0
    // Description: ROM filename signature such as BASLUS-01411-YUGIOH
    char header_str[32];

    char blankFiller0[95];

    // Offset: 0x7F (127)
    // Description: Checksum to match the original game ROM (iirc)
    char checksum[69];

    char blankFiller1[28];

    char unkData[0x1A0];

    // Offset: 0x280 (640)

    // Description:
    // Player Data Profile that will be loaded into the game
    // Same structure as in the game

    struct
    {
        // Offset: 0x0
        short playerDeck[40];

        // Offset: 0x50 (80)
        char cardsInChest[722];

        char unkPlayerFill_12[0x12];

        // Offset: 0x334 (820)
        int duelistCode;

        char blankPlayerFill[8]; // Blank Filler

        // Offset: 0x340 (832)
        char unkPlayerData[64];

        char unkPlayerFill_174[0x174]; // Filler

        // Offset: 0x4F4 (1268)
        int freeDuelUnlocks;

        char unkPlayerFill_C4[0xC4]; // Filler

        // Offset: 0x5BC (1468)
        short last10CardsDrop[10];

        char unkPlayerFill_16[16]; // Filler

        // Offset: 0x5E0 (1504)
        int numStarchips;

        char unkPlayerFill_A1C[0xA1C];

        // MemcardProfile[0] - main profile to be first loaded
        // MemcardProfile[1] - Backup duplicate (same data) in case first profile is deemed 'Illegal'

    } MemcardProfile[2];
};