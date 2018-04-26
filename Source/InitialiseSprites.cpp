#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"


bool AngryBirdsGame::loadBackgrounds()
{
	std::string background_layer = "Resources\\images\\foreground.png";
	std::string midground_layer = "Resources\\images\\midground.png";
	std::string foreground_layer = "Resources\\images\\foreground.png";
	std::string sky_layer = "Resources\\images\\sky.png";
	std::string overlay_layer = "Resources\\images\\overlay.png";

	//background
	if (!background.addSpriteComponent(renderer.get(), background_layer))
	{
		return false;
	}
	//midground
	if (!midground.addSpriteComponent(renderer.get(), midground_layer))
	{
		return false;
	}
	//sky
	if (!sky.addSpriteComponent(renderer.get(), sky_layer))
	{
		return false;
	}
	//overlay
	if (!overlay.addSpriteComponent(renderer.get(), overlay_layer))
	{
		return false;
	}

	std::string catapult_layer = "Resources\\images\\catapult.png";

}