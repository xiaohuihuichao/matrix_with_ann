#ifndef RELU_LAYER_H_
#define RELU_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class ReluLayer : public Operator
	{
	private:
		matrix m_in;
		matrix m_out;
		matrix m_dx;

	public:
		ReluLayer();
		ReluLayer(const int &_col);
		~ReluLayer();

		const matrix& forward(const matrix &_lastOut);

		const matrix& backward(const matrix &_nextDerr);

	}Relu;
}

#endif // !RELU_LAYER_H_