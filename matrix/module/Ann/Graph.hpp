#ifndef GRAPH_H_
#define GRAPH_H_

#include "config.hpp"
#include <vector>

using namespace std;

namespace mario
{
#define INT_MAX 0x7fffffff

	class Graph
	{
	private:
		vector<Operator*> m_nodes;

		matrix m_trainX;
		matrix m_trainY;

		int m_batchSize;
		matrix m_batchX;
		matrix m_batchY;

		matrix m_testX;
		matrix m_testY;

		double m_learningRate;
		double m_lrDecay;
		int m_lrDecayIte;
		int m_iterator;

		double m_loss;
		matrix m_out;

	public:
		Graph();
		Graph(const double &_lr, const double &_lrDecey = -1, const int &_lrDecayIte = -1);
		~Graph();

		void setLearningRate(const double &_lr);
		void setLrDecay(const double &_lrDecay, const int &_lrDecayIte);
		void setBatchSize(const int &_batchSize);

		void loadTrainData(const matrix &_x, const matrix &_y);
		void feedXY(const int &_startIndex, const int &_num);

		void loadTestData(const matrix &_x, const matrix &_y);
		
		void clearStruct();

		void addFullConnection(const int &_lastNeuronNum, const int&_nextNeuronNum);
		void addSigmoid(const int &_col);
		void addTanh(const int &_col);
		void addRelu(const int &_col);
		void addMse(const int &_col);
		void addSoftmax(const int &_col);
		
		void init();
		void train();
		const matrix& predict();

		const double& getLoss() const;
		const matrix& getOut() const;

	protected:
		void forward(const matrix &_x);
		void backward(const matrix &_y);

	};
}

#endif // !GRAPH_H_
