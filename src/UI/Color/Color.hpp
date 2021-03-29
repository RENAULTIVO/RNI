#ifndef COLOR_HPP
#define COLOR_HPP

class Color {

  public:
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
    unsigned short int alpha;

    Color(
      unsigned short int red = 0,
      unsigned short int green = 0,
      unsigned short int blue = 0,
      unsigned short int alpha = 255) {
      this->red = red;
      this->green = green;
      this->blue = blue;
      this->alpha = alpha;
    }

};

#endif