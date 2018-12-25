#include "SigmoidLayer.hpp"

namespace mario
{

	SigmoidLayer::SigmoidLayer(){}
	
	SigmoidLayer::SigmoidLayer(const int &_col)
	{
		m_in = matrixRand(1, _col, -1, 1);
		m_out = matrixRand(1, _col, -1, 1);
		m_dx = matrixRand(1, _col, -1, 1);
	}
	
	SigmoidLayer::~SigmoidLayer()
	{
		m_in.release();
		m_out.release();
		m_dx.release();
	}

	const matrix& SigmoidLayer::forward(const matrix &_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			cerr << "Error in SigmoidLayer::forward(): m_in.cols() != _lastOut.cols().\n";
			return Matrix();
		}

		m_in.release();
		m_out.release();

		m_in = _lastOut;
		m_out = m_in.sigmoid();

		return m_out;
	}

	const matrix& SigmoidLayer::backward(const matrix &_nextDerr)
	{
		if (m_in.rows() != _nextDerr.rows())
		{
			cerr << "Error in MeanSquareErrorLayer::backward(): m_in.rows() != _nextDx.rows().\n";
			return matrix();
		}

		m_dx.release();

		m_dx = m_out.mul(1 - m_out).mul(_nextDerr);

		return m_dx;
	}
}