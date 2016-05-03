#include "drawrend.h"
#include "CGL/misc.h"
#include <iostream>
#include <sstream>
#include "CGL/lodepng.h"
#include <ctime>
#include "math.h"

#include <typeinfo>

// #include "visualization.h"


using namespace std;

namespace CGL {

class Triangle;
class Circle;

DrawRend::DrawRend(size_t w, size_t h) {
  sample_rate = 1;

  // Set up size
  width = w; height = h;

  framebuffer.resize(4 * w * h);
  superbuffer.resize(4 * w * h * sample_rate);
  // memset(&framebuffer[0], 255, 4 * width * height);
  // memset(&superbuffer[0], 255, 4 * width * height * sample_rate);

  float scale = min(width, height);
  ndc_to_screen(0,0) = scale; ndc_to_screen(0,2) = (width  - scale) / 2;
  ndc_to_screen(1,1) = scale; ndc_to_screen(1,2) = (height - scale) / 2;

  
}

DrawRend::~DrawRend( void ) {}




/**
 * Writes the contents of the pixel buffer to disk as a .png file.
 * The image filename contains the month, date, hour, minute, and second
 * to make sure it is unique and identifiable.
 */
void DrawRend::write_frame_shot(double frame_number) {
    draw_frame();


    time_t t = time(nullptr);
    tm *lt = localtime(&t);
    stringstream ss;
    ss << "screenshot_" << lt->tm_mon+1 << "-" << lt->tm_mday << "_" 
      << lt->tm_hour << "-" << lt->tm_min << "-" << lt->tm_sec << ".png";
    string file = ss.str();
    cout << "Writing file " << file << "...";

    if (lodepng::encode(file, framebuffer, width, height))
      cerr << "Could not be written" << endl;
    else 
      cout << "Success!" << endl;
}

/**
 * Draws the current frame to the framebuffer. Resolves the supersample buffers
 * into the framebuffer before posting the framebuffer pixels to the screen.
 */
void DrawRend::draw_frame() {
  memset(&framebuffer[0], 255, 4 * width * height);
  memset(&superbuffer[0], 255, 4 * width * height * sample_rate);

  // SVG &svg = *svgs[current_svg];
  // svg.draw(this, ndc_to_screen*svg_to_ndc[current_svg]);

  // call the draw method of each Shape in the vector of Shapes, which is either public static or passed in from somewhere

  downsample();
}

/**
 * Resolves whatever supersampling buffer you create into the
 * framebuffer pixel vector
 */
void DrawRend::downsample() {
  //Average the values of superbuffer here and then put into framebuffer

  for (int fpix = 0; fpix < width * height; fpix++) { // goes thru all pixels in framebuffer

    // fpix is the number of the pixel in the framebuffer
    int pixNum = 4*sample_rate*fpix;

    float red = 0;
    float green = 0;
    float blue = 0;
    float alpha = 0;
    for (int s = 0; s < sample_rate; s++) { // innermost, goes thru samples in a pixel
      int sampNum = 4*s;

      unsigned char *sb = &superbuffer[0] + pixNum + sampNum;

      red += sb[0];
      green += sb[1];
      blue += sb[2];
      alpha += sb[3];      
    }

    red /= sample_rate;
    green /= sample_rate;
    blue /= sample_rate;
    alpha /= sample_rate;
    unsigned char *f = &framebuffer[0] + 4 * fpix;
    f[0] = red;
    f[1] = green;
    f[2] = blue;
    f[3] = alpha;
  }
}

// rasterize a point from a line
void DrawRend::rasterize_line_point( float x, float y, Color color ) {
  // fill in the nearest pixel
  int sx = (int) floor(x) * sqrt(sample_rate);
  int sy = (int) floor(y) * sqrt(sample_rate);

  // check bounds
  if ( sx < 0 || sx >= width * sqrt(sample_rate) ) return;
  if ( sy < 0 || sy >= height * sqrt(sample_rate) ) return;

  int sf = sqrt(sample_rate);

  // perform alpha blending with previous value
  for (int i = 0; i < sample_rate; ++i) {
    unsigned char *p = &superbuffer[0] + 4 * (i + ((sx * sf) + sy * width * sf));
    float Ca = p[3] / 255., Ea = color.a;
    p[0] = (uint8_t) (color.r * 255 * Ea + (1 - Ea) * p[0]);
    p[1] = (uint8_t) (color.g * 255 * Ea + (1 - Ea) * p[1]);
    p[2] = (uint8_t) (color.b * 255 * Ea + (1 - Ea) * p[2]);
    p[3] = (uint8_t) ((1 - (1 - Ea) * (1 - Ca)) * 255);    
  }

}

  // rasterize a point from a shape
void DrawRend::rasterize_shape_point(float x, float y, int xr, int yr, Color color) {
    // check bounds, x and y are floats that hold integer values
  int sx = (int) floor(x);
  int sy = (int) floor(y);

  // check bounds
  if ( sx < 0 || sx >= width ) return;
  if ( sy < 0 || sy >= height ) return;

  int pixelNum = (sy*width + sx) * 4 * sample_rate;
  int sampleNum = xr + (sqrt(sample_rate) * yr);
  int index = pixelNum + 4 * (sampleNum);

  // perform alpha blending with previous value
  unsigned char *p = &superbuffer[0] + index;
  float Ca = p[3] / 255., Ea = color.a;
  p[0] = (uint8_t) (color.r * 255 * Ea + (1 - Ea) * p[0]);
  p[1] = (uint8_t) (color.g * 255 * Ea + (1 - Ea) * p[1]);
  p[2] = (uint8_t) (color.b * 255 * Ea + (1 - Ea) * p[2]);
  p[3] = (uint8_t) ((1 - (1 - Ea) * (1 - Ca)) * 255);

}



  // rasterize a line
void DrawRend::rasterize_line( float x0, float y0,
                     float x1, float y1,
                     Color color) {

  int dx = x1-x0;
  int dy = y1-y0;

  if (dx >= 0 && dy>=0) { //Quad I
    if (dy <= dx) { //Oct 1
      int x = x0, y = y0, e = -dx;
      while (x < x1) {
        rasterize_line_point(x, y, color);

        x += 1;
        e += 2*dy;
        if (e >= 0.0) {
          y += 1;
          e -= 2*dx;
        }
      }

    } else { //Oct 2
      int x = y0, y = x0, e = -dy;
      while (x < y1) {
        rasterize_line_point(y, x, color);

        x += 1;
        e += 2*dx;
        if (e >= 0.0) {
          y += 1;
          e -= 2*dy;
        }
      }

    }
  } else if (dx < 0 && dy>=0) { //Quad II
    if (-dx < dy) { //Oct 3 -nw
      int x = y0, y = -x0, e = -dy;
      while (x < y1) {
        rasterize_line_point(-y, x, color); 

        x += 1;
        e += 2* -dx;
        if (e >= 0.0) {
          y += 1;
          e -= 2*dy;
        }
      }

    } else { //Oct 4
      int x = -x0, y = y0, e = -dx;
      while (x < -x1) {
        rasterize_line_point(-x, y, color);

        x += 1;
        e += 2*dy;
        if (e >= 0.0) {
          y += 1;
          e -= 2* -dx;
        }
      }

    }
  } else if (dx < 0 && dy < 0){ //Quad III
    if (-dy < -dx) { //Oct 5 
      int x = -x0, y = -y0, e = dx;
      while (x < -x1) {
        rasterize_line_point(-x, -y, color);

        x += 1;
        e += 2* -dy;
        if (e >= 0.0) {
          y += 1;
          e -= 2* -dx;
        }
      }

    } else { //Oct 6 
      int x = -y0, y = -x0, e = dy;
      while (x < -y1) {
        rasterize_line_point(-y, -x, color);

        x += 1;
        e += 2* -dx;
        if (e >= 0.0) {
          y += 1;
          e -= 2* -dy;
        }
      }

    }
  } else { //Quad IV
    if (dx < -dy) { //Oct 7
      int x = -y0, y = x0, e = dy;
      while (x < -y1) {
        rasterize_line_point(y, -x, color); 

        x += 1;
        e += 2*dx;
        if (e >= 0.0) {
          y += 1;
          e -= 2* -dy;
        }
      }

    } else { //Oct 8
      int x = x0, y = -y0, e = -dx;
      while (x < x1) {
        rasterize_line_point(x, -y, color);

        x += 1;
        e += 2* -dy;
        if (e >= 0.0) {
          y += 1;
          e -= 2*dx;
        }
      }
    }
  }


}

  // rasterize a triangle
void DrawRend::rasterize_triangle( float x0, float y0,
                         float x1, float y1,
                         float x2, float y2,
                         Color color, Triangle *tri) {
  
  int sf = sqrt(sample_rate);
  float xmin = floor(min(x0, min(x1,x2)));
  float xmax = ceil(max(x0, max(x1,x2)));
  float ymin = floor(min(y0, min(y1,y2)));
  float ymax = ceil(max(y0, max(y1,y2)));

  for (float y = ymin; y < ymax; y++) {
    for (int yr = 0; yr < sf; yr++) {
      float sy = y + (yr+1.0)/(sf+1.0);
      for (float x = xmin; x < xmax; x++) {
        for (int xr = 0; xr < sf; xr++) {
          float sx = x + (xr+1.0)/(sf+1.0);

          float alpha = ((y1 - y2)*sx + (x2 - x1)*sy + x1*y2 - x2*y1) /  ((y1 - y2)*x0 + (x2 - x1)*y0 + x1*y2 - x2*y1);
          float beta =  ((y2 - y0)*sx + (x0 - x2)*sy + x2*y0 - x0*y2) /  ((y2 - y0)*x1 + (x0 - x2)*y1 + x2*y0 - x0*y2);
          float gamma = 1 - alpha - beta;
          if (alpha >= -.0001 && beta >= -.0001 && gamma >= -.0001 && alpha <= 1 && beta <= 1 && gamma <= 1) {
            if (tri) {
              Color col = tri->color(alpha, beta, color); 
              rasterize_shape_point(x, y, xr, yr, col);
            } else {
              rasterize_shape_point(x, y, xr, yr, color);          
            }
          }

        }
      }
    }
  }
}

  // rasterize a circle
void DrawRend::rasterize_circle( float cx, float cy, float r, Color color, Circle *cir ) {

  int sf = sqrt(sample_rate);
  float xmin = floor(cx - r);
  float xmax = ceil(cx + r);
  float ymin = floor(cy - r);
  float ymax = ceil(cy + r);

  for (float y = ymin; y <= ymax; y++) {
    for (int yr = 0; yr < sf; yr++) {
      float sy = y + (yr+1.0)/(sf+1.0);
      for (float x = xmin; x <= xmax; x++) {
        for (int xr = 0; xr < sf; xr++) {
          float sx = x + (xr+1.0)/(sf+1.0);

          float dist = sqrt((cx - sx)*(cx - sx) + (cy - sy)*(cy - sy));

          if (dist <= r) {
            if (cir) {
              Color col = cir->color(dist/r, color);
              rasterize_shape_point(x, y, xr, yr, col);
            } else {
              rasterize_shape_point(x, y, xr, yr, color);          
            }
          }

        }
      }
    }
  }
}


}
