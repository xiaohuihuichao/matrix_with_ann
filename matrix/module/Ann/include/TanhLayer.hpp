#ifndef TANH_LAYER_H_
#define TANH_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class TanhLayer : public Operator
	{
	private:
		matrix m_in;
		matrix m_out;
		matrix m_dx;

	public:
		TanhLayer();
		TanhLayer(const int &_col);
		~TanhLayer();

		const matrix& forward(const matrix &_lastOut);
		const matrix& backward(const matrix &_nextDerr);

	}Tanh;
}

#endif // !TANH_LAYER_H_