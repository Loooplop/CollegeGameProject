#pragma once
#include <vector>
#include <map>
#include "Font.h"
class Text
{
public:
	Text();
	Text(std::string initialString, Font *font, vec2f initialTextPosition);
	~Text();
	

	void add(std::string string);
	void add(int number);
	void add(float number);
	void add(double number);
	void clear();

	Font *getFont()
	{
		return textFont;
	};

private:
	Font *textFont;
	std::vector<int> textGlyphCodes;
	vec2f textPosition;
	
};

