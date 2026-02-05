#include <iostream>
#include "Point.class.hpp"

using std::cout;
using std::endl;

static void displayTriangleInfo(Point const a, Point const b, Point const c) {
    cout << "\n[Triangle Configuration]" << endl;
    cout << "  Vertex A: (" << a.x() << ", " << a.y() << ")" << endl;
    cout << "  Vertex B: (" << b.x() << ", " << b.y() << ")" << endl;
    cout << "  Vertex C: (" << c.x() << ", " << c.y() << ")" << endl;
}

bool	bsp( Point const a, Point const b, Point const c, Point const point);

int main(void) {
    cout << "=== Testing BSP (Point in Triangle) ===" << endl;

    // Define triangle vertices
    Point a(0.0f, 0.0f);
    Point b(4.0f, 0.0f);
    Point c(2.0f, 4.0f);

	displayTriangleInfo(a, b, c);

    // Test cases
    cout << "\n--- Test 1: Point inside the triangle ---" << endl;
    Point p1(2.0f, 1.0f);  // Inside the triangle
    cout << "Is point (2.0, 1.0) inside? " << (bsp(a, b, c, p1) ? "Yes" : "No") << endl;

    cout << "\n--- Test 2: Point outside the triangle ---" << endl;
    Point p2(5.0f, 2.0f);  // Outside the triangle
    cout << "Is point (5.0, 2.0) inside? " << (bsp(a, b, c, p2) ? "Yes" : "No") << endl;

    cout << "\n--- Test 3: Point on the edge ---" << endl;
    Point p3(2.0f, 0.0f);  // On the edge (between a and b)
    cout << "Is point (2.0, 0.0) inside? " << (bsp(a, b, c, p3) ? "Yes" : "No") << endl;

    cout << "\n--- Test 4: Point on a vertex ---" << endl;
    Point p4(4.0f, 0.0f);  // On vertex b
    cout << "Is point (4.0, 0.0) inside? " << (bsp(a, b, c, p4) ? "Yes" : "No") << endl;

    cout << "\n--- Test 5: Degenerate triangle ---" << endl;
    Point d(0.0f, 0.0f);
    Point e(2.0f, 2.0f);
    Point f(4.0f, 4.0f);  // Collinear: degenerate triangle
	
	displayTriangleInfo(d, e ,f);
	cout << endl;

    Point p5(1.0f, 1.0f);  // On the line
    
	cout << "Is point (1.0, 1.0) inside the degenerate triangle? " << (bsp(d, e, f, p5) ? "Yes" : "No") << endl;

    cout << "\n--- Test 6: Point outside but close ---" << endl;
    Point p6(3.0f, -0.1f);  // Just below the edge
    cout << "Is point (3.0, -0.1) inside? " << (bsp(a, b, c, p6) ? "Yes" : "No") << endl;

    return 0;
}
