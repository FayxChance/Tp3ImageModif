#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWritter.hpp"
#include "Image2DReader.hpp"
int main()
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img(256, 256, Color(0, 0, 0));
    Iterator it = img.begin();
    for (int y = 0; y < 256; ++y)
        for (int x = 0; x < 256; ++x)
        {
            *it++ = Color(y, x, (2 * x + 2 * y) % 256);
        }
    std::ofstream output("colors.ppm"); // ios::binary for Windows system
    Image2DWriter<Color>::write(img, output, false);
    output.close();
    std::ifstream input("colors.ppm"); // ios::binary for Windows system
    Image2DReader<Color>::read(img, input);
    input.close();
    std::ofstream output2("colorsRes.ppm");
    Image2DWriter<Color>::write(img, output2, true);
    output2.close();
    return 0;
}
