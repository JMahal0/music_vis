/**
 * @author Jaskirat Mahal
 */

#include "visualization.h"
#include <iostream>
#include "drawrend.h"
#include "CGL/vector2D.h"
#include "CGL/matrix3x3.h"
#include "transforms.h"

#include "aquila/global.h"


namespace CGL {


VShape::VShape(double _duration, Color f_c) {
	duration = _duration;
	transparency_a = 1.0;
	fill_color = f_c;
}

// VShape::draw(DrawRend *dr, Color color, Matrix3x3 global_transform) {
// 	cout << "[Visualization] error - VShape object" ,, endl;
// }

void Triangle::draw(DrawRend *dr, Matrix3x3 global_transform) {

	if (fill_color.a != 0) {
		Vector2D a = global_transform * a;
		Vector2D b = global_transform * b;
		Vector2D c = global_transform * c;

		dr->rasterize_triangle( a.x, a.y, b.x, b.y, c.x, c.y, fill_color, this );
	} else {
		std::cout << "[Visualization] - Triangle has alpha of 0";
	}
	
}

Color Triangle::color(float alpha, float beta) {
	return fill_color;
}

// Returns the appropriate weighted combination of the
// three colors.
Color GradiantTri::color(float alpha, float beta) {
	//ac,bc,cc.alpha = fill_color.alpha
	float gamma = 1 - alpha - beta;
	return alpha*ac + beta*bc + gamma*cc;
}

void Line::draw(DrawRend *dr, Matrix3x3 global_transform) {

	if (fill_color.a != 0) {
		Vector2D p0 = global_transform * p0;
		Vector2D p1 = global_transform * p1;
		dr->rasterize_line(p0.x, p0.y, p1.x, p1.y, fill_color);
	}
	
}

void Rectangle::draw(DrawRend *dr, Matrix3x3 global_transform) {
	
	Vector2D p0 = global_transform * p;
	Vector2D p1 = global_transform * Vector2D( p.x + w , p.y );
	Vector2D p2 = global_transform * Vector2D( p.x , p.y + h );
	Vector2D p3 = global_transform * Vector2D( p.x + w , p.y + h );

	if (fill_color.a != 0 ) {
    dr->rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, fill_color );
    dr->rasterize_triangle( p2.x, p2.y, p1.x, p1.y, p3.x, p3.y, fill_color );
	}

}

void Circle::draw(DrawRend *dr, Matrix3x3 global_transform) {

	if (fill_color.a != 0) {

		Vector2D center = global_transform * o;
		Vector2D tanget_pt = global_transform * Vector2D(o.x + r, o.y);

		double dx = center.x - tanget_pt.x;
		double dy = center.y - tanget_pt.y;

		double radius = sqrt(dx * dx + dy * dy);

		dr->rasterize_circle( center.x, center.y, radius, fill_color);
	}
}

Color Circle::color(float distance) {
	return fill_color;
}

// Returns the weighted combo of the the color at the 
// origin (near_c) and the color at the edge (far_c).
// distance is the distance from the origin / the radius.
Color GradiantCir::color(float distance) {
	//near_c,far_c.alpha = fill_color.alpha
	return distance*far_c + (1 - distance)*near_c;
}


Visualization::Visualization(Color main_low, Color main_high, Color second_low, Color second_high, Color accent_low, Color accent_high) {

	color_main_low = main_low; 
	color_main_high = main_high;
	color_secondary_low = second_low;
	color_secondary_high = second_high; 
	color_accent_low = accent_low;
	color_accent_high = accent_high;

}

// The function will create a list of VShapes using m_data 
// and will return it in the vshape_lst pointer. 
// Index tells where the current data point is.
void Visualization::visualizeMono(Aquila::ComplexType m_data, int index, int length) {
	int er = 3;
}

// The function will create a list of VShapes using both 
// of the m_data and will return it in the vshape_lst pointer.  
// Index tells where the current data point is.
void Visualization::visualizeStereo(Aquila::ComplexType m_data_left, Aquila::ComplexType m_data_right, int index, int length) {
	int er = 3;
}




}

