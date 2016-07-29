#pragma once
#include "Texture.h"
#include "WE_Vector.h"
#include <fstream>
#include <map>
class Font
{
public:
	Font();
	Font(const char *filename);
	~Font();

	Texture  *getTexture()
	{
		return fontAtlas;
	};
	vec2f getGlyphSize()
	{
		return glyphSize;
	};
	int getTextureSize()
	{
		return textureSize;
	};
	int getGlyphCode(char character);
	bool characterExists(char character);
	int getGlyphsPerRow()
	{
		return glyphsPerRow;
	}
private:

	Texture *fontAtlas;
	int glyphsPerRow;
	vec2f glyphSize;
	int textureSize;
	std::map<char, int> glyphCode;
	std::map<char,vec2f> glyphInfo;
};

