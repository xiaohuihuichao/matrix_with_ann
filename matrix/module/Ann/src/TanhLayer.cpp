#include "TanhLayer.hpp"

namespace mario
{
	TanhLayer::TanhLayer(){}

	TanhLayer::TanhLayer(const int &_col)
	{
		m_in = matrixRand(1, _col, -1, 1);
		m_out = matrixRand(1, _col, -1, 1);
		m_dx = matrixRand(1, _col, -1, 1);
	}

	TanhLayer::~TanhLayer()
	{
		m_in.release();
		m_out.release();
		m_dx.release();
	}

	const matrix& TanhLayer::forward(const matrix &_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			throw "Error in TanhLayer::forward(): m_in.cols() != _lastOut.cols().";
		}

		m_in.release();
		m_out.release();

		m_in = _lastOut;
		m_out = m_in.tanh();

		return m_out;
	}

	const matrix& TanhLayer::backward(const matrix &_nextDerr)
	{
		if (m_in.rows() != _nextDerr.rows())
		{
			throw "Error in TanhLayer::backward(): m_in.rows() != _nextDx.rows().";
		}

		m_dx.release();

		m_dx = (1 - m_out.mul(m_out)).mul(_nextDerr);

		return m_dx;
	}
}
