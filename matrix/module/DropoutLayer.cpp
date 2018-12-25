#include "DropoutLayer.hpp"

namespace mario
{
	DropoutLayer::DropoutLayer(const int &_lastNeuronNum, const double &_p)
	{
		m_p = _p;

		m_in = matrix(1, _lastNeuronNum, 0);
		m_mul = matrix(1, _lastNeuronNum, 0);
		m_out = matrix(1, _lastNeuronNum, 0);

		m_dx = matrix(1, _lastNeuronNum, 0);
	}

	const matrix& DropoutLayer::forward(const matrix &_lastOut)
	{
		if (_lastOut.cols() != m_in.cols())
		{
			cerr << "Error in DropoutLayer::forward(): _lastOut.cols() != m_in.cols().\n";
			return matrix();
		}

		m_in.release();
		m_in = _lastOut;

#if 1==TRAIN

		matrix deleteMul(1, m_in.cols(), 0);

		for (int c = 0; c < deleteMul.cols(); ++c)
		{
			if (isDelete())
			{
				deleteMul.set(0, c, 0);
			}
			else
			{
				deleteMul.set(0, c, 1);
			}
		}

#endif // 1==TRAIN
#if 0==TRAIN

		matrix deleteMul(1, m_in.cols(), 1);

#endif // 0==TRAIN

		

		m_mul.release();
		m_mul = copyRow(deleteMul, _lastOut.rows());

		m_out.release();
		m_out = m_mul.mul(_lastOut);

		return m_out;
	}

	const matrix& DropoutLayer::backward(const matrix &_nextDerr)
	{
		if (m_dx.cols() != _nextDerr.cols())
		{
			cerr << "Error in DropoutLayer::backward(): m_dx.cols() != _nextDerr.cols().\n";
			return Matrix();
		}

		m_dx.release();
		m_dx = m_mul.mul(_nextDerr);

		return m_dx;
	}

	bool DropoutLayer::isDelete()
	{
		double p = rand() / double(RAND_MAX);
		if (p < m_p)
		{
			return true;
		}

		return false;
	}

}