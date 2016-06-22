#include "Text.h"
#include <string>


Text::Text()
{
}

Text::Text(std::string initialString, Font * font, vec2f initialTextPosition)
{
	textFont = font;
	add(initialString);
	textPosition = initialTextPosition;
}


Text::~Text()
{
	textGlyphCodes.clear();
}

void Text::add(std::string string)
{
	for (int i = 0; i < string.size(); i++)
	{
		if (!textFont->characterExists(string[i]))
		{
			textGlyphCodes.push_back(0);
		}
		else
		{
			textGlyphCodes.push_back(textFont->getGlyphCode(string[i]));
		}
	}
}

void Text::add(int number)
{
	add(std::to_string(number));
}

void Text::add(float number)
{
	add(std::to_string(number));
}

void Text::add(double number)
{
	add(std::to_string(number));
}

void Text::clear()
{
	textGlyphCodes.clear();
}
