// David Sami 2015

#include <fstream>
#include "FileOutput.h"

void FileOutput::OutputPPM(const PixelBuffer& aBuffer, const std::string& aFilename){
    std::fstream fout;
    fout.open(aFilename, std::fstream::out | std::fstream::binary | std::fstream::trunc);

    size_t height, width;
    height = aBuffer.GetHeight();
    width = aBuffer.GetWidth();

    fout << "P3\n";
    fout << width << ' ' << height << std::endl;
    fout << "255" << std::endl;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            Colour pixel = aBuffer.GetPixel(x,y);
            fout << (int)pixel.r << ' ' << (int)pixel.g << ' ' << (int)pixel.b << ' ' ;
        }
        fout << std::endl;
    }
    fout.close();
}
