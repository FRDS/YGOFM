#include <common.h>

void ChangeCardView(char player)
{
    sdata->DuelScreen[player].viewCard = 0;
    sdata->DuelScreen[player % 2].viewCard = -1;
}

void AdjustLPString()
{
	for (int i = 0; i < numPlayers; i++)
	{
		ReadMem(RAM::lp[i] - 2, &lp[i], sizeof(lp[i]));
		if (lp[i] > 9999)
			WriteMem(RAM::maxLPDigits[i], &Cheat::maxLPDigits, sizeof(Cheat::maxLPDigits));
		else
			WriteMem(RAM::maxLPDigits[i], &Cheat::minLPDigits, sizeof(Cheat::minLPDigits));
	}
}

void HookDuelistCodeBypass()
{
	WriteMem(RAM::duelistCode, &Cheat::nop, sizeof(Cheat::nop));
	WriteMem(RAM::duelistCodeRet, &Cheat::duelistCodeRet, sizeof(Cheat::duelistCodeRet));
}

char SceneIsPvP()
{
	ReadMem(RAM::currentScene, &currentScene, sizeof(currentScene));
	return currentScene == PvPScene;
}

char SceneIsDuel()
{
	ReadMem(RAM::currentScene, &currentScene, sizeof(currentScene));
	return currentScene == duelScene;
}

char TurnTransitioned()
{
	ReadMem(RAM::currentTurn, &currentTurn, sizeof(currentTurn));

	if (currentTurn != lastTurn)
	{
		lastTurn = currentTurn;
		return true;
	}
	return false;
}

void SetSeed()
{
	ReadMem(RAM::prng, &seed, sizeof(seed));
	cout << "\nSeed: 0x" << hex << seed << ". Make sure that your seed is synchronized with your opponent's starting seed." << endl;
}

void AdvanceSeed()
{
	for (int i = 0; i < 255; i++)
		seed = (seed * 0x41C64E6D) + 0x3039; // LCG using FM's params

	WriteMem(RAM::prng, &seed, sizeof(seed));
}

void RemoveTrapRotation()
{
	for (int i = 0; i < numTrapRotInst; ++i)
		WriteMem(RAM::trapRot[i], &Cheat::nop, sizeof(Cheat::nop));
}

void SwitchSides()
{
	if (SceneIsPvP())
	{
		if (!switchedSides)
		{
			switchedSides = true;
			duelEnded = false;
			AdvanceSeed();
			if (p1Begin)
			{
				WriteMem(RAM::playerBeginMatch, &Cheat::playerBeginMatch[1], sizeof(Cheat::playerBeginMatch[1]));
				p1Begin = false;
			}
			else
			{
				WriteMem(RAM::playerBeginMatch, &Cheat::playerBeginMatch[0], sizeof(Cheat::playerBeginMatch[0]));
				p1Begin = true;
			}
		}
	}
	else
	{
		switchedSides = false;
	}
}

void UpdateImgAndText(char player)
{
	if (player == currentTurn)
	{
		WriteMem(RAM::playGsSound, &Cheat::playSound, sizeof(Cheat::playSound));
		for (int i = 0; i < numDrawCursorInst; ++i)
			WriteMem(RAM::drawGsCursor[i], &Cheat::drawGsCursor[i], sizeof(Cheat::drawGsCursor[i]));
		WriteMem(RAM::drawGsSymbols, &Cheat::drawText, sizeof(Cheat::drawText));
		WriteMem(RAM::drawGsText, &Cheat::drawText, sizeof(Cheat::drawText));
		WriteMem(RAM::triangleImage, &Cheat::triangleImage, sizeof(Cheat::triangleImage));
		WriteMem(RAM::triangleText, &Cheat::triangleText, sizeof(Cheat::triangleText));
	}
	else
	{
		WriteMem(RAM::playGsSound, &Cheat::nop, sizeof(Cheat::nop));
		for (int i = 0; i < numDrawCursorInst; ++i)
			WriteMem(RAM::drawGsCursor[i], &Cheat::nop, sizeof(Cheat::nop));
		WriteMem(RAM::drawGsSymbols, &Cheat::nop, sizeof(Cheat::nop));
		WriteMem(RAM::drawGsText, &Cheat::nop, sizeof(Cheat::nop));
		WriteMem(RAM::triangleImage, &Cheat::nop, sizeof(Cheat::nop));
		WriteMem(RAM::triangleText, &Cheat::nop, sizeof(Cheat::nop));
	}
}

char LoadingLifePoints()
{
	char loading = false;
	for (int i = 0; i < numPlayers; ++i)
	{
		ReadMem(RAM::lp[i], &lp[i], sizeof(lp[i]));
		if (!lp[i])
			loading = true;
	}
	return loading;
}

void CheckEndOfDuel()
{
	char ended = false;
	for (int i = 0; i < numPlayers; ++i)
	{
		ReadMem(RAM::lp[i], &lp[i], sizeof(lp[i]));
		if (!lp[i])
			ended = true;
	}
	if (ended)
		UpdateImgAndText(currentTurn);
}

void HandleGame(char player)
{
	if (duelEnded)
	{
		SwitchSides();
	}
	else
	{
		if (SceneIsDuel())
		{
			ChangeCardView(player);
			if (!playing)
			{
				while (LoadingLifePoints())
					ChangeCardView(player);
				playing = true;
				TurnTransitioned();
				UpdateImgAndText(player);
			}

			AdjustLPString();
			if (TurnTransitioned())
				UpdateImgAndText(player);

			CheckEndOfDuel();
		}
		else
		{
			if (playing)
			{
				duelEnded = true;
				playing = false;
				UpdateImgAndText(currentTurn);
			}
		}
	}
}