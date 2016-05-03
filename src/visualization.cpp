/**
 * @author Jaskirat Mahal
 */

#include "visualization.h"
#include <iostream>
#include "aquila/source/WaveFile.h"


namespace CGL {

// void visualize function
// args maybe are music_data SpectrumType*




void Triangle::draw(DrawRend *dr, Color color) {
	if (color.a != 0) {
		dr->rasterize_triangle( a.x, a.y, b.x, b.y, c.x, c.y, color, this );
	}
	
}

// Returns the appropriate weighted combination of the
// three colors.
Color GradiantTri::color(double alpha, double beta, Color c) {
	double gamma = 1 - alpha - beta;
	return alpha*ac + beta*bc + gamma*cc;
}

void Line::draw(DrawRend *dr, Color color) {
	if (color.a != 0) {
		dr->rasterize_line(p0.x, p0.y, p1.x, p1.y, color);
	}
	
}

void Rectangle::draw(DrawRend *dr, Color color) {
	
	Vector2D p1 = Vector2D( p0.x + w , p0.y );
	Vector2D p2 = Vector2D( p0.x , p0.y + h );
	Vector2D p3 = Vector2D( p0.x + w , p0.y + h );

	if (color.a != 0 ) {
    dr->rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, color );
    dr->rasterize_triangle( p2.x, p2.y, p1.x, p1.y, p3.x, p3.y, color );
	}

}

void Circle::draw(DrawRend *dr, Color color) {
	if (color.a != 0) {
		dr->rasterize_circle( o.x, o.y, r, color);
	}
}

// Returns the weighted combo of the the color at the 
// origin (near_c) and the color at the edge (far_c).
// distance is the distance from the origin / the radius.
Color GradiantCir::color(double distance, Color c) {
	return distance*far_c + (1 - distance)*near_c;
}



}