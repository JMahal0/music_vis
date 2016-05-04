#ifndef CGL_DRAWREND_H
#define CGL_DRAWREND_H

#include "CGL/CGL.h"
#include "CGL/renderer.h"
#include "CGL/color.h"
#include <vector>
#include "GLFW/glfw3.h"
// #include "CGL/matrix3x3.h"
// #include "CGL/vector2D.h"


#include "visualization.h"

namespace CGL {



class DrawRend {
 public:
  DrawRend(size_t w, size_t h);
  
  ~DrawRend( void );

  // write current pixel buffer to disk
  void write_frame_shot(int frame_number, std::vector<VShape*> *shapes);

  
  // rasterize a line
  void rasterize_line( float x0, float y0,
                       float x1, float y1,
                       Color color);

  // rasterize a triangle
  void rasterize_triangle( float x0, float y0,
                           float x1, float y1,
                           float x2, float y2,
                           Color color, Triangle *tri = NULL );

  // rasterize a circle
  void rasterize_circle( float cx, float cy, float r, Color color, Circle *cir = NULL);

private:
  Matrix3x3 ndc_to_screen;

  std::vector<unsigned char> framebuffer;
  size_t width, height;

  int sample_rate;
  std::vector<unsigned char> superbuffer;

  // drawing functions
  void draw_frame(std::vector<VShape*> *shapes);
  void downsample();

  // rasterize a point
  void rasterize_line_point( float x, float y, Color color );

  // rasterize a point for a shape
  void rasterize_shape_point( float x, float y, int xr, int yr, Color color );

  

};




} // namespace CGL

#endif // CGL_DRAWREND_H