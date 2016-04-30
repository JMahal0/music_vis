#include "drawrend.h"
#include "svg.h"
#include "transforms.h"
#include "CGL/misc.h"
#include <iostream>
#include <sstream>
#include "CGL/lodepng.h"
#include "texture.h"
#include <ctime>
#include "math.h"

#include <typeinfo>

using namespace std;

namespace CGL {

// struct SVG;


DrawRend::~DrawRend( void ) {}

/**
* Initialize the renderer.
* Set default parameters and initialize the viewing transforms for each tab.
*/
void DrawRend::init() {
  sample_rate = 1;
  left_clicked = false;
  show_zoom = 0;

  svg_to_ndc.resize(svgs.size());
  for (int i = 0; i < svgs.size(); ++i) {
    current_svg = i;
    view_init();
  }
  current_svg = 0;
  psm = P_NEAREST;
  lsm = L_ZERO;

  
}

/**
* Draw content.
* Simply reposts the framebuffer and the zoom window, if applicable.
*/
void DrawRend::render() {
  draw_pixels();
  if (show_zoom)
    draw_zoom();
}

/**
 * Respond to buffer resize.
 * Resizes the buffers and resets the 
 * normalized device coords -> screen coords transform.
 * \param w The new width of the context
 * \param h The new height of the context
 */
void DrawRend::resize( size_t w, size_t h ) {
  width = w; height = h;

  framebuffer.resize(4 * w * h);
  // int rows = 4 * w * h; //was 4*w*h w*h - if this dont work, revert here and everywhere
  // int cols = sample_rate; // was sample_rate
  // // sbuffer.resize(rows, vector<Color>(cols, Color::RealWhite)); // may have to reverse rows and cols
  superbuffer.resize(4 * w * h * sample_rate);

  float scale = min(width, height);
  ndc_to_screen(0,0) = scale; ndc_to_screen(0,2) = (width  - scale) / 2;
  ndc_to_screen(1,1) = scale; ndc_to_screen(1,2) = (height - scale) / 2;

  redraw();
  // cout << typeid(framebuffer).name() << "\n";

}

/**
 * Return a brief description of the renderer.
 * Displays current buffer resolution, sampling method, sampling rate.
 */
static const string level_strings[] = { "level zero", "nearest level", "bilinear level interpolation"};
static const string pixel_strings[] = { "nearest pixel", "bilinear pixel interpolation"};
std::string DrawRend::info() { 
  stringstream ss;
  stringstream sample_method;
  sample_method <<  level_strings[lsm] << ", " << pixel_strings[psm];
  ss << "Resolution " << width << " x " << height << ". ";
  ss << "Using " << sample_method.str() << " sampling. ";
  ss << "Supersample rate " << sample_rate << " per pixel. ";
  return ss.str(); 
}

/**
 * Respond to cursor events.
 * The viewer itself does not really care about the cursor but it will take
 * the GLFW cursor events and forward the ones that matter to  the renderer.
 * The arguments are defined in screen space coordinates ( (0,0) at top
 * left corner of the window and (w,h) at the bottom right corner.
 * \param x the x coordinate of the cursor
 * \param y the y coordinate of the cursor
 */
void DrawRend::cursor_event( float x, float y ) { 
  // translate when left mouse button is held down
  if (left_clicked) {
    float dx = (x - cursor_x) / width  * svgs[current_svg]->width;
    float dy = (y - cursor_y) / height * svgs[current_svg]->height;
    move_view(dx,dy,1);
    redraw();
  }
  
  // register new cursor location
  cursor_x = x;
  cursor_y = y;
}

/**
 * Respond to zoom event.
 * Like cursor events, the viewer itself does not care about the mouse wheel
 * either, but it will take the GLFW wheel events and forward them directly
 * to the renderer.
 * \param offset_x Scroll offset in x direction
 * \param offset_y Scroll offset in y direction
 */
void DrawRend::scroll_event( float offset_x, float offset_y ) {
  if (offset_x || offset_y) {
    float scale = 1 + 0.05 * (offset_x + offset_y);
    scale = std::min(1.5f,std::max(0.5f,scale));
    move_view(0,0,scale);
    redraw();
  }
}

/**
 * Respond to mouse click event.
 * The viewer will always forward mouse click events to the renderer.
 * \param key The key that spawned the event. The mapping between the
 *        key values and the mouse buttons are given by the macros defined
 *        at the top of this file.
 * \param event The type of event. Possible values are 0, 1 and 2, which
 *        corresponds to the events defined in macros.
 * \param mods if any modifier keys are held down at the time of the event
 *        modifiers are defined in macros.
 */
void DrawRend::mouse_event( int key, int event, unsigned char mods ) {
  if (key == MOUSE_LEFT) {
    if (event == EVENT_PRESS)
      left_clicked = true;
    if (event == EVENT_RELEASE)
      left_clicked = false;
  }
}

/**
 * Respond to keyboard event.
 * The viewer will always forward mouse key events to the renderer.
 * \param key The key that spawned the event. ASCII numbers are used for
 *        letter characters. Non-letter keys are selectively supported
 *        and are defined in macros.
 * \param event The type of event. Possible values are 0, 1 and 2, which
 *        corresponds to the events defined in macros.
 * \param mods if any modifier keys are held down at the time of the event
 *        modifiers are defined in macros.
 */
void DrawRend::keyboard_event( int key, int event, unsigned char mods ) {
  if (event != EVENT_PRESS)
    return;

  // tab through the loaded files
  if (key >= '1' && key <= '9' && key-'1' < svgs.size()) {
    current_svg = key - '1';
    redraw();
    return;
  } 

  switch( key ) {

    // reset view transformation
    case ' ':
      view_init();
      redraw();
      break;

    // set the sampling rate to 1, 4, 9, or 16
    case '=':
      if (sample_rate < 16) {
        sample_rate = (int)(sqrt(sample_rate)+1)*(sqrt(sample_rate)+1);
        // Part 3: might need to add something here
        // total_sample_pts = ;
        // int rows = 4 * width * height;
        // int cols =  sample_rate;
        // sbuffer.resize(rows, vector<Color>(cols, Color::RealWhite));

        // for (int i = 0; i < rows; ++i) {
        //   int eee = (sbuffer[i]).size();
        //   printf("%d %d\n", i, eee);
        //   // for (int j = 0; j < cols; ++i) {
        //   //   // sbuffer[i][j] = Color::RealWhite;
        //   // }
        // }

        // // for (int i = 0; i < rows; ++i)
        // // {
        // //   sbuffer[i].resize()
        // // }

        superbuffer.resize(4 * width * height * sample_rate);
        memset(&superbuffer[0], 255, 4 *width * height * sample_rate);

        redraw();
      }
      break;
    case '-':
      if (sample_rate > 1) {
        sample_rate = (int)(sqrt(sample_rate)-1)*(sqrt(sample_rate)-1);
        // Part 3: might need to add something here
        // total_sample_pts = width * height * sample_rate;
        // int rows = 4 *width * height;
        // int cols = sample_rate;
        // sbuffer.resize(rows, vector<Color>(cols, Color::RealWhite));
        

        superbuffer.resize(4 * width * height * sample_rate);
        memset(&superbuffer[0], 255, 4 * width * height * sample_rate);

        redraw();
      }
      break;

    // save the current buffer to disk 
    case 'S':
      write_screenshot();
      break;

    // toggle pixel sampling scheme
    case 'P':
      psm = (PixelSampleMethod)((psm+1)%2);
      redraw();
      break;
    // toggle level sampling scheme
    case 'L':
      lsm = (LevelSampleMethod)((lsm+1)%3);
      redraw();
      break;

    // toggle zoom
    case 'Z':
      show_zoom = (show_zoom+1)%2;
      break;

    default:
      return;
  }
}

/**
 * Writes the contents of the pixel buffer to disk as a .png file.
 * The image filename contains the month, date, hour, minute, and second
 * to make sure it is unique and identifiable.
 */
void DrawRend::write_screenshot() {
    redraw();
    if (show_zoom) draw_zoom();

    vector<unsigned char> windowPixels( 4*width*height );
    glReadPixels(0, 0, 
                width,
                height,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                &windowPixels[0] );

    vector<unsigned char> flippedPixels( 4*width*height );
    for (int row = 0; row < height; ++row)
      memcpy(&flippedPixels[row * width * 4], &windowPixels[(height - row - 1) * width * 4], 4*width);

    time_t t = time(nullptr);
    tm *lt = localtime(&t);
    stringstream ss;
    ss << "screenshot_" << lt->tm_mon+1 << "-" << lt->tm_mday << "_" 
      << lt->tm_hour << "-" << lt->tm_min << "-" << lt->tm_sec << ".png";
    string file = ss.str();
    cout << "Writing file " << file << "...";
    if (lodepng::encode(file, flippedPixels, width, height))
      cerr << "Could not be written" << endl;
    else 
      cout << "Success!" << endl;
}

/**
 * Draws the current SVG tab to the screen. Also draws a 
 * border around the SVG canvas. Resolves the supersample buffers
 * into the framebuffer before posting the framebuffer pixels to the screen.
 */
void DrawRend::redraw() {
  memset(&framebuffer[0], 255, 4 * width * height);
  memset(&superbuffer[0], 255, 4 * width * height * sample_rate);

  // int rows = width * height;
  // int cols = 4 * sample_rate;
  // sbuffer.resize(rows, vector<Color>(cols, Color::RealWhite)); //might not need this

  SVG &svg = *svgs[current_svg];
  svg.draw(this, ndc_to_screen*svg_to_ndc[current_svg]);

  // draw canvas outline
  Vector2D a = ndc_to_screen*svg_to_ndc[current_svg]*(Vector2D(    0    ,     0    )); a.x--; a.y++;
  Vector2D b = ndc_to_screen*svg_to_ndc[current_svg]*(Vector2D(svg.width,     0    )); b.x++; b.y++;
  Vector2D c = ndc_to_screen*svg_to_ndc[current_svg]*(Vector2D(    0    ,svg.height)); c.x--; c.y--;
  Vector2D d = ndc_to_screen*svg_to_ndc[current_svg]*(Vector2D(svg.width,svg.height)); d.x++; d.y--;

  rasterize_line(a.x, a.y, b.x, b.y, Color::Black);
  rasterize_line(a.x, a.y, c.x, c.y, Color::Black);
  rasterize_line(d.x, d.y, b.x, b.y, Color::Black);
  rasterize_line(d.x, d.y, c.x, c.y, Color::Black);

  resolve();
  draw_pixels();
}

/**
 * Resolves whatever supersampling buffer you create into the
 * framebuffer pixel vector in preparation for draw_pixels();
 */
void DrawRend::resolve() { //where downsampling happens!
  // Part 3: Fill this in
  
  //Average the values of superbuffer here and then put into framebuffer

  for (int fpix = 0; fpix < width * height; fpix++) { // goes thru all pixels in framebuffer

    // fpix is the number of the pixel in the framebuffer ~
    
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

/**
 * OpenGL boilerplate to put an array of RGBA pixels on the screen.
 */
void DrawRend::draw_pixels() {
  const unsigned char *pixels = &framebuffer[0];
  // copy pixels to the screen
  glPushAttrib( GL_VIEWPORT_BIT );
  glViewport(0, 0, width, height);

  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  glOrtho( 0, width, 0, height, 0, 0 );

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  glTranslatef( -1, 1, 0 );

  glRasterPos2f(0, 0);
  glPixelZoom( 1.0, -1.0 );
  glDrawPixels( width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
  glPixelZoom( 1.0, 1.0 );

  glPopAttrib();
  glMatrixMode( GL_PROJECTION ); glPopMatrix();
  glMatrixMode( GL_MODELVIEW  ); glPopMatrix();
}

/**
 * Reads off the pixels that should be in the zoom window, and
 * generates a pixel array with the zoomed view.
 */
void DrawRend::draw_zoom() {

  // size (in pixels) of region of interest
  size_t regionSize = 32;

  // relative size of zoom window
  size_t zoomFactor = 16;
  
  // compute zoom factor---the zoom window should never cover
  // more than 40% of the framebuffer, horizontally or vertically
  size_t bufferSize = min( width, height );
  if( regionSize*zoomFactor > bufferSize * 0.4) {
    zoomFactor = (bufferSize * 0.4 )/regionSize;
  }
  size_t zoomSize = regionSize * zoomFactor;

  // adjust the cursor coordinates so that the region of
  // interest never goes outside the bounds of the framebuffer
  size_t cX = max( regionSize/2, min( width-regionSize/2-1, (size_t) cursor_x ));
  size_t cY = max( regionSize/2, min( height-regionSize/2-1, height - (size_t) cursor_y ));

  // grab pixels from the region of interest
  vector<unsigned char> windowPixels( 3*regionSize*regionSize );
  glReadPixels( cX - regionSize/2,
                cY - regionSize/2 + 1, // meh
                regionSize,
                regionSize,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                &windowPixels[0] );

  // upsample by the zoom factor, highlighting pixel boundaries
  vector<unsigned char> zoomPixels( 3*zoomSize*zoomSize );
  unsigned char* wp = &windowPixels[0];
  // outer loop over pixels in region of interest
  for( int y = 0; y < regionSize; y++ ) {
   int y0 = y*zoomFactor;
   for( int x = 0; x < regionSize; x++ ) {
      int x0 = x*zoomFactor;
      unsigned char* zp = &zoomPixels[ ( x0 + y0*zoomSize )*3 ];
      // inner loop over upsampled block
      for( int j = 0; j < zoomFactor; j++ ) {
        for( int i = 0; i < zoomFactor; i++ ) {
          for( int k = 0; k < 3; k++ ) {
            // highlight pixel boundaries
            if( i == 0 || j == 0 ) {
              const float s = .3;
              zp[k] = (int)( (1.-2.*s)*wp[k] + s*255. );
            } else {
              zp[k] = wp[k];
            }
          }
          zp += 3;
        }
        zp += 3*( zoomSize - zoomFactor );
      }
      wp += 3;
    }
  }

  // copy pixels to the screen using OpenGL
  glMatrixMode( GL_PROJECTION ); glPushMatrix(); glLoadIdentity(); glOrtho( 0, width, 0, height, 0.01, 1000. );
  glMatrixMode( GL_MODELVIEW  ); glPushMatrix(); glLoadIdentity(); glTranslated( 0., 0., -1. );
  
  glRasterPos2i( width-zoomSize, height-zoomSize );  
  glDrawPixels( zoomSize, zoomSize, GL_RGB, GL_UNSIGNED_BYTE, &zoomPixels[0] );
  glMatrixMode( GL_PROJECTION ); glPopMatrix();
  glMatrixMode( GL_MODELVIEW ); glPopMatrix();

}

/**
 * Initializes the default viewport to center and reasonably zoom the SVG
 * with a bit of margin.
 */
void DrawRend::view_init() {
  float w = svgs[current_svg]->width, h = svgs[current_svg]->height;
  set_view(w/2, h/2, 1.2 * std::max(w,h) / 2);
}

/**
 * Sets the viewing transform matrix corresponding to a view centered at 
 * (x,y) in SVG space, extending 'span' units in all four directions.
 * This transform maps to 'normalized device coordinates' (ndc), where the window
 * corresponds to the [0,1]^2 rectangle.
 */
void DrawRend::set_view(float x, float y, float span) {
  svg_to_ndc[current_svg] = Matrix3x3(1,0,-x+span,  0,1,-y+span,  0,0,2*span);
}

/**
 * Recovers the previous viewing center and span from the viewing matrix, 
 * then shifts and zooms the viewing window by setting a new view matrix.
 */
void DrawRend::move_view(float dx, float dy, float zoom) {
  // Part 4: Fill this in

  //Extract the x,y, and span  values from svg_to_ndc made in set_view 

  double span = svg_to_ndc[current_svg](2, 2) / 2.0;
  double x = span - svg_to_ndc[current_svg](0, 2);
  double y = span - svg_to_ndc[current_svg](1, 2);


  //Add dx to x, dy to y, and mult zoom to span
  //Call set_view with updated values
  set_view(x-dx, y-dy, span/zoom);

}

  // rasterize a point
void DrawRend::rasterize_point( float x, float y, Color color ) {
  // fill in the nearest pixel
  int sx = (int) floor(x) * sqrt(sample_rate);
  int sy = (int) floor(y) * sqrt(sample_rate);

  // check bounds
  if ( sx < 0 || sx >= width * sqrt(sample_rate) ) return;
  if ( sy < 0 || sy >= height * sqrt(sample_rate) ) return;

  int sf = sqrt(sample_rate);

  // perform alpha blending with previous value
  for (int i = 0; i < sample_rate; ++i)
  {
    unsigned char *p = &superbuffer[0] + 4 * (i + ((sx * sf) + sy * width * sf));
    float Ca = p[3] / 255., Ea = color.a;
    p[0] = (uint8_t) (color.r * 255 * Ea + (1 - Ea) * p[0]);
    p[1] = (uint8_t) (color.g * 255 * Ea + (1 - Ea) * p[1]);
    p[2] = (uint8_t) (color.b * 255 * Ea + (1 - Ea) * p[2]);
    p[3] = (uint8_t) ((1 - (1 - Ea) * (1 - Ca)) * 255);
    
  }




}

  // rasterize a point from rasterize_triangle
void DrawRend::rasterize_tri_point(float x, float y, int xr, int yr, Color color) {
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

  // Color prev = sbuffer[row][col];
  // float Ca = prev.a / 255., Ea = color.a;
  // float red = (uint8_t) (color.r * 255 * Ea + (1 - Ea) * prev.r);
  // float gre = (uint8_t) (color.g * 255 * Ea + (1 - Ea) * prev.g);
  // float blu = (uint8_t) (color.b * 255 * Ea + (1 - Ea) * prev.b);
  // float alp = (uint8_t) ((1 - (1 - Ea) * (1 - Ca)) * 255); 
  // Color *nc = new Color(red, gre, blu, alp);
  // sbuffer[row][col] = *nc;

}



  // rasterize a line
void DrawRend::rasterize_line( float x0, float y0,
                     float x1, float y1,
                     Color color) {

  // Part 1: Fill this in
  int dx = x1-x0;
  int dy = y1-y0;

  if (dx >= 0 && dy>=0) { //Quad I
    if (dy <= dx) { //Oct 1
      int x = x0, y = y0, e = -dx;
      while (x < x1) {
        rasterize_point(x, y, color);

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
        rasterize_point(y, x, color);

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
        rasterize_point(-y, x, color); 

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
        rasterize_point(-x, y, color);

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
        rasterize_point(-x, -y, color);

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
        rasterize_point(-y, -x, color);

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
        rasterize_point(y, -x, color); 

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
        rasterize_point(x, -y, color);

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
  // Part 2: Fill in this function with basic triangle rasterization code
  // Part 3: Add supersampling to antialias your triangles
  // Part 5: Add barycentric coordinates and use tri->color for shading when available
  // Part 6: Fill in a SampleParams struct with psm, lsm and pass it to the tri->color function
  // Part 7: Pass in correct barycentric differentials dx and dy to tri->color for mipmapping
  
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

              float dxalpha = ((y1 - y2)*(sx+1) + (x2 - x1)*sy + x1*y2 - x2*y1) /  ((y1 - y2)*x0 + (x2 - x1)*y0 + x1*y2 - x2*y1);
              float dxbeta =  ((y2 - y0)*(sx+1) + (x0 - x2)*sy + x2*y0 - x0*y2) /  ((y2 - y0)*x1 + (x0 - x2)*y1 + x2*y0 - x0*y2);

              float dyalpha = ((y1 - y2)*sx + (x2 - x1)*(sy+1) + x1*y2 - x2*y1) /  ((y1 - y2)*x0 + (x2 - x1)*y0 + x1*y2 - x2*y1);
              float dybeta =  ((y2 - y0)*sx + (x0 - x2)*(sy+1) + x2*y0 - x0*y2) /  ((y2 - y0)*x1 + (x0 - x2)*y1 + x2*y0 - x0*y2);

              SampleParams* sp = new SampleParams();
              sp->psm = psm;
              sp->lsm = lsm;
              Color col = tri->color(Vector2D(alpha, beta), Vector2D(dxalpha, dxbeta), Vector2D(dyalpha, dybeta), *sp); 
              rasterize_tri_point(x, y, xr, yr, col); 
              
            } else {
              rasterize_tri_point(x, y, xr, yr, color);          
            }
          }

        }
      }
    }
  }


}



}
