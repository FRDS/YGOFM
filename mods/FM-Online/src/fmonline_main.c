#include <common.h>

/* ASM Locations */
extern u_int *playerBeginMatch;
extern u_int *triangleText;
extern u_int *triangleImage;
extern u_int *playGsSound;
extern u_int *drawGsCursor[3] = {0x800370EC, 0x800371D0, 0x8003725C};
extern u_int *drawGsSymbols;
extern u_int *drawGsText;
extern u_char *lpDigits[2] = {0x80016F98, 0x80016F14};

/* ASM Instructions */
int triangleTextInst = 0x93860343;
int triangleImageInst = 0x24060004;
int playSoundInst = 0x0C00FFB8;
int drawGsCursorInst[3] = {0x0C00DBE0, 0x0C01001B, 0x0C00DBE0};
int drawTextInst = 0x0C00DB05;

char i, duelEnded, playing, changeTurn, switchedSides = 0;
char p1Begin = 1;

void ChangeCardView(char player)
{
	gp->DuelScreen[player].viewCard = 0;
	gp->DuelScreen[player + 1 % 2].viewCard = -1;
}

void AdjustLPString()
{
	for (i = 0; i < 2; i++)
	{
		if (gp->DuelScreen[i].LPActual > 9999)
			*lpDigits[i] = 5;
		else
			*lpDigits[i] = 4;
	}
}

void AdvanceSeed()
{
	int seed = gp->prngSeed;

	for (i = 0; i < 255; i++)
		seed = (seed * 0x41C64E6D) + 0x3039; // LCG using FM's params

	gp->prngSeed = seed;
}

void SwitchSides()
{
	if (gp->currentScene == DUEL_SETUP)
	{
		if (!switchedSides)
		{
			switchedSides = 1;
			duelEnded = 0;
			AdvanceSeed();
			if (p1Begin)
			{
				*playerBeginMatch = 0x90;
				p1Begin = 0;
			}
			else
			{
				*playerBeginMatch = 0x80;
				p1Begin = 1;
			}
		}
	}
	else
	{
		switchedSides = 0;
	}
}

void UpdateImgAndText(char player)
{
	if (player == gp->currentTurn)
	{
		*playGsSound = playSoundInst;
		for (i = 0; i < 3; ++i)
			*drawGsCursor[i] = drawGsCursorInst[i];
		*drawGsSymbols = drawTextInst;
		*drawGsText = drawTextInst;
		*triangleImage = triangleImageInst;
		*triangleText = triangleTextInst;
	}
	else
	{
		*playGsSound = 0;
		for (i = 0; i < 3; ++i)
			*drawGsCursor[i] = 0;
		*drawGsSymbols = 0;
		*drawGsText = 0;
		*triangleImage = 0;
		*triangleText = 0;
	}
}

void HandleGame(char player)
{
	if (duelEnded)
	{
		SwitchSides();
	}
	else
	{
		if (gp->currentScene == DUEL_2P)
		{
			short lp[2] = {gp->DuelScreen[0].LPActual, gp->DuelScreen[1].LPActual};
			ChangeCardView(player);

			if (!playing)
			{
				while (!lp[0] && !lp[0])
					ChangeCardView(player);
				playing = 1;
				UpdateImgAndText(player);
			}

			AdjustLPString();

			if (gp->currentTurn != player)
				UpdateImgAndText(player);

			if (!lp[0] && !lp[0])
				UpdateImgAndText(gp->currentTurn);
		}
		else
		{
			if (playing)
			{
				duelEnded = 1;
				playing = 0;
				UpdateImgAndText(gp->currentTurn);
			}
		}
	}
}

// Still trying to find where they process inputs to determine global player.
char DeterminePlayer()
{
	short pad1 = gp->GamePad.ButtonHeld[0];
	short pad2 = gp->GamePad.ButtonHeld[1];
	if ((pad1 > 0) && (!pad2))
		return 1;
	else if ((!pad1) && (pad2 > 0))
		return 2;
	else
		return 0;
}

// Hook into a function that runs every frame, Vsync()?
void fmOnline_main()
{
	char player;
	short scene;

	if (scene = gp->currentScene,
		scene != DUEL_SETUP && scene != DUEL_2P)
		return;

	if (!player)
		player = DeterminePlayer();
	else
		HandleGame(player - 1);
}