/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Texture.h>
Purpose: <Texture class definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/29/2023>
--------------------------------------------------------*/
#pragma once
class Texture
{
public:
    glm::vec2* texcoord;

    Texture(const char* filename);
    //-------------------
    // image loading function
  
    // @brief assign the image buffer to destination
    // @param dest: destination to store the image buffer
    void getImage(glm::vec3*& dest);

    // @brief reads the png file and extracts data
    // @param filename: path and file name of the png file
    void loadPNGFile(const char* filename);
    //-------------------

    //-------------------
    //getter functions

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }
    //-------------------

private:
    glm::vec3* m_image;
    int m_size;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_bytesPerPix;
    unsigned int m_bitDepth;
};
