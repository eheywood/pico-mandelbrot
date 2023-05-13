#include "main.h"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

//Set max number of iterations
const int MAX_COUNT;

int main() {
    fractal();
}

/* Does the calculating for the mandelbrot set*/
void fractal(){

    /* Use a size of 3 for testing otherwise you will be 
        waiting for  a very long time*/
    int size = 3;

    //The current number made from the real part and the imaginary part
    double c_real, c_imaginary;

    //The newly calculated number made from the real part and imaginary part
    double z_real,z_imaginary;

    //Size of screen
    int width = 240 / size;
    int height = 135 / size;

    //Starting and ending complex numbers
    //real:
    double re_min = -2.0;
    double re_max = 0.47;
    //imaginary
    double im_min = -1.12;
    double im_max = 1.12;

    //Scaling
    double re_scale = (re_max-re_min) / width;
    double im_scale = (im_max-im_min) / height;

    //Need to loop through all pixels on screen.
    //Each pixel will represent a complex number (x + yi)
    for(int y = 0; y < height ; y++){

        //set imaginary part of "current" pixel
        c_imaginary = im_max - (y * im_scale);

        for(int x = 0; x < width; x++){

            //set real part of "current" pixel:
    

            //set z_real initial val:
            

            //set z_imaginary initial val:


            //create counter

            /*Calculate whether the complex number is a part of the mandelbrot set by 
               iterating to the max number of iterations*/
            //If it is a part of the set then colour the pixel
        }
    }

}

/*Sets a "pixel" of a specified size. Use to speed 
    up the rendering process*/
void setPoint(int x, int y, int size){
    for(int i = 0; i < size; i++ ){
        for(int j = 0; j < size; j++){
            graphics.set_pixel(Point(x+i,y+j));
        }
    }
}