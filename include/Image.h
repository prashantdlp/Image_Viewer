#ifndef IMAGE 
#define IMAGE

#include<vector>
#include<cstdint>

class Image{
private:  
    int width;
    int height;
    std::vector<uint8_t> pixels; // size = width * height * 3 (RGB)
public:
    int get_width();
    int get_height();
    std::vector<uint8_t> get_pixels(); 
    void set_width(int width);
    void set_height(int height);
    void set_pixels(std::vector<uint8_t> pixels); 
};
#endif