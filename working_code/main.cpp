#include "main.h"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

const int MAX_COUNT = 127;

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

        //imaginary part of "current" pixel
        c_imaginary = im_max - (y * im_scale);

        for(int x = 0; x < width; x++){

            //real part of "current" pixel
            c_real = re_min + (x*re_scale);

            //z_real
            z_real = c_real;

            //z_imaginary
            z_imaginary = c_imaginary;

            //count
            int count = 0;

            //Calculate whether the complex number is a part of the mandelbrot set and colour it if it is.
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

/*Sets a "pixel" of a specified size. Use to speed 
    up the rendering process*/
void setPoint(int x, int y, int size){
    for(int i = 0; i < size; i++ ){
        for(int j = 0; j < size; j++){
            graphics.set_pixel(Point(x+i,y+j));
        }
    }
}