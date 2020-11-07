#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_

#include <iostream>
#include <string>
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include <exception>
#include <vector>

#include "Color.hpp"
#include "Image2D.hpp"

template <typename TValue>
class Image2DReader
{
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool read(Image &img, std::istream &input)
    {
        std::cerr << "[Image2DReader<TValue>::read] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char>
{
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;
    static bool read(Image &img, std::istream &input)
    {
        if (!input.good())
            return false;

        std::string str;
        bool isAscii;
        std::getline(input, str);
        isAscii = str == "P1";

        std::getline(input, str);
        while ((str != "") && (str[0] == '#'))
        {
            std::getline(input, str);
        }

        // Taille
        std::istringstream sizeImage(str);
        int width, height;
        sizeImage >> width >> height;
        img = Image(width, height);
        // Couleur max
        std::getline(input, str);
        if (isAscii)
        {
            input >> std::skipws;
            for (auto it = img.begin(), itE = img.end(); it != itE; ++it)
            {

                unsigned char g;
                input >> g;
                *it = (int)g;
            }
        }
        else
        {
            input >> std::noskipws;
            for (auto it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                unsigned char g;
                input >> g;
                *it = g;
            }
        }
        return true;
    }
};

/// Specialization for color images.
template <>
class Image2DReader<Color>
{
public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static bool read(Image &img, std::istream &input)
    {
        if (!input.good())
            return false;

        std::string str;
        bool isAscii;
        std::getline(input, str);
        isAscii = str == "P3";

        std::getline(input, str);
        while ((str != "") && (str[0] == '#'))
        {
            std::getline(input, str);
        }

        // Taille
        std::istringstream sizeImage(str);
        int width, height;
        sizeImage >> width >> height;
        img = Image(width, height);
        // Couleur max
        std::getline(input, str);
        if (isAscii)
        {
            input >> std::skipws;
            for (auto it = img.begin(), itE = img.end(); it != itE; ++it)
            {

                Color::Byte r, g, b;
                input >> r >> g >> b;
                Color c = Color(r, g, b);
                *it = c;
            }
        }
        else
        {
            input >> std::noskipws;
            for (auto it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                unsigned char r, g, b;
                input >> r >> g >> b;
                *it = Color((int)r, (int)g, (int)b);
            }
        }
        return true;
    }
};

#endif // _IMAGE2DREADER_HPP_
