#include "GrayLevelImage2D.hpp"
#include <exception>
#include <fstream> // flux sur les fichiers
#include <iostream>
#include <sstream> // flux sur les chaînes de caractères
#include <string>  // chaînes de caractères
#include <vector>

GrayLevelImage2D::GrayLevelImage2D() : m_width(0), m_height(0), m_data() {}

GrayLevelImage2D::GrayLevelImage2D(int w, int h, GrayLevel g)
    : m_width(w), m_height(h), m_data(Container(h * w, g)) {}

void GrayLevelImage2D::fill(GrayLevel g)
{
    for (int i = 0; i < (int)m_data.size(); i++)
        m_data[i] = g;
}

int GrayLevelImage2D::w() const { return m_width; }

int GrayLevelImage2D::h() const { return m_height; }

/**
   Accesseur read-only à la valeur d'un pixel.
   @return la valeur du pixel(i,j)
*/
GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(int i, int j) const
{
    return m_data[index(i, j)];
}

/**
   Accesseur read-write à la valeur d'un pixel.
   @return une référence à la valeur du pixel(i,j)
*/
GrayLevelImage2D::GrayLevel &GrayLevelImage2D::at(int i, int j)
{
    return m_data[index(i, j)];
}
//! [gli2d-sec3]

GrayLevelImage2D::Iterator::Iterator(GrayLevelImage2D &Image, int x, int y)
    : GrayLevelImage2D::Container::iterator(Image.m_data.begin() +
                                            Image.index(x, y)) {}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin() { return start(0, 0); }

GrayLevelImage2D::Iterator GrayLevelImage2D::end()
{
    return start(0, m_height);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y)
{
    return Iterator(*this, x, y);
}

// std::pair<int,int> GrayLevelImage2D::position( Iterator it ) const{}

bool GrayLevelImage2D::importPGM(std::istream &input)
{
    if (!input.good())
        return false;

    // P2
    std::string str;
    bool isAscii;
    std::getline(input, str);
    isAscii = str == "P2";

    // Commentaire
    std::getline(input, str);
    while ((str != "") && (str[0] == '#'))
    {
        std::getline(input, str);
    }

    // Taille
    std::istringstream sizeImage(str);
    int width, height;
    sizeImage >> width >> height;
    m_width = width;
    m_height = height;
    m_data.resize(m_height * m_width);

    // Couleur max
    std::getline(input, str);

    if (isAscii)
    {
        for (Iterator it = begin(), itE = end(); it != itE; ++it)
        {
            int g;
            input >> g;
            *it = g;
        }
    }
    else
    {
        input >> std::noskipws;
        for (Iterator it = begin(), itE = end(); it != itE; ++it)
        {
            unsigned char g;
            input >> g;
            *it = g;
        }
    }
    return true;
}

bool GrayLevelImage2D::exportPGM(std::ostream &output, bool ascii)
{
    if (!output.good())
        return false;
    output << (ascii ? "P2" : "P5") << std::endl;
    output << "#Commentaire made by me" << std::endl;
    output << m_width << " " << m_height << std::endl;
    output << 255 << std::endl;

    if (ascii)
    {
        for (Iterator it = begin(), itE = end(); it != itE; ++it)
            output << (int)*it << " ";
    }
    else
    {
        for (Iterator it = begin(), itE = end(); it != itE; ++it)
            output << *it;
    }

    return true;
}

int GrayLevelImage2D::index(int x, int y) const { return x + y * m_width; }
