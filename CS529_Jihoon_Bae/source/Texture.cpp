/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Texture.cpp>
Purpose: <Texture function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_3>
Author: <jihoon.bae>
Creation date: <09/29/2023>
--------------------------------------------------------*/
#include "pch.h"

Texture::Texture(const char* filename) {
    loadPNGFile(filename);
}

void Texture::getImage(glm::vec3*& dest) { dest = m_image; }

void Texture::loadPNGFile(const char* filename) {
    std::vector<unsigned char> pngData; // Store the loaded PNG data

    // load the PNG file
    unsigned int error = lodepng::load_file(pngData, filename);

    if (error) {
        std::cerr << "Error loading PNG file: " << lodepng_error_text(error) << std::endl;
        return;
    }

    // decode the PNG data
    std::vector<unsigned char> image;
    unsigned int width, height;

    error = lodepng::decode(image, width, height, pngData);

    if (error) {
        std::cerr << "Error decoding PNG data: " << lodepng_error_text(error) << std::endl;
        return;
    }

    // check that the image has 3 or 4 channels (RGB or RGBA)
    if (image.size() % 3 != 0 && image.size() % 4 != 0) {
        std::cerr << "Unsupported PNG image format: " << filename << std::endl;
        return;
    }

    // determine the number of channels (3 for RGB, 4 for RGBA)
    int channels = (image.size() % 4 == 0) ? 4 : 3;

    m_width = width;
    m_height = height;
    m_bytesPerPix = channels;
    m_bitDepth = 8; // Assuming 8-bit per channel

    m_size = m_width * m_height;
    m_image = new glm::vec3[m_size];
    texcoord = new glm::vec2[m_size];

    // convert the image data to glm::vec3 format
    for (size_t i = 0; i < m_size; ++i) {
        glm::vec3 vertex;
        vertex.x = static_cast<float>(image[i * channels]) / 255.0f;
        vertex.y = static_cast<float>(image[i * channels + 1]) /  255.0f;
        vertex.z = static_cast<float>(image[i * channels + 2]) /  255.0f;
        m_image[i] = vertex;
    }
}