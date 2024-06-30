/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Utils.h>
Purpose: <utility functions>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_5>
Author: <jihoon.bae>
Creation date: <11/10/2023>
--------------------------------------------------------*/
#pragma once

class Utils
{
public:
    // @brief extracts the class name from datatype
    // @return string class name
    template<typename DataType>
    static std::string GetClassName() 
    {
        std::string typeName = typeid(DataType).name();
        std::string prefix = "class ";
        size_t prefixPosition = typeName.find(prefix);
        if (prefixPosition == 0) {
            return typeName.substr(prefix.length());
        }
        return typeName;
    }

private:
    Utils() {};
};

