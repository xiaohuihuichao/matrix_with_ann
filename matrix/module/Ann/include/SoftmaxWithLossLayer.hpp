#ifndef SOFTMAX_WITH_LOSS_LAYER_H_
#define SOFTMAX_WITH_LOSS_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class SoftmaxWithLossLayer : public Operator
	{
	private:
		matrix m_in;
		matrix m_out;

		matrix m_y;
		matrix m_dx;

		double m_loss;

	public:
		SoftmaxWithLossLayer();
		SoftmaxWithLossLayer(const int &_col);
		~SoftmaxWithLossLayer();

		double getLoss() const;

		const matrix& forward(const matrix &_lastOut);
		const matrix& backward(const matrix &_y);

	protected:
		double calLoss();
		void setLabel(const matrix &_y);

	}Softmax;
}

#endif // !SOFTMAX_WITH_LOSS_LAYER_H_