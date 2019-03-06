#include "Graph.hpp"

namespace mario
{
	Graph::Graph() : m_batchSize(-1), m_learningRate(0.1), m_lrDecay(-1), m_lrDecayIte(-1), m_iterator(1){}
	
	Graph::Graph(const double &_lr, const double &_lrDecey, const int &_lrDecayIte)
		: m_learningRate(_lr), m_lrDecay(_lrDecey), m_lrDecayIte(_lrDecayIte), m_batchSize(-1), m_iterator(1)
	{}

	Graph::~Graph()
	{
		clearStruct();

		m_trainX.release();
		m_trainY.release();

		m_batchX.release();
		m_batchY.release();

		m_testX.release();
		m_testY.release();

		m_out.release();

		m_iterator = 0;
	}

	void Graph::setLearningRate(const double &_lr)
	{
		m_learningRate = _lr;
	}

	void Graph::setLrDecay(const double &_lrDecay, const int &_lrDecayIte)
	{
		m_lrDecay = _lrDecay;
		m_lrDecayIte = _lrDecayIte;
	}

	void Graph::setBatchSize(const int &_batchSize)
	{
		m_batchSize = _batchSize;
	}

	void Graph::loadTrainData(const matrix &_x, const matrix &_y)
	{
		if (_x.rows() != _y.rows())
		{
			throw "Error in Graph::loadData(): _x.rows() != _y.rows().";
		}

		m_trainX.release();
		m_trainY.release();

		m_trainX = _x;
		m_trainY = _y;
	}

	void Graph::feedXY(const int &_startIndex, const int &_num)
	{
		if (_startIndex + _num > m_trainX.rows())
		{
			throw "Error in Graph::feedXY(): _startIndex + _num > m_X.rows().";
		}

		m_batchX.release();
		m_batchY.release();

		m_batchX = m_trainX.block(_startIndex, 0, _num, m_trainX.cols());
		m_batchY = m_trainY.block(_startIndex, 0, _num, m_trainY.cols());
	}

	void Graph::clearStruct()
	{
		while (m_nodes.size() > 0)
		{
			delete m_nodes.back();
			m_nodes.pop_back();
		}

		m_iterator = 0;
	}

	void Graph::loadTestData(const matrix &_x, const matrix &_y)
	{
		if (_x.rows() != _y.rows())
		{
			throw "Error in Graph::loadData(): _x.rows() != _y.rows().";
		}

		m_testX.release();
		m_testY.release();

		m_testX = _x;
		m_testY = _y;
	}
	void Graph::addFullConnection(const int &_lastNeuronNum, const int&_nextNeuronNum)
	{
		Fc *fc = new Fc(_lastNeuronNum, _nextNeuronNum);
		m_nodes.emplace_back(fc);
	}

	void Graph::addSigmoid(const int &_col)
	{
		Sigmoid *sig = new Sigmoid(_col);
		m_nodes.emplace_back(sig);
	}

	void Graph::addTanh(const int &_col)
	{
		Tanh *tanh = new Tanh(_col);
		m_nodes.emplace_back(tanh);
	}

	void Graph::addRelu(const int &_col)
	{
		Relu *relu = new Relu(_col);
		m_nodes.emplace_back(relu);
	}

	void Graph::addMse(const int &_col)
	{
		Mse *mse = new Mse(_col);
		m_nodes.emplace_back(mse);
	}

	void Graph::addSoftmax(const int &_col)
	{
		Softmax *softmax = new Softmax(_col);
		m_nodes.emplace_back(softmax);
	}

	void Graph::init()
	{
		if (-1 == m_batchSize)
		{
			m_batchSize = m_trainX.rows();
		}

		if (-1 == m_lrDecayIte)
		{
			m_lrDecayIte = INT_MAX;
		}
		if (isEqual(m_lrDecay, -1))
		{
			m_lrDecay = 1;
		}

		m_iterator = 1;
	}

	void Graph::train()
	{
		for (int i = 0; i*m_batchSize < m_trainX.rows(); ++i)
		{
			int startIndex = i*m_batchSize;
			int num = startIndex + m_batchSize <= m_trainX.rows()
				? m_batchSize : m_trainX.rows() - startIndex;
			feedXY(startIndex, num);
			
			forward(m_batchX);
			backward(m_batchY);
		}

		++m_iterator;
		if (0 == m_iterator%m_lrDecayIte)
		{
			m_learningRate *= m_lrDecay;
		}
	}

	const matrix& Graph::predict()
	{
		forward(m_testX);

		Operator *lossNode = m_nodes.back();
		lossNode->backward(m_testY);
		m_loss = lossNode->getLoss();

		return m_out;
	}

	void Graph::forward(const matrix &_x)
	{
		if (0 == m_nodes.size())
		{
			throw "Error in Graph::forward(): 0 == m_nodes.size().";
		}

		Operator *node = m_nodes[0];
		matrix lastOut = node->forward(_x);
		for (int i = 1; i < m_nodes.size(); ++i)
		{
			node = m_nodes[i];
			matrix out = node->forward(lastOut);

			lastOut.release();
			lastOut = out;
		}

		m_out.release();
		m_out = lastOut;
	}

	void Graph::backward(const matrix &_y)
	{
		if (0 == m_nodes.size())
		{
			throw "Error in Graph::backward(): 0 == m_nodes.size().";
		}

		Operator *node = m_nodes.back();
		matrix nextDerr = node->backward(_y);
		m_loss = node->getLoss();
		for (int i = m_nodes.size() - 2; i >= 0;--i)
		{
			node = m_nodes[i];
			matrix derr = node->backward(nextDerr);
			node->update(m_learningRate);

			nextDerr.release();
			nextDerr = derr;
		}
	}

	const double& Graph::getLoss() const
	{
		return m_loss;
	}

	const matrix& Graph::getOut() const
	{
		return m_out;
	}

}
