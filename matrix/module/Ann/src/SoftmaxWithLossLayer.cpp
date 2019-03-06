#include "SoftmaxWithLossLayer.hpp"

namespace mario
{
	SoftmaxWithLossLayer::SoftmaxWithLossLayer(){}

	SoftmaxWithLossLayer::SoftmaxWithLossLayer(const int &_col)
	{
		m_in = matrixRand(1, _col, -1, 1);
		m_out = matrixRand(1, _col, -1, 1);
		m_y = matrixRand(1, _col, -1, 1);
		m_dx = matrixRand(1, _col, -1, 1);

		m_loss = -1;
	}

	SoftmaxWithLossLayer::~SoftmaxWithLossLayer()
	{
		m_in.release();
		m_out.release();
		m_y.release();
		m_dx.release();
	}

	const matrix& SoftmaxWithLossLayer::forward(const matrix &_lastOut)
	{
		if (m_in.cols() != _lastOut.cols())
		{
			throw "Error in MeanSquareErrorLayer::forward(): m_in.cols() != _lastOut.cols().";
		}

		m_in.release();
		m_out.release();

		m_in = _lastOut;
		m_out = m_in.exp();

		matrix sum = m_out.sumByRow();
		for (int i = 0; i < m_out.rows(); ++i)
		{
			const double const sumI = sum.getRowPoint(i)[0];
			double *pData = m_out.getRowPoint(i);
                        for (int j = 0; j < m_out.cols(); ++j)
                        {
                             pData[j] /= sumI;
                        }
		}

		return m_out;
	}

	const matrix& SoftmaxWithLossLayer::backward(const matrix &_y)
	{
		if (m_out.rows() != _y.rows() || m_out.cols() != _y.cols())
		{
			throw "Error in SoftmaxWithLossLayer::calLoss(): m_in.rows() != m_y.rows() || m_in.cols() != m_y.cols().";
		}
		if (m_in.rows() != _y.rows())
		{
			throw "Error in SoftmaxWithLossLayer::backward(): m_in.rows() != _nextDx.rows().";
		}

		m_dx.release();

		setLabel(_y);
		calLoss();

		m_dx = m_out - m_y;

		return m_dx;
	}

	double SoftmaxWithLossLayer::getLoss() const
	{
		return m_loss;
	}

	void SoftmaxWithLossLayer::setLabel(const matrix &_y)
	{
		if (m_out.cols() != m_y.cols())
		{
			throw "Error in MeanSquareErrorLayer::setLabel(): m_out.cols() != m_y.cols().";
		}

		m_y.release();
		m_y = _y;
	}

	double SoftmaxWithLossLayer::calLoss()
	{
		matrix logMat = (m_out + 0.00001).log2();
		matrix yLogOut = m_y.mul(logMat)*-1;

		matrix crossEntroy = yLogOut.sumByRow();
		matrix ones = matrix(crossEntroy.rows(), crossEntroy.cols(), 1);
		double lossSum = ones.dot(crossEntroy);
		m_loss = lossSum / ones.rows();

		return m_loss;
	}
}
