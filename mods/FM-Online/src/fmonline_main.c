#include <common.h>

/* ASM Locations */
u_int *maxLPDigits[2] = {0x80016F98, 0x80016F14};
u_int *playerBeginMatch = 0x80017AF2;
u_int *triangleText = 0x800284D8;
u_int *triangleImage = 0x8002946C;
u_int *playGsSound = 0x800370E4;
u_int *drawGsCursor[3] = {0x800370EC, 0x800371D0, 0x8003725C};
u_int *drawGsSymbols = 0x80037FF4;
u_int *drawGsText = 0x80039730;
u_char *lpDigits[2] = {0x80016F98, 0x80016F14};

/* ASM Instructions */
int triangleText = 0x93860343;
int triangleImage = 0x24060004;
int playSound = 0x0C00FFB8;
int drawGsCursor[3] = {0x0C00DBE0, 0x0C01001B, 0x0C00DBE0};
int drawText = 0x0C00DB05;

char i, duelEnded, playing, changeTurn, switchedSides = 0;
char p1Begin = 1;

void ChangeCardView(char player)
{
	sdata->DuelScreen[player].viewCard = 0;
	sdata->DuelScreen[player + 1 % 2].viewCard = -1;
}

void AdjustLPString()
{
	for (i = 0; i < 2; i++)
	{
		if (sdata->DuelScreen[i].LPActual > 9999)
			*lpDigits[i] = 5;
		else
			*lpDigits[i] = 4;
	}
}

void AdvanceSeed()
{
	int seed = sdata->prngSeed;

	for (i = 0; i < 255; i++)
		seed = (seed * 0x41C64E6D) + 0x3039; // LCG using FM's params

	sdata->prngSeed = seed;
}

void SwitchSides()
{
	if (sdata->currentScene == DUEL_SETUP)
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
	if (player == sdata->currentTurn)
	{
		*playGsSound = playGsSound;
		for (i = 0; i < 3; ++i)
			*drawGsCursor[i] = drawGsCursor;
		*drawGsSymbols = drawGsSymbols;
		*drawGsText = drawGsText;
		*triangleImage = triangleImage;
		*triangleText = triangleText;
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

char LoadingLifePoints()
{
	char loading = 0;
	for (int i = 0; i < 2; ++i)
	{
		if (!sdata->DuelScreen[i].LPActual)
			loading = 1;
	}
	return loading;
}

void CheckEndOfDuel()
{
	char ended = 0;
	for (int i = 0; i < 2; ++i)
	{
		if (!sdata->DuelScreen[i].LPActual)
			ended = 1;
	}
	if (ended)
		UpdateImgAndText(sdata->currentTurn);
}

void HandleGame(char player)
{
	if (duelEnded)
	{
		SwitchSides();
	}
	else
	{
		if (sdata->currentScene == DUEL_2P)
		{
			ChangeCardView(player);

			if (!playing)
			{
				while (LoadingLifePoints())
					ChangeCardView(player);
				playing = 1;
				UpdateImgAndText(player);
			}

			AdjustLPString();
			if (sdata->currentTurn != player)
				UpdateImgAndText(player);

			CheckEndOfDuel();
		}
		else
		{
			if (playing)
			{
				duelEnded = 1;
				playing = 0;
				UpdateImgAndText(sdata->currentTurn);
			}
		}
	}
}

// Still trying to find where they process inputs to determine global player.
char DeterminePlayer()
{
}

// Hook into a function that runs every frame, Vsync()?
void fmOnline_main()
{
	if (sdata->currentScene != DUEL_SETUP && sdata->currentScene != DUEL_2P)
		return;
	char player = DeterminePlayer();
	HandleGame(player);
}