#ifndef OPERATOR_H_
#define	OPERATOR_H_

#include "Matrix.h"

namespace mario
{
	class Operator
	{
	public:
		Operator();
		virtual const matrix& forward(const matrix &_lastOut) = 0;
		virtual const matrix& backward(const matrix &_nextDerr) = 0;
	
		virtual const matrix& getW() const;
		virtual const matrix& getB() const;

		virtual void update(const double &_learningRate = 0.001);

		virtual double getLoss() const;

	protected:
		virtual void setLabel(const matrix&_x);
		virtual double calcLoss();

	};
}

#endif // !OPERATOR_H_
