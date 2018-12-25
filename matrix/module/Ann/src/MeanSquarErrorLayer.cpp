#include "MeanSquareErrorLayer.hpp"

namespace mario
{
	MeanSquareErrorLayer::MeanSquareErrorLayer(){}

	MeanSquareErrorLayer::MeanSquareErrorLayer(const int &_col)
	{
		m_in = matrixRand(1, _col, -1, 1);
		m_out = matrixRand(1, _col, -1, 1);
		m_y = matrixRand(1, _col, -1, 1);
		m_dx = matrixRand(1, _col, -1, 1);

		m_loss = -1;
	}

	MeanSquareErrorLayer::~MeanSquareErrorLayer()
	{
		m_in.release();
		m_out.release();
		m_y.release();
		m_dx.release();
	}

	double MeanSquareErrorLayer::getLoss() const
	{
		return m_loss;
	}

	const matrix& MeanSquareErrorLayer::forward(const matrix &_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			cout << "Error in MeanSquareErrorLayer::forward(): m_in.cols() != _lastOut.cols().\n";
			return matrix();
		}

		m_in.release();
		m_out.release();

		m_in = _lastOut;
		m_out = m_in;

		return m_out;
	}

	const matrix& MeanSquareErrorLayer::backward(const matrix &_y)
	{
		if (m_out.rows() != _y.rows() || m_out.cols() != _y.cols())
		{
			cout << "Error in MeanSquareErrorLayer::calLoss(): m_in.rows() != m_y.rows() || m_in.cols() != m_y.cols().\n";
			return Matrix();
		}
		if (m_in.rows() != _y.rows())
		{
			cerr << "Error in MeanSquareErrorLayer::backward(): m_in.rows() != _nextDx.rows().\n";
			return matrix();
		}

		m_dx.release();
		setLabel(_y);
		m_dx = m_out - m_y;

		calLoss();

		return m_dx;
	}

	void MeanSquareErrorLayer::setLabel(const matrix &_y)
	{
		if (_y.cols() != m_y.cols())
		{
			cout << "Error in MeanSquareErrorLayer::setLabel(): m_out.cols() != m_y.cols().\n";
		}

		m_y.release();
		m_y = _y;
	}

	double MeanSquareErrorLayer::calLoss()
	{
		m_loss = m_dx.dot(m_dx) / m_dx.rows() / 2;

		return m_loss;
	}
}