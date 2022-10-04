#include "Matrix2x2.h"

namespace Ethrl
{
	// 1 0
	// 0 1
	const Matrix2x2 Matrix2x2::identity{ Vector2{1, 0}, Vector2{0, 1} };
	const Matrix2x2 Matrix2x2::zero{ Vector2{0, 0}, Vector2{0, 0} };
}