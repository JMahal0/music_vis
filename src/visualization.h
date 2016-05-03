/**
 * @author Jaskirat Mahal
 * Converts the data from the sound file to shapes that 
 * the renderer will show.
 */

#include <vector>
#include "CGL/color.h"
// #include "texture.h"
#include "CGL/vector2D.h"
#include "CGL/matrix3x3.h"

// #include "transforms.h"

namespace CGL {



class Visualization {
 public:
 	Visualization(Color main_low, Color main_high, Color second_low, Color second_high, Color accent_low, Color accent_high); // all the 6 colors
 	~Visualization();

 	void visualize(Aquila::SpectrumType *m_data);

 	void visualize(Aquila::SpectrumType *m_data_left, Aquila::SpectrumType *m_data_right );

 private:
	Color color_main_low, color_main_high, color_secondary_low, color_secondary_high, color_accent_low, color_accent_high;

};

struct Shape {
	Shape() {}
	~Shape() {}

	// Draws the Shape to the framebuffer
	virtual void draw(DrawRend *dr, Color color) = 0;

	// Makes the Shape's color closer and closer to the
	// background color.
	// Returns whether or not the Shape has completely
	// faded (when time_elapsed >= duration).
	bool fade(double time_elapsed);

	// Amount of frames/sec? until the shape completely 
	// fades into the background
	double duration;

	// The alpha value in RGBA. In range [0,1]
	// Decreases with time in fade function.
	float transparency_a;
};

struct Triangle : Shape {
	Triangle(): Shape() {}
	void draw(DrawRend *dr, Color color);
	virtual Color color(double alpha, double beta, Color c) = c;

	Vector2D a, b, c; // The 3 points of the triangle
};

struct GradiantTri : Triangle {
	GradiantTri(): Triangle() {}
	Color color(double alpha, double beta, Color c);

	Color ac, bc, cc;
};



struct Line : Shape {
	Line(): Shape() {}
	void draw(DrawRend *dr, Color color);

	Vector2D p0, p1;
};

struct Rectangle : Shape {
	Rectangle(): Shape() {}
	void draw(DrawRend *dr, Color color);

	Vector2D p0; // The bottom left corner of the Rectangle
	double w, h;
};

struct Circle : Shape {
	Circle(): Shape() {}
	void draw(DrawRend *dr, Color color);
	virtual Color color(double distance, Color c) = c;

	Vector2D o; // origin
	double r; // radius
};

struct GradiantCir : Circle {
	GradiantCir(): Circle() {}
	Color color(double distance, Color c);

	Color near_c, far_c;
};






}