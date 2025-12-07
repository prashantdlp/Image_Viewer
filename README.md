# Image Viewer (SDL2)

A lightweight **image viewer** written in **C++ + SDL2**.  
Currently supports **PPM image loading**, window resizing, and smooth rendering.  
Built as a learning project for graphics, file parsing, and SDL-based rendering.

---

## Features

- Fast **PPM (P3 and P6) loader**
- **Window scaling** — resize window & image scales accordingly
- **Zoom in / Zoom out** (planned)
- **Pan / Move image** (planned)
- Full **Data Security** which is not available in **Online viewers**
- Simple and easy-to-understand codebase
- Clean modular structure:  
  - `Image.h / Image.cpp`  
  - `ppm.cpp` (PPM parser)  
  - `utils.h`  
  - `main.cpp`

---

## Build & Run

### **Prerequisites**
Make sure you have:
- **g++ / clang++**
- **SDL2 development libraries**

### **On Linux / WSL**
Install SDL2:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev
```

## How to Use  
Clone the repository and navigate to the project directory and run :

``` .\program(executable)  <path-to-image.ppm> ```