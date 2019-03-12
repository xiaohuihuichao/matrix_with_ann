#ifndef FULLCONNECTION_LAYER_H_
#define FULLCONNECTION_LAYER_H_

#include "Operator.hpp"

namespace mario
{
	typedef class FullConnectionLayer : public Operator
	{
	private:
		matrix m_w;
		matrix m_b;

		matrix m_dw;
		matrix m_db;
		matrix m_dx;

		matrix m_in;
		matrix m_out;

	public:
		FullConnectionLayer();
		FullConnectionLayer(const int &_lastNeuronNum, const int&_nextNeuronNum);
		~FullConnectionLayer();
	
		const matrix& getW() const;

		const matrix& getB() const;

		const matrix& forward(const matrix&_lastOut);

		const matrix& backward(const matrix &_nextDerr);

		void update(const double &_learningRate = 0.001);

	}Fc;
}

#endif	//FULLCONNECTION_LAYER_H_