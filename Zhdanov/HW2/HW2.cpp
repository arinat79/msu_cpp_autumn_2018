#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

class output //класс вывода
{
public:
	int result;
	bool error;
};

class calculator //класс калькулятора
{
	output out;
	vector <int> numbers;
	vector <char> operators;

public:
	calculator(char *str)
	{
		int cur_number;
		char cur_operator;
		char *point1;
		char *point2;
		point1 = str;
		this->ignore_space(point1);
		if (*point1 == '-')
		{
			++point1;
			cur_number = strtoll(point1, &point2, 10);
			if (point1 == point2 || cur_number <= 0)
			{
				out.error = true;
				throw out;
			}
			cur_number = -cur_number;
		}
		else
			cur_number = strtoll(point1, &point2, 10);
		while (point1 != point2)
		{
			numbers.push_back(cur_number);
			ignore_space(point2);
			cur_operator = *point2;
			if (cur_operator == '\0')
			{
				for (int i = 0; i < operators.size(); ++i)
					if (operators[i] == '-')
					{
						operators[i] = '+';
						numbers[i + 1] = -numbers[i + 1];
					}
				out.error = false;
				out.result = this->calculation(0, operators.size() - 1);
				throw out;
			}
			if (cur_operator != '+' && cur_operator != '-' && cur_operator != '*' && cur_operator != '/')
			{
				out.error = true;
				throw out;
			}
			++point2;
			ignore_space(point2);
			operators.push_back(cur_operator);
			point1 = point2;
			if (*point1 == '-')
			{
				++point1;
				cur_number = strtoll(point1, &point2, 10);
				if (point1 == point2 || cur_number <= 0)
				{
					out.error = true;
					throw out;
				}
				cur_number = -cur_number;
			}
			else
				cur_number = strtoll(point1, &point2, 10);
		}
		out.error = true;
		throw out;
	}

	int calculation(int left, int right)
	{
		if (left == right)
		{
			switch (operators[left])
			{
			case '+':
				return numbers[left] + numbers[left + 1];
			case '*':
				return numbers[left] * numbers[left + 1];
			case '/':
				if (numbers[left + 1] != 0)
					return numbers[left] / numbers[left + 1];
				else
				{
					out.error = true;
					throw out;
				}
			}
		}
		for (int i = left; i <= right; ++i) //сложение
		{
			if (operators[i] == '+')
			{
				int a, b;
				if (i == left)
					a = numbers[i];
				else if (i == right)
					b = numbers[i + 1];
				else
					a = calculation(left, i - 1);
					b = calculation(i + 1, right);
				return a + b;
			}
		}
		int result = numbers[left];
		for (int i = left; i <= right; ++i) //умножение/деление
		{
			switch (operators[i])
			{
			case '*':
				result = result * numbers[i + 1];
				break;
			case '/':
				if (numbers[i + 1] != 0)
					result = result / numbers[i + 1];
				else
				{
					out.error = true;
					throw out;
				}
				break;
			}
		}
		return result;
	}

	void ignore_space(char* &position) //пропуск пробелов
	{
		while (*position == ' ')
			++position;
	}
};

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "error" << endl;
		return 1;
	}
	try
	{
		calculator start(argv[1]);
	}
	catch (output &out)
	{
		if (out.error)
		{
			cout << "error" << endl;
			return 1;
		}
		else
		{
			cout << out.result << endl;
			return 0;
		}
	}
	return 0;
}