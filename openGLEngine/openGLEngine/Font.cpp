#include "Font.h"
#include <string>


Font::Font()
{
}

Font::Font(const char * filename)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;

		std::getline(file, line);
		fontAtlas = new Texture(line.c_str(), GL_TEXTURE_2D);

		std::getline(file, line);
		glyphsPerRow = std::stoi(line);

		std::getline(file, line);
		glyphSize = vec2f(std::stof(line.substr(0, line.find_first_of(","))), std::stof(line.substr(line.find_first_of(",") + 1)));

		std::getline(file, line);
		textureSize = std::stoi(line);

		glyphCode = std::map<char, int>();
		for (int i = 33; i <= 126; i++)
		{
			glyphCode[i] = i - 32;
		}
		/*
		
		
		*/
	}
	file.close();
}


Font::~Font()
{
	delete fontAtlas;
	glyphCode.clear();
	std::cout << "Destroyed Font" << std::endl;
}

int Font::getGlyphCode(char character)
{
	return glyphCode[character];
}

bool Font::characterExists(char character)
{
	return glyphCode.find(character) != glyphCode.end();
}