#include <common.h>

extern u_int triangleText;
extern u_int triangleImage;
extern u_int playGsSound;
extern u_int drawGsSymbols;
extern u_int drawGsText;
extern u_int drawGsCursor0;
extern u_int drawGsCursor1;
extern u_int drawGsCursor2;
extern u_char lpDigits0, lpDigits1, playerBeginMatch;

/* ASM Instructions */
int triangleTextInst = 0x93860343;
int triangleImageInst = 0x24060004;
int playSoundInst = 0x0C00FFB8;
int drawGsCursorInst[3] = {0x0C00DBE0, 0x0C01001B, 0x0C00DBE0};
int drawTextInst = 0x0C00DB05;

char duelEnded, playing, switchedSides = 0;
char this_player = -1;
char p1Begin = 1;

void ChangeCardView(char player)
{
	gp->DuelStats[player * 2].viewCard = 0;
	gp->DuelStats[((!player) ? 2 : 0)].viewCard = -1;
}

void AdvanceSeed()
{
	int seed = gp->prngSeed;

	for (short i = 0; i < 255; i++)
		seed = (seed * 0x41C64E6D) + 0x3039; // LCG using FM's params

	gp->prngSeed = seed;
}

void SwitchSides()
{
	if (gp->currentScene == DUEL_SETUP && !switchedSides)
	{
		switchedSides = 1;
		duelEnded = 0;
		AdvanceSeed();
		// switch to P2 and back after every match
		playerBeginMatch = (p1Begin) ? 0x90 : 0x80;
		p1Begin = !p1Begin;
	}
}

void UpdateImgAndText(char player)
{
	if (player == gp->currentTurn)
	{
		playGsSound = playSoundInst;
		drawGsCursor0 = drawGsCursorInst[0];
		drawGsCursor1 = drawGsCursorInst[1];
		drawGsCursor2 = drawGsCursorInst[2];
		drawGsSymbols = drawTextInst;
		drawGsText = drawTextInst;
		triangleImage = triangleImageInst;
		triangleText = triangleTextInst;
	}
	else
	{
		playGsSound = 0;
		drawGsCursor0 = 0;
		drawGsCursor1 = 0;
		drawGsCursor2 = 0;
		drawGsSymbols = 0;
		drawGsText = 0;
		triangleImage = 0;
		triangleText = 0;
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
		char currentTurn = gp->currentTurn;
		if (gp->currentScene == DUEL_2P)
		{
			short lp[2] = {gp->DuelStats[0].LPActual, gp->DuelStats[2].LPActual};
			if (!playing)
			{
				if (!lp[0] && !lp[1]) // if still loading don't change view yet
					return;
				ChangeCardView(player);
				playing = 1;
				switchedSides = 0;
			}
			else
			{
				// LP Num digits based on value
				lpDigits0 = (lp[0] > 9999) ? 5 : 4;
				lpDigits1 = (lp[1] > 9999) ? 5 : 4;

				UpdateImgAndText(player);

				if (!lp[0] && !lp[1])
					UpdateImgAndText(currentTurn);
			}
		}
		else
		{
			if (playing)
			{
				duelEnded = 1;
				playing = 0;
				UpdateImgAndText(currentTurn);
			}
		}
	}
}

// Still trying to find where they process inputs to determine global player.
char DeterminePlayer()
{
	short pad1 = gp->GamePad.ButtonHeld[0];
	short pad2 = gp->GamePad.ButtonHeld[1];
	return (pad1 > 0 && !pad2) ? 0 : ((!pad1 && pad2 > 0) ? 1 : -1);
}

// Hook into a function that runs every frame, Vsync()?
void fmOnline_main()
{
	short scene = gp->currentScene;

	if (scene != DUEL_SETUP && scene != DUEL_2P)
		return;

	if (this_player < 0)
		this_player = DeterminePlayer();
	else
		HandleGame(this_player);
}