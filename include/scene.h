/*
    002  Player's Name
...
008  YOUR DECK ISN'T READY!
009  YOUR DECK ISN'T READY! menu
00A  SETTLED!
00B  Trade Screen text
00C  WIN 0 LOSS 0
00D  SELECT OPPONENT!
00E  ?
00F  Debug menu text
010  2PDUEL
011  Card Shop menu (softlock)
012  NO YES
...
01C  YOU MUST PREPARE A DECK TO PLAY THE CAMPAIGN MODE!
...
020  Trade Screen validate
021  SELECT A GUARDIAN STAR (softlock)
022  QUIT DUEL? NO YES
023  SECRET NO. 00000000
024  1P'S DECK IS NOT READY
025  PvP Duel Screen text
026  Red 00000000 Blue 00000000
...
028  YOU CANNOT COMPETE WITH THE SAME DUELIST CODES!
029  YOU CANNOT TRADE WITH THE SAME DUELIST CODES!
...
03D  YOU
03E  YOU
03F  COM
040  Post-Duel text - TOTAL ANNIHILATION
041  Post-Duel text - VICTORY BY ATTRITION
042  Post-Duel text - SUMMON Exodia
043  Post-Duel text #2
044  Post-Duel text #2
045  Post-Duel text #2
...
0BA  DO NOT PLUG/UNPLUG MEMORY CARD IN slot 1
...
0BC  BACKUP DATA LOAD? START QUIT
0BD  ILLEGAL DATA!
0BE  NOW FORMATTING...
0BF  FORMAT COMPLETE!
0C0  ACCESSING MEMORY CARD (Trade menu)
0C1  MEMORY CARD NOT PLUGGED!
0C2  Memory Cards load Trade menu
0C3  MEMORY CARD slot 1 HAS BEEN REPLACED!
0C4  NOW TRADING CARD(S)
0C5  TRADE FAILED!
0C6  TRADE COMPLETE!
0C7  LOAD INCOMPLETE!
0C8  LOAD? YES NO
0C9  SAVE? YES NO
0CA  DOWNLOAD? YES NO
0CB  DOWNLOAD INCOMPLETE!
0CC  DOWNLOAD COMPLETE!
0CD  SAVE INCOMPLETE!
0CE  UNABLE TO LOCATE LOAD DATA!
0CF  OVERWRITE? YES NO
0D0  LOAD COMPLETE!
0D1  SAVE COMPLETE!
0D2  MEMORY CARD REQUIRED!
0D3  NO DATA!
0D4  ACCESSING MEMORY CARD
0D5  LOADING...
0D6  SAVING...
0D7  DOWNLOADING...
0D8  LOAD INCOMPLETE!
0D9  SAVE INCOMPLETE!
0DA  UNABLE TO ACCESS MEMORY CARD!
0DB  NOT ENOUGH FREE MEMORY BLOCKS!
0DC  DOWNLOAD INCOMPLETE!
0DD  FORMAT INCOMPLETE!
0DE  MEMORY CARD NOT FORMATTED!
0DF  FORMAT? NO YES
...
0E1  STARCHIP ×0
0E2  Please enter 'PASSWORD'
0E3  Password Card Cost text
...
400  to 4FF: copy of 500 to 5FF
500  Introduction
501  Simon Muran rant
502  Simon Muran pre-duel
503  Simon Muran (win)
504  Simon Muran (lose)
505  Simon Muran (cards mystics speech)
506  "There's nobody around..."
507  Teana #1 duel
508  Teana #1 re-duel
509  Teana #1 re-re-duel
50A  Teana #1 (before leaving to the festival)
50B  Teana #1 (dismissed)
50C  Villager #1 (before leaving to the festival)
50D  Villager #1 duel
50E  Villager #1 refuses re-duel
50F  Villager #2 duel
510  Villager #2 duel (same)
...
543  Heishin #1 rematch
551  Mai Valentine duel
552  Mai Valentine (win) - (softlock)
553  Mai Valentine (lose)
554  Bandit Keith duel
...
560  Pegasus duel
...
566  Seto Kaiba duel
567  Seto Kaiba (win)
568  Seto Kaiba (lose)
569  Yugi has all the Millenium Items cards - (softlock)
56A  Simon Muran returns you to Egypt
...
577  Give Map to Sadin (veryyyyy glitchy and laggy when Seto appears)
...
581  Discover Map to the Forbidden Ruins
...
583  Go to Hidden Dueling Grounds
...
58E  Water Mage re-duel
58F  Water Mage (lose)
590  Water Mage (win)
591  ?
592  ?
593  Secmeton duel
...
5AE  Desert Mage (win)
5AF  ?
5B0  ?
5B1  Martis duel
...
5C8  Heishin duel
...
5CF  Heishin comes back
5D0  Heishin threatens Seto
5D1  Heishin threatens Seto (refused to give items)
5D2  (softlock)
5D3  Darknite (lose)
5D4  Nitemare duel
5D5  Nitemare (lose)
5D6  Nitemare (win)
5D7  Ending
5D8  Card Shop - Egypt (post World Tournament)
5D9  Vast Temple Guard
5DA  Jono #2 duel
5DB  Teana #2 duel
...
5E0  Teana #2 duel (again)
...
5E5  Jono #2 (win)
...
5EC  Enter the Labyrinth
...
5F0  Teana is rescued
5F1  Labyrinth Guard duel
5F2  Labyrinth Guard (win)
5F3  Labyrinth Guard (lose)
5F4  Seto #2 (win)
5F5  Seto #2 (lose)
5F6  Prompt before Yami Temple
...
5F8  Festival ended
...
5FD  Post-Duel text
5FE  No Memory Card
...
602  Trade Screen text (again)
C00  Post-Duel text (again)
D00  T-Duel? NO YES
E00  Jono #1 duel prompt
FFF  CARDS USED      REMAINING LP */
enum Scene
{
    DUEL_SETUP = 0x2D0,
    DUEL_2P = 0x2C3
};
