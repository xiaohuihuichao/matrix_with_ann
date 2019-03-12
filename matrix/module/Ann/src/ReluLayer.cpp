#include "ReluLayer.hpp"

namespace mario
{

	ReluLayer::ReluLayer(){}

	ReluLayer::ReluLayer(const int &_col)
	{
		m_in = matrixRand(1, _col, -1, 1);
		m_out = matrixRand(1, _col, -1, 1);
		m_dx = matrixRand(1, _col, -1, 1);
	}

	ReluLayer::~ReluLayer()
	{
		m_in.release();
		m_out.release();
		m_dx.release();
	}

	const matrix& ReluLayer::forward(const matrix &_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			throw "Error in ReluLayer::forward(): m_in.cols() != _lastOut.cols().";
		}

		m_in.release();
		m_out.release();

		m_in = _lastOut;
		m_out = m_in.relu();

		return m_out;
	}

	const matrix& ReluLayer::backward(const matrix &_nextDerr)
	{
		if (m_in.rows() != _nextDerr.rows())
		{
			throw "Error in ReluLayer::backward(): m_in.rows() != _nextDx.rows().";
		}

		matrix dRelu = m_in;

		for (int r = 0; r < dRelu.rows(); ++r)
		{
			double *pDx = dRelu.getRowPoint(r);
			for (int c = 0; c < dRelu.cols(); ++c)
			{
				pDx[c] = pDx[c]>0 ? 1 : 0;
			}
		}

		m_dx.release();
		m_dx = dRelu.mul(_nextDerr);

		return m_dx;
	}
}
