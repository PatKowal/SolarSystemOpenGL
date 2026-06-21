#define _CRT_SECURE_NO_WARNINGS

#include "TexturedObject.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

TexturedObject::TexturedObject() : textureID(0) {}

TexturedObject::~TexturedObject() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

GLuint TexturedObject::getTextureID()
{
    return textureID;
}

unsigned int TexturedObject::getInt(FILE* fp) {
    int c, c1, c2, c3;
    c = getc(fp);  c1 = getc(fp);  c2 = getc(fp);  c3 = getc(fp);
    return ((unsigned int)c) + (((unsigned int)c1) << 8) + (((unsigned int)c2) << 16) + (((unsigned int)c3) << 24);
}

unsigned short TexturedObject::getShort(FILE* fp) {
    int c, c1;
    c = getc(fp);  c1 = getc(fp);
    return ((unsigned short)c) + (((unsigned short)c1) << 8);
}

bool TexturedObject::loadTexture(const std::string& filename) {
    FILE* file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;
    char temp;

    if ((file = fopen(filename.c_str(), "rb")) == NULL) {
        std::cout << "File Not Found : " << filename << std::endl;
        return false;
    }

    fseek(file, 18, SEEK_CUR);

    Image image;
    image.sizeX = getInt(file);
    image.sizeY = getInt(file);

    size = image.sizeX * image.sizeY * 3;

    planes = getShort(file);
    if (planes != 1) {
        std::cout << "Planes from " << filename << " is not 1: " << planes << std::endl;
        fclose(file);
        return false;
    }

    bpp = getShort(file);
    if (bpp != 24) {
        std::cout << "Bpp from " << filename << " is not 24: " << bpp << std::endl;
        fclose(file);
        return false;
    }

    fseek(file, 24, SEEK_CUR);

    image.data = (char*)malloc(size);
    if (image.data == NULL) {
        std::cout << "Error allocating memory" << std::endl;
        fclose(file);
        return false;
    }

    if ((fread(image.data, size, 1, file)) != 1) {
        std::cout << "Error reading image data" << std::endl;
        free(image.data);
        fclose(file);
        return false;
    }

    for (i = 0; i < size; i += 3) {
        temp = image.data[i];
        image.data[i] = image.data[i + 2];
        image.data[i + 2] = temp;
    }

    fclose(file);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.sizeX, image.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);

    free(image.data);
    return true;
}