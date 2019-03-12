#ifndef DROPOUT_LAYER_H_
#define DROPOUT_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class DropoutLayer : public Operator
	{
	private:
		double m_p;

		matrix m_in;
		matrix m_mul;
		matrix m_out;
		
		matrix m_dx;

	public:
		DropoutLayer(const int &_lastNeuronNum, const double &_p=-1);

		const matrix& forward(const matrix &_lastOut);
		const matrix& backward(const matrix &_nextDerr);

	protected:
		bool isDelete();

	}Dropout;
}

#endif // !DROPOUT_LAYER_H_
