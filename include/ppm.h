#ifndef PPM_H
#define PPM_H

#include <string>
#include "Image.h"

void skipComments(std::ifstream& file); // HELPER FUNCTION TO SKIP COMMENTS IN PPM FILE

Image loadPPM(const std::string& filename);

#endif