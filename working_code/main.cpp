#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "main.h"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

const int MAX_COUNT = 127;

int main() {

    fractal();
    st7789.update(&graphics);
}

void fractal(){
    int size = 1;
    double c_real, c_imaginary,z_real,z_imaginary;
    int count;

    //Size of screen
    int width = 240 / size;
    int height = 135 / size;

    //Starting and ending complex numbers
    double re_min = -2.0;
    double re_max = 0.47;
    double im_min = -1.12;
    double im_max = 1.12;
    //double im_max = re_min+(re_max-re_min)*(height/width);

    //Scaling
    double re_scale = (re_max-re_min) / width;
    double im_scale = (im_max-im_min) / height;


    //Need to loop through all pixels on screen.
    //Each pixel will represent a complex number (x + yi)
    for(int y = 0; y < height ; y++){
        //c_imaginary
        c_imaginary = im_max - (y * im_scale);

        for(int x = 0; x < width; x++){
            //Calculate whether the complex number is a part of the mandelbrot set and colour it if it is.

            //real part of number:
            c_real = re_min + (x*re_scale);

            //z_real
            z_real = c_real;

            //z_imaginary
            z_imaginary = c_imaginary;

            //count
            count = 0;
            while(count < MAX_COUNT){

                double z_real2 = z_real * z_real;
                double z_imaginary2 = z_imaginary * z_imaginary;

                if((z_real2 + z_imaginary2) > 4){
                    break;
                }
                
                z_imaginary = 2*z_real*z_imaginary + c_imaginary;
                z_real = z_real2 - z_imaginary2 + c_real;
                count += 1;
            }

            graphics.set_pen(255-(count*2),255-(count*2),255-(count*2));

            setPoint(x*size,y*size,size);
            st7789.update(&graphics);
        }
    }

}

void setPoint(int x, int y, int size){
    for(int i = 0; i < size; i++ ){
        for(int j = 0; j < size; j++){
            graphics.set_pixel(Point(x+i,y+j));
        }
    }
}