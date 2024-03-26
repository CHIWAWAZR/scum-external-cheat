#pragma once
#include "Main.h"

namespace visuals
{
	bool simplechest = false;
	bool ornateechest = false;
	bool skeleton = false;
	bool trap = false;
	bool mob = false;
	bool sentry = false;
	bool goldchest = false;
	bool gravity = false;
	bool mummy = false;
	bool giant = false;
	bool goblin = false;
	bool zombie = false;
	bool box = false;
	bool player = false;
	bool aim = false;
	int aimkey = 0;
	bool demon = false;
	bool ghost = false;
	bool item = false;
	bool tracers = false;
	bool healthbar = false;
	bool fullbright = false;
	bool drone = false;
	bool pallet = false;
	bool Explosive = false;
	bool hook = false;
	bool bear = false;
	bool generator = false;
	bool genHUD = false;
	bool totem = false;
	bool name = false;
	bool print = false;


	bool slasher = false;
	bool window = false;
	bool exit = false;
	bool killerping = false;
	bool outline = false;
	bool lines = false;
	bool chest = false;
	bool closet = false;
	bool hatch = false;
	bool door = false;
	bool team = false;
	bool team_name = false;
	bool skillcheck = true;
	bool killerinfo = false;
	bool teaminfo = false;
	bool killerAura = false;
	bool TrapAura = false;
	bool survAura = false;
	bool survSkeleton = false;
	bool snowman = false;

	bool speedhackbool = false;
	bool speedKey = false;
	bool speedKeyInput = false;
	bool lock = false;

	bool crosshair = false;

	int boxMode = 0;
	int skelMode = 0;
	int lineMode = 0;
	bool fov = false;
	float fovvalue = 120;
	bool Anonymous = false;
	bool Radar = false;
	bool PlayerRadar = false;
	bool KillerRadar = false;
	bool GeneratorRadar = false;
	float distance = 100;
	float AimbotFOV = 10.0f;
	float speedhack = 5.0f;
	float Smoothing = 1.0f;
	float distanceaim = 50;
	int KillerPickerInt = 0;
	bool KillerPicking = false;
}

//->TEST DE SYSTEME DE SAUVEGARDE
void WriteElem(FILE* save, int valeur)
{
	fprintf(save, "%d ", valeur);
}

//void ReadSettings()
//{
//	FILE* save = fopen("settings.stern", "r");
//	if (save != NULL)
//	{
//		int tempint = 33;
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::pallet = true;
//		}
//		else
//		{
//			visuals::pallet = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::hook = true;
//		}
//		else
//		{
//			visuals::hook = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::generator = true;
//		}
//		else
//		{
//			visuals::generator = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::totem = true;
//		}
//		else
//		{
//			visuals::totem = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::name = true;
//		}
//		else
//		{
//			visuals::name = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::slasher = true;
//		}
//		else
//		{
//			visuals::slasher = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::window = true;
//		}
//		else
//		{
//			visuals::window = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::exit = true;
//		}
//		else
//		{
//			visuals::exit = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::box = true;
//		}
//		else
//		{
//			visuals::box = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::killerbox = true;
//		}
//		else
//		{
//			visuals::killerbox = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::chest = true;
//		}
//		else
//		{
//			visuals::chest = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::closet = true;
//		}
//		else
//		{
//			visuals::closet = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::hatch = true;
//		}
//		else
//		{
//			visuals::hatch = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::survAura = true;
//		}
//		else
//		{
//			visuals::survAura = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::killerAura = true;
//		}
//		else
//		{
//			visuals::killerAura = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::door = true;
//		}
//		else
//		{
//			visuals::door = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::Radar = true;
//		}
//		else
//		{
//			visuals::Radar = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::PlayerRadar = true;
//		}
//		else
//		{
//			visuals::PlayerRadar = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::KillerRadar = true;
//		}
//		else
//		{
//			visuals::KillerRadar = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::GeneratorRadar = true;
//		}
//		else
//		{
//			visuals::GeneratorRadar = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::Anonymous = true;
//		}
//		else
//		{
//			visuals::Anonymous = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::killerinfo = true;
//		}
//		else
//		{
//			visuals::killerinfo = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::killerping = true;
//		}
//		else
//		{
//			visuals::killerping = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::speedhackbool = true;
//		}
//		else
//		{
//			visuals::speedhackbool = false;
//		}
//
//		fscanf(save, "%d", &tempint);
//		if (tempint == 1)
//		{
//			visuals::speedKey = true;
//		}
//		else
//		{
//			visuals::speedKey = false;
//		}
//
//		fclose(save);
//	}
//}
//
//void WriteSettings()
//{
//	FILE* save = fopen("settings.stern", "w+");
//	if (save != NULL)
//	{
//		if (visuals::pallet)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::hook)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::generator)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::totem)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::name) //surv ESP
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::slasher)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::window)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::exit)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::box)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::killerbox)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		//if (visuals::outline) //?
//		//{
//		//	WriteElem(save, 1);
//		//}
//		//else
//		//{
//		//	WriteElem(save, 0);
//		//}
//		if (visuals::chest)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::closet)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::hatch)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::survAura)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::killerAura)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::door)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::Radar)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::PlayerRadar)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::KillerRadar)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::GeneratorRadar)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::Anonymous)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::killerinfo)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::killerping)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		//if (visuals::skillcheck)
//		//{
//		//	WriteElem(save, 1);
//		//}
//		//else
//		//{
//		//	WriteElem(save, 0);
//		//}
//		if (visuals::speedhackbool)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//		if (visuals::speedKey)
//		{
//			WriteElem(save, 1);
//		}
//		else
//		{
//			WriteElem(save, 0);
//		}
//
//		fclose(save);
//	}
//}

/*
aperçu des seetings :

	bool pallet = false;
	bool hook = false;
	bool bear = false;
	bool generator = false;
	bool totem = false;
	bool name = false;
	bool slasher = false;
	bool window = false;
	bool exit = false;
	bool box = false;
	bool killerbox = false;
	bool killerping = false;
	bool outline = false;
	bool lines = false;
	bool chest = false;
	bool closet = false;
	bool hatch = false;
	bool door = false;
	bool team = false;
	bool team_name = false;
	bool skillcheck = false;
	bool killerinfo = false;
	bool killerAura = false;
	bool TrapAura = false;
	bool survAura = false;

	bool speedhackbool = false;
	bool speedKey = false;
	bool speedKeyInput = false;

	int boxMode = 0;
	int skelMode = 0;
	int lineMode = 0;

	bool Anonymous = false;
	bool Radar = false;
	bool PlayerRadar = false;
	bool KillerRadar = false;
	bool GeneratorRadar = false;

	float speedhack = 1.0f;

	int KillerPickerInt = 0;
	bool KillerPicking = false;
	*/
