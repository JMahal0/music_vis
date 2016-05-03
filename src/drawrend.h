#ifndef CGL_DRAWREND_H
#define CGL_DRAWREND_H

#include "CGL/CGL.h"
#include "CGL/renderer.h"
#include "CGL/color.h"
#include <vector>
#include "GLFW/glfw3.h"

namespace CGL {

class DrawRend {
 public:
  DrawRend(Aquila::WaveFile wav_): {}
  
  ~DrawRend( void );

  // inherited Renderer interface functions
  void resize( size_t w, size_t h );
  void keyboard_event( int key, int event, unsigned char mods );

  // write current pixel buffer to disk
  void write_screenshot();

  // drawing functions
  void redraw();
  void resolve();

  // rasterize a point
  void rasterize_point( float x, float y, Color color );

  // rasterize a point for a triangle
  void rasterize_tri_point( float x, float y, int xr, int yr, Color color );

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
  void rasterize_circle( float cx, float cy, float r, Color color, Circle *cir = NULL)

private:
  Matrix3x3 ndc_to_screen;

  std::vector<unsigned char> framebuffer;
  size_t width, height;

  int sample_rate;

  std::vector<unsigned char> superbuffer;
  

};

} // namespace CGL

#endif // CGL_DRAWREND_H