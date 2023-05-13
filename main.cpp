#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "main.h"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

const int MAX_COUNT = 30;

int main() {

    fractal();
    st7789.update(&graphics);
}

void fractal(){
    float c_real, c_imaginary,z_real,z_imaginary,tempx;
    int count;

    //Size of screen
    int xmax = __INT_WIDTH__;
    int ymax = __INT_WIDTH__;

    float left = -1.75;
    float top = -0.25;
    float xside = 0.25;
    float yside = 0.45;

    //Scaling
    float xscale = xside / xmax;
    float yscale = yside / ymax;

    //Need to loop through all pixels on screen.
    //Each pixel will represent a complex number (x + yi)
    for(int x = 0; x < xmax -1; x++){
        for(int y = 0; y < ymax -1; y++){
            //Calculate whether the complex number is a part of the mandelbrot set and colour it if it is.

            //c_real
            c_real = x * xscale + left;

            //c_imaginary
            c_imaginary = y * yscale + top;

            //z_real
            z_real = 0;

            //z_imaginary
            z_imaginary = 0;

            //count
            count = 0;

            while(count < MAX_COUNT && (z_real * z_real + z_imaginary * z_imaginary < 4)){
                tempx = z_real*z_real - z_imaginary * z_imaginary + c_real;

                z_imaginary = 2 * z_real * z_imaginary * c_real;

                z_real = tempx;

                count += 1;
            }




            //If count > 1 then display
            if(count > 2){
                graphics.set_pen(255,255,255);
            }else{
                graphics.set_pen(0,0,0);
            }
            graphics.set_pixel(Point(x,y));
        }
    }
}