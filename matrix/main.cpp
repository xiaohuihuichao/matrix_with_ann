#include "Matrix.h"

int main(int argc, char **argv)
{
	try
	{
		mario::Matrix a, b(3, 3, 1);
		//std::cout << b.get(0, 1);
		//a = b;
		//std::cout << a.rows() << a.cols() << a.get(1, 1);
		mario::Matrix c(b);
		c.set(0, 0, 1);
		c.set(1, 1, 100);
		c.set(2, 2, 10);
		c.set(0, 2, 7);
		cout << c.rows() << c.cols() << c.get(1, 1) << endl;
		cout << c << c * c << c.inv_LU() * c << c.getDet() << endl;

		mario::Matrix d = mario::matrixRand(2, 2, -2, 9);

		cout << d << d.inv_LU() * d;

		d.release();

		d = mario::diag(5, 2.1);

		cout << d << d.inv_LU() << d*d.inv_LU();
	}
	catch (const char* e)
	{
		cerr << e << endl;
	}
	
	return 0;
}
