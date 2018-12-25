#include "FullConnectionLayer.hpp"

namespace mario
{
	FullConnectionLayer::FullConnectionLayer(){}

	FullConnectionLayer::FullConnectionLayer(const int &_lastNeuronNum, const int&_nextNeuronNum)
	{
		m_w = matrixRand(_lastNeuronNum, _nextNeuronNum, -1, 1);
		m_b = matrixRand(1, _nextNeuronNum, -1, 1);

		m_dw = matrixRand(_lastNeuronNum, _nextNeuronNum, -1, 1);
		m_db = matrixRand(1, _nextNeuronNum, -1, 1);
		m_dx = matrixRand(1, _lastNeuronNum, -1, 1);

		m_in = matrixRand(1, _lastNeuronNum, -1, 1);
		m_out = matrixRand(1, _nextNeuronNum, -1, 1);
	}

	FullConnectionLayer::~FullConnectionLayer()
	{
		m_w.release();
		m_b.release();

		m_dw.release();
		m_db.release();
		m_dx.release();

		m_in.release();
		m_out.release();
	}

	const matrix& FullConnectionLayer::getW() const
	{
		return m_w;
	}

	const matrix& FullConnectionLayer::getB() const
	{
		return m_b;
	}

	const matrix& FullConnectionLayer::forward(const matrix&_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			cout << "Error in ullConnectionLayer::forward(): m_in.cols() != _lastOut.cols().\n";
			return matrix();
		}

		m_in.release();
		m_out.release();
		
		m_in = _lastOut;
		m_out = m_in*m_w + m_b;

		return m_out;
	}

	const matrix& FullConnectionLayer::backward(const matrix &_nextDerr)
	{
		if (m_in.rows() != _nextDerr.rows())
		{
			cerr << "Error in FullConnectionLayer::backward(): m_in.rows() != _nextDx.rows().\n";
			return matrix();
		}

		m_dw.release();
		m_db.release();
		m_dx.release();

		m_dw = m_in.T()*_nextDerr / m_in.rows();
		m_db = _nextDerr.meanByCol();
		m_dx = _nextDerr*m_w.T();

		return m_dx;
	}

	void FullConnectionLayer::update(const double &_learningRate)
	{
		m_w -= _learningRate*m_dw;
		m_b -= _learningRate*m_db;
	}
}