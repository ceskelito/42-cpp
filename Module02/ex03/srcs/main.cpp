#include <iostream>
#include "Point.class.hpp"

static void displayTriangleInfo(Point const a, Point const b, Point const c) {
    std::cout << "\n[Triangle Configuration]" << std::endl;
    std::cout << "  Vertex A: (" << a.x() << ", " << a.y() << ")" << std::endl;
    std::cout << "  Vertex B: (" << b.x() << ", " << b.y() << ")" << std::endl;
    std::cout << "  Vertex C: (" << c.x() << ", " << c.y() << ")" << std::endl;
}

bool	bsp( Point const a, Point const b, Point const c, Point const point);

int main(void) {
    std::cout << "=== Testing BSP (Point in Triangle) ===" << std::endl;

    // Define triangle vertices
    Point a(0.0f, 0.0f);
    Point b(4.0f, 0.0f);
    Point c(2.0f, 4.0f);

	displayTriangleInfo(a, b, c);

    // Test cases
    std::cout << "\n--- Test 1: Point inside the triangle ---" << std::endl;
    Point p1(2.0f, 1.0f);  // Inside the triangle
    std::cout << "Is point (2.0, 1.0) inside? " << (bsp(a, b, c, p1) ? "Yes" : "No") << std::endl;

    std::cout << "\n--- Test 2: Point outside the triangle ---" << std::endl;
    Point p2(5.0f, 2.0f);  // Outside the triangle
    std::cout << "Is point (5.0, 2.0) inside? " << (bsp(a, b, c, p2) ? "Yes" : "No") << std::endl;

    std::cout << "\n--- Test 3: Point on the edge ---" << std::endl;
    Point p3(2.0f, 0.0f);  // On the edge (between a and b)
    std::cout << "Is point (2.0, 0.0) inside? " << (bsp(a, b, c, p3) ? "Yes" : "No") << std::endl;

    std::cout << "\n--- Test 4: Point on a vertex ---" << std::endl;
    Point p4(4.0f, 0.0f);  // On vertex b
    std::cout << "Is point (4.0, 0.0) inside? " << (bsp(a, b, c, p4) ? "Yes" : "No") << std::endl;

    std::cout << "\n--- Test 5: Degenerate triangle ---" << std::endl;
    Point d(0.0f, 0.0f);
    Point e(2.0f, 2.0f);
    Point f(4.0f, 4.0f);  // Collinear: degenerate triangle
	
	displayTriangleInfo(d, e ,f);
	std::cout << std::endl;

    Point p5(1.0f, 1.0f);  // On the line
    
	std::cout << "Is point (1.0, 1.0) inside the degenerate triangle? " << (bsp(d, e, f, p5) ? "Yes" : "No") << std::endl;

    std::cout << "\n--- Test 6: Point outside but close ---" << std::endl;
    Point p6(3.0f, -0.1f);  // Just below the edge
    std::cout << "Is point (3.0, -0.1) inside? " << (bsp(a, b, c, p6) ? "Yes" : "No") << std::endl;

    return 0;
}
