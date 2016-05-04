/**
 * @author Jaskirat Mahal
 * Converts the data from the sound file to VShapes that 
 * the renderer will show.
 */
#ifndef CGL_VISUALIZATION_H
#define CGL_VISUALIZATION_H
#include <vector>
// #include "texture.h"
// #include "aquila/source/WaveFile.h"
#include "aquila/global.h"
#include "CGL/color.h"

// #include "drawrend.h"

#include "transforms.h"
#include "CGL/vector2D.h"
#include "CGL/matrix3x3.h"


namespace CGL {

class DrawRend;

class VShape {
 public:
  VShape(double _duration, Color f_c);
  ~VShape() {}

  // Draws the VShape to the framebuffer
  virtual void draw(DrawRend *dr, Matrix3x3 global_transform) = 0;

  // Makes the VShape's color closer and closer to the
  // background color.
  // Returns whether or not the VShape has completely
  // faded (when time_elapsed >= duration).
  bool fade(double time_elapsed);

  // Amount of frames/sec? until the shape completely 
  // fades into the background
  double duration;

  // The alpha value in RGBA. In range [0,1]
  // Decreases with time in fade function.
  float transparency_a;

  // The color of the Shape, not used in GradiantTri or GradiantCir
  Color fill_color;
};

class Triangle : public VShape {
 public:
  Triangle(double _duration, Color f_c, Vector2D p0, Vector2D p1, Vector2D p2) : VShape(_duration, f_c) {
    a = p0;
    b = p1;
    c = p2;
  }
  
  void draw(DrawRend *dr, Matrix3x3 global_transform);
  virtual Color color(float alpha, float beta);

 private:
  Vector2D a, b, c; // The 3 points of the triangle
};

class GradiantTri : public Triangle {
 public:
  GradiantTri(double _duration, Color f_c, Vector2D p0, Vector2D p1, Vector2D p2, Color p0c, Color p1c, Color p2c): Triangle(_duration, f_c, p0, p1, p2) {
    ac = p0c;
    bc = p1c;
    cc = p2c;
  }
  
  Color color(float alpha, float beta);

 private:
  Color ac, bc, cc;
};



class Line : public VShape {
 public:
  Line(double _duration, Color f_c, Vector2D _p0, Vector2D _p1): VShape(_duration, f_c) {
    p0 = _p0;
    p1 = _p1;
  }

  void draw(DrawRend *dr, Matrix3x3 global_transform);

 private:
  Vector2D p0, p1;
};

class Rectangle : public VShape {
 public:
  Rectangle(double _duration, Color f_c, Vector2D _p, double _w, double _h): VShape(_duration, f_c) {
    p = _p;
    w = _w;
    h = _h;
  }
  
  void draw(DrawRend *dr, Matrix3x3 global_transform);

 private:
  Vector2D p; // The bottom left corner of the Rectangle
  double w, h;
};

class Circle : public VShape {
 public:
  Circle(double _duration, Color f_c, Vector2D _o, double _r): VShape(_duration, f_c) {
    o = _o;
    r = _r;
  }

  void draw(DrawRend *dr, Matrix3x3 global_transform);

  virtual Color color(float distance);

  Vector2D o; // origin
  double r; // radius
};

class GradiantCir : public Circle {
 public:
  GradiantCir(double _duration, Color f_c, Vector2D _o, double _r, Color near, Color far): Circle(_duration, f_c, _o, _r) {
    near_c = near;
    far_c = far;
  }

  Color color(float distance);

  Color near_c, far_c;
};




class Visualization {
 public:
 	Visualization(Color main_low, Color main_high, Color second_low, Color second_high, Color accent_low, Color accent_high); // all the 6 colors
 	~Visualization() {};

 	void visualizeMono(Aquila::ComplexType m_data, int index, int length);

 	void visualizeStereo(Aquila::ComplexType m_data_left, Aquila::ComplexType m_data_right, int index, int length, double str_left, double str_right);

	// Holds all the shapes that are visible on screen
 	std::vector<VShape*> vshapes;


 private:
 	// The color scheme of the visualization
	Color color_main_low, color_main_high, color_secondary_low, color_secondary_high, color_accent_low, color_accent_high;

};




}

#endif // CGL_VISUALIZATION_H