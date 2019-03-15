#include "pch.h"
#include "Assets.h"

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets()
{
	sprites["ammocrate"] = SpriteInfo("Content/Textures/ammocrate.png");
	sprites["player"] = SpriteInfo("Content/Textures/player.jpg");
}
