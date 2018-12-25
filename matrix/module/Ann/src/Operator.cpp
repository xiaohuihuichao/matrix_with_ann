#include "Operator.hpp"
namespace mario
{
	Operator::Operator()
	{
		cout << "Operator::Operator().\n";
	}

	const matrix& Operator::getW() const
	{
		cout << "Operator::getW();\n";
		return matrix();
	}

	const matrix& Operator::getB() const
	{
		cout << "Operator::getB().\n";
		return matrix();
	}

	void Operator::update(const double &_learningRate)
	{
		//cout << "Operator::update();\n";
	}

	double Operator::getLoss() const
	{
		cout << "Operator::getLoss().\n";
		return -1;
	}

	void Operator::setLabel(const matrix&_x)
	{
		cout << "Operator::setLabel().\n";
	}
	
	double Operator::calcLoss()
	{
		cout << "Operator::calcLoss().\n";
		return -1;
	}
}