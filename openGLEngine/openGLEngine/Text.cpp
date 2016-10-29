#include "Text.h"
#include <string>


Text::Text()
{
}

Text::Text(std::string initialString, Font * font, vec2f initialTextPosition, vec3f initialtextColor)
{
	textFont = font;
	add(initialString);
	textPosition = initialTextPosition;
	textColor = initialtextColor;
}


Text::~Text()
{
	textGlyphCodes.clear();
}

void Text::add(std::string string)
{
	for (int i = 0; i < string.size(); i++)
	{
		if (textFont->characterExists(string[i]))
		{
			textGlyphCodes.push_back(textFont->getGlyphCode(string[i]));
		}
		else
		{
			textGlyphCodes.push_back(0);
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

void Text::add(vec3f number)
{
	add(number.getX());
	add(", ");
	add(number.getY());
	add(", ");
	add(number.getZ());
}

void Text::clear()
{
	textGlyphCodes.clear();
}
