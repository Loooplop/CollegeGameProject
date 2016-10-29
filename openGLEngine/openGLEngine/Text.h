#pragma once
#include <vector>
#include <map>
#include "Font.h"
class Text
{
public:
	Text();
	Text(std::string initialString, Font *font, vec2f initialTextPosition,vec3f initialtextColor =vec3f(0,0,0));
	~Text();
	

	void add(std::string string);
	void add(int number);
	void add(float number);
	void add(double number);
	void add(vec3f number);
	void clear();

	Font *getFont()
	{
		return textFont;
	};
	std::vector<int> &getTextGlyphCodes()
	{
		return textGlyphCodes;
	};
	vec2f getTextLocation()
	{
		return textPosition;
	}
	vec3f getTextColor()
	{
		return textColor;
	}
private:
	Font *textFont;
	std::vector<int> textGlyphCodes;
	vec2f textPosition;
	vec3f textColor;
};

