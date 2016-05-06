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
		// std::cout << "[Visualization] - Triangle calling rasterize" << std::endl;
		dr->rasterize_triangle( a.x, a.y, b.x, b.y, c.x, c.y, fill_color, this );
	} else {
		std::cout << "[Visualization] - Triangle has alpha of 0" << std::endl;
	}
	
}

Color Triangle::color(float alpha, float beta) {
	return fill_color;
}

// Returns the appropriate weighted combination of the
// three colors.
Color GradiantTri::color(float alpha, float beta) {
	ac.a = fill_color.a;
	bc.a = fill_color.a;
	cc.a = fill_color.a;


	float gamma = 1 - alpha - beta;
	return alpha*ac + beta*bc + gamma*cc;
}

void Line::draw(DrawRend *dr, Matrix3x3 global_transform) {

	if (fill_color.a != 0) {
		Vector2D p0 = global_transform * p0;
		Vector2D p1 = global_transform * p1;
		std::cout << "[Visualization] - Line calling rasterize" << std::endl;
		dr->rasterize_line(p0.x, p0.y, p1.x, p1.y, fill_color);
	}
	
}

void Rectangle::draw(DrawRend *dr, Matrix3x3 global_transform) {
	
	// std::cout << "[Rectangle] - drawing if not 0 " << fill_color.a << std::endl;

	Vector2D p0 = global_transform * p;
	Vector2D p1 = global_transform * Vector2D( p.x + w , p.y );
	Vector2D p2 = global_transform * Vector2D( p.x , p.y + h );
	Vector2D p3 = global_transform * Vector2D( p.x + w , p.y + h );

	if (fill_color.a != 0 ) {
		std::cout << "[Visualization] - Rectangle calling rasterize" << std::endl;
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
		// std::cout << "[Visualization] - Circle calling rasterize" << std::endl;
		dr->rasterize_circle( center.x, center.y, radius, fill_color, this);
	}
}

Color Circle::color(float distance) {
	return fill_color;
}

// Returns the weighted combo of the the color at the 
// origin (near_c) and the color at the edge (far_c).
// distance is the distance from the origin / the radius.
Color GradiantCir::color(float distance) {
	near_c.a = fill_color.a;
	far_c.a = fill_color.a;
	Color col = distance*far_c + (1 - distance)*near_c;
	// std::cout << "[GradiantCir::color] distance is " << distance << " color is " << col << std::endl;
	return col;
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
// and will add them to the vshapes vector. 
// Index tells where the current data point is and length is total
// number of data points.
void Visualization::visualizeMono(Aquila::ComplexType m_data, int index, int length) {
	int er = 3;
}

// The function will create a list of VShapes using both 
// of the m_data and will add them to the vshapes vector.  
// Index tells where the current data point is and length is total
// number of data points.
void Visualization::visualizeStereo(Aquila::ComplexType m_data_left, Aquila::ComplexType m_data_right, int index, int length, double str_left, double str_right) {
	
	// Rectangle r1 = Rectangle(1.0, Color::Black, Vector2D(0.0, -2.0), 5.0, 2.5) ;
	Triangle t1 = Triangle(1.0, color_accent_low, Vector2D(0.0, 0.0), Vector2D(0.0, 100), Vector2D(200, 0));


	// GradiantTri gt1 = GradiantTri(1.0, color_main_low, Vector2D(0.0, 0.0), Vector2D(0.0, 122.0), Vector2D(58.0, 3.0), color_main_low, color_accent_high, color_secondary_high );
	// Line l1 = Line(1.0, color_secondary_high, Vector2D(0, 0), Vector2D(320, 240));
	// Circle c2 = Circle(1.0, color_secondary_low, Vector2D(1,1), 1);
	Color f2 = color_secondary_high;
	f2.a = .5;
	// GradiantCir gc1 = GradiantCir(1.0, color_accent_high, Vector2D(6, -2), 3, color_accent_high, color_accent_low);



	float x = (index + 0.0)/length;
	Color f = x*color_secondary_low + (1.0-x)*color_secondary_high;

    double intensity_left = sqrt(m_data_left.real()*m_data_left.real() + m_data_left.imag()*m_data_left.imag());    
    double intensity_right = sqrt(m_data_right.real()*m_data_right.real() + m_data_right.imag()*m_data_right.imag());

	float alf = std::min(std::max(0.1, intensity_right/str_right + intensity_left/str_left)*1.75, 1.0);
	// std::cout << alf << std::endl;
	f.a = alf;

	Circle background = Circle(1.0, x*color_main_low + (1.0-x)*color_main_high, Vector2D(0,480), 640);
	Circle c1 = Circle(1.0, f, Vector2D(640,0), 300);

	Circle lilc = Circle(1.0, color_accent_high, Vector2D(640*x, 10), 16);
	lilc.fill_color.a = .7;

	// std::cout << "Circle r " << c1.r << std::endl;
	// std::cout << "Circle r " << c2.r << std::endl;

	// std::cout << index <<" GradCircle r " << gc1.r << std::endl;
	// std::cout << "GradCircle c " << gc1.far_c << std::endl;



	vshapes.push_back(&background);
	vshapes.push_back(&c1);
	vshapes.push_back(&lilc);

	Circle powc1 = Circle(1.0, color_accent_high , Vector2D(rand() % 640, alf * 480 ), 25);
	float powalph = alf*2;
	if (powalph < .6) {
		powc1.fill_color.a = 0.0;
	} else {
		powc1.fill_color.a = std::min(powalph * 2.5, 1.0);		
	}

	vshapes.push_back(&powc1);
	

	


	// vshapes.push_back(&gc1);

	vshapes.push_back(&t1);

	


	

	// vshapes.push_back(&gt1);
	// vshapes.push_back(&l1);
	// vshapes.push_back(&r1);


}




}

