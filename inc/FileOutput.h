// David Sami 2015

#ifndef FILE_OUTPUT_H
#define FILE_OUTPUT_H

#include "PixelBuffer.h"
#include <string>

class FileOutput {
public:
    FileOutput()=default;
    void OutputPPM(const PixelBuffer& aBuffer, const std::string& aFilename);
};

#endif
