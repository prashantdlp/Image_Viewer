#include "ppm.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>

void skipComments(std::ifstream& file){
    char ch;
    while (file >> ch) {
        if (ch == '#') {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            file.unget();
            return;
        }
    }   
}

Image loadPPM(const std::string& filename){
    
    std::ifstream file(filename, std::ios::binary);
    if (!file){
        throw std::runtime_error("Cannot open PPM file");
    }
    
    std::string label;
    file >> label;
    
    if (label != "P3" && label != "P6"){
        throw std::runtime_error("Unsupported PPM format");
    }
    
    skipComments(file);
    int width, height, maxval;
    file >> width >> height;
    skipComments(file);
    file >> maxval;

    if (maxval < 0 || maxval > 255) {
        throw std::runtime_error("Invalid maxval in PPM");
    }

    file.get(); // consume the newline after maxval

    std::vector<uint8_t> pixels(width*height*3); 
    
    if (label == "P6") // P6 Binary
    { 
        file.read((char*)pixels.data(), width * height * 3);
    } 
    else // P3 ASCII
    { 
        for (int i = 0; i < width * height * 3; i++) {
            int v;
            file >> v;
            pixels[i] = (uint8_t)v;
        }
    }

    Image img;
    img.set_width(width);
    img.set_height(height);
    img.set_pixels(pixels);

    return img;
}