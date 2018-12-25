#ifndef MEAN_SQUARE_ERROR_LAYER_H_
#define MEAN_SQUARE_ERROR_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class MeanSquareErrorLayer : public Operator
	{
	private:
		matrix m_in;
		matrix m_out;

		matrix m_y;
		matrix m_dx;

		double m_loss;

	public:
		MeanSquareErrorLayer();
		MeanSquareErrorLayer(const int &_col);
		~MeanSquareErrorLayer();

		double getLoss() const;

		const matrix& forward(const matrix &_lastOut);
		const matrix& backward(const matrix &_y);

	protected:
		void setLabel(const matrix &_y);
		double calLoss();

	}Mse;
}

#endif // !MEAN_SQUARE_ERROR_LAYER_H_