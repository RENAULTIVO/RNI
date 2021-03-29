#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

class Vector2D {

  public:
    float x;
    float y;

    Vector2D(float x=0, float y=0) {
      this->x = x;
      this->y = y;
    }

    inline Vector2D operator+(const Vector2D &v2) const {
      return Vector2D(x + v2.x, y + v2.y);
    }

    inline Vector2D operator-(const Vector2D &v2) const {
      return Vector2D(x - v2.x, y - v2.y);
    }

    inline Vector2D operator*(const float scale) const {
      return Vector2D(x * scale, y * scale);
    }

};

#endif