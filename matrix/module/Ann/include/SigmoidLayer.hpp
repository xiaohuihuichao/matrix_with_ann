#ifndef SIGMOID_LAYER_H_
#define SIGMOID_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class SigmoidLayer : public Operator
	{
	private:
		matrix m_in;
		matrix m_out;
		matrix m_dx;

	public:
		SigmoidLayer();
		SigmoidLayer(const int &_col);
		~SigmoidLayer();

		const matrix& forward(const matrix &_lastOut);

		const matrix& backward(const matrix &_nextDerr);

	}Sigmoid;
}

#endif // !SIGMOID_LAYER_H_