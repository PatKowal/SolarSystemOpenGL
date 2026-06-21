#pragma once
#include <string>
#include <GL/glut.h>

class TexturedObject
{
private:
	GLuint textureID;

	struct Image
	{
		unsigned long sizeX;
		unsigned long sizeY;
		char* data;
	};

	unsigned int getInt(FILE* fp);
	unsigned short getShort(FILE* fp);

protected:
	bool loadTexture(const std::string& filename);

public:
	TexturedObject();
	virtual ~TexturedObject();

	GLuint getTextureID();

	virtual void draw() = 0;
};

