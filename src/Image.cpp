#include "Image.h"

int Image::get_width(){
    return this->width ;
}

int Image::get_height(){
    return this->height ;
}

std::vector<uint8_t> Image::get_pixels(){
    return this->pixels ;
}

void Image::set_width(int width){
    this->width = width ;
};

void Image::set_height(int height){
    this->height = height ;
};
    
void Image::set_pixels(std::vector<uint8_t> pixels){
    this->pixels = pixels ;
};