#include "Point.class.hpp"

static int	sign(Point const &v1, Point const &v2, Point const &test) {

/**
 * @brief Computes the orientation sign of a point relative to a line segment.
 *
 * @param v1    The first endpoint of the line segment.
 * @param v2    The second endpoint of the line segment.
 * @param test  The point whose orientation relative to the line segment is to be determined.
 *
 * @return int
 *   -  1 if the point is on the left side of the line segment (counterclockwise orientation).
 *   - -1 if the point is on the right side of the line segment (clockwise orientation).
 *   -  0 if the point is collinear with the line segment (including vertices).
 *
 * @details
 * This function calculates the sign of the cross product between the vectors (v2 - v1) and (test - v1).
 * The result is derived from the equation of the line passing through v1 and v2:
 *   (v2.y - v1.y) * (test.x - v1.x) - (v2.x - v1.x) * (test.y - v1.y)
 * The formula is expanded and rearranged for computational efficiency.
 *
 * @note
 * The function uses fixed-point arithmetic (Fixed type) to ensure precision and avoid floating-point errors,
 * which is critical for geometric computations where accuracy is paramount.
 */
	Fixed sign	= (v2.y() - v1.y()) * test.x()
				- (v2.x() - v1.x()) * test.y()
				+ (v2.x() - v1.x()) * v1.y()
				- (v2.y() - v1.y()) * v1.x();

	return (sign == 0) ? 0 : (sign > 0) ? 1 : -1;
}

bool	bsp(Point const a, Point const b, Point const c, Point const point) {

/**
 * @brief Checks if a point lies inside a triangle using the barycentric coordinate method.
 *
 * @param a, b, c The three vertices of the triangle.
 * @param point   The point to check for inclusion within the triangle.
 *
 * @return true   If the point is inside the triangle.
 * @return false  If the point is outside the triangle (or on its boundary).
 *
 * @details
 * The function uses the concept of barycentric coordinates to determine the point's position.
 * For each edge of the triangle, it calculates the sign of the point relative to the line equation
 * defined by the edge. The point is inside the triangle if and only if it lies on the same side of
 * all three edges as the opposite vertex. This is verified by comparing the signs of the cross products.
 *
 * @note
 * The function assumes that the points are in a 2D plane and that the triangle is non-degenerate.
 */
	if (sign(a, b, c) == 0)
		return (false);
		
	bool same_side_ab = (sign(a, b, c) == sign(a, b, point) && sign(a, b, point) != 0);
	bool same_side_ac = (sign(a, c, b) == sign(a, c, point) && sign(a, c, point) != 0);
	bool same_side_bc = (sign(b, c, a) == sign(b, c, point) && sign(b, c, point) != 0);

	return ( same_side_ab && same_side_ac && same_side_bc );
}
