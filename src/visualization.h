/**
 * @author Jaskirat Mahal
 * Converts the data from the sound file to VShapes that 
 * the renderer will show.
 */
#ifndef CGL_VISUALIZATION_H
#define CGL_VISUALIZATION_H
#include <vector>
// #include "texture.h"
#include "aquila/source/WaveFile.h"
#include "CGL/color.h"

// #include "drawrend.h"

#include "transforms.h"
#include "CGL/vector2D.h"
#include "CGL/matrix3x3.h"


namespace CGL {

class DrawRend;

class VShape {
 public:
  VShape(double _duration);
  ~VShape() {}

  // Draws the VShape to the framebuffer
  virtual void draw(DrawRend *dr, Color color, Matrix3x3 global_transform) = 0;

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
};

class Triangle : VShape {
 public:
  Triangle(double _duration, Vector2D p0, Vector2D p1, Vector2D p2) : VShape(_duration) {
    a = p0;
    b = p1;
    c = p2;
  }
  
  void draw(DrawRend *dr, Color color, Matrix3x3 global_transform);
  virtual Color color(float alpha, float beta, Color c) = 0;

 private:
  Vector2D a, b, c; // The 3 points of the triangle
};

class GradiantTri : Triangle {
 public:
  GradiantTri(double _duration, Vector2D p0, Vector2D p1, Vector2D p2, Color p0c, Color p1c, Color p2c): Triangle(_duration, p0, p1, p2) {
    ac = p0c;
    bc = p1c;
    cc = p2c;
  }
  
  Color color(float alpha, float beta, Color c);

 private:
  Color ac, bc, cc;
};



class Line : VShape {
 public:
  Line(double _duration, Vector2D _p0, Vector2D _p1): VShape(_duration) {
    p0 = _p0;
    p1 = _p1;
  }

  void draw(DrawRend *dr, Color color, Matrix3x3 global_transform);

 private:
  Vector2D p0, p1;
};

class Rectangle : VShape {
 public:
  Rectangle(double _duration, Vector2D _p, double _w, double _h): VShape(_duration) {
    p = _p;
    w = _w;
    h = _h;
  }
  
  void draw(DrawRend *dr, Color color, Matrix3x3 global_transform);

 private:
  Vector2D p; // The bottom left corner of the Rectangle
  double w, h;
};

class Circle : VShape {
 public:
  Circle(double _duration, Vector2D _o, double _r): VShape(_duration) {
    o = _o;
    r = _r;
  }

  void draw(DrawRend *dr, Color color, Matrix3x3 global_transform);

  virtual Color color(float distance, Color c);

  Vector2D o; // origin
  double r; // radius
};

class GradiantCir : Circle {
 public:
  GradiantCir(double _duration, Vector2D _o, double _r, Color near, Color far): Circle(_duration, _o, _r) {
    near_c = near;
    far_c = far;
  }

  Color color(float distance, Color c);

  Color near_c, far_c;
};




class Visualization {
 public:
 	Visualization(Color main_low, Color main_high, Color second_low, Color second_high, Color accent_low, Color accent_high); // all the 6 colors
 	~Visualization();

 	void visualizeMono(Aquila::SpectrumType *m_data, double index, std::vector<VShape> *vshape_lst);

 	void visualizeStereo(Aquila::SpectrumType *m_data_left, Aquila::SpectrumType *m_data_right, double index, std::vector<VShape> *vshape_lst);



 private:
 	// Holds all the shapes that are visible on screen
 	std::vector<VShape> vshapes;

 	// The color scheme of the visualization
	Color color_main_low, color_main_high, color_secondary_low, color_secondary_high, color_accent_low, color_accent_high;

};




}

#endif // CGL_VISUALIZATION_H