#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Type {
private:
	void* data;
	string type;
	//----------
	template<typename dataType>
	string toString(dataType value)
	{
		ostringstream x;
		x << value;
		return x.str();
	}
public:
	Type() :data(new string("No value")), type("No Type"){}
	template<typename dataType>
	Type(dataType value)
	{
		data = new dataType(value);
		type = typeid(dataType).name();
	}
	void typeof()
	{
		cout << type;
	}
	friend istream& operator>>(istream& stream, Type& value)
	{
		delete value.data;
		char INPUT[50];
		stream >> ws;
		stream.get(INPUT, 50);
		if (INPUT == "true")
		{
			value.data = new bool(1);
			value.type = "bool";
		}
		else if (INPUT == "false")
		{
			value.data = new bool(0);
			value.type = "bool";
		}
		else if ((int)strlen(INPUT) == 1)
		{
			if (INPUT[0] >= '0' && INPUT[0] <= '9')
			{
				value.data = new int(int(INPUT[0] - '0'));
				value.type = "int";
			}
			else
			{
				value.data = new char(INPUT[0]);
				value.type = "char";
			}
		}
		else
		{
			int test = 0;
			for (int i = 0; i < (int)strlen(INPUT); i++)
			{
				if (INPUT[i] == '.')
				{
					test++;
				}
				else if (INPUT[i] > '9' || INPUT[i] < '0')
				{
					test += 10;
					break;
				}
			}
			if (test >= 2)
			{
				value.data = new string(INPUT);
				value.type = "string";
			}
			else if (test == 1)
			{
				value.data = new double(atof(INPUT));
				value.type = "double";
			}
			else if (atoll(INPUT) > 2147483647 || atoll(INPUT) < -2147483648)
			{
				value.data = new long long(atoll(INPUT));
				value.type = "long long";
			}
			else
			{
				value.data = new int(atoi(INPUT));
				value.type = "int";
			}
		}
		return stream;
	}
	template<typename dataType>
	Type operator=(dataType value)
	{
		delete data;
		data = new dataType(value);
		type = typeid(dataType).name();
		return this;
	}
	Type operator+(Type value)
	{
		Type sum;
		if (value.type == "string" || type == "string" ||
			value.type == typeid(string).name() || type == typeid(string).name() ||
			value.type == "char" || type == "char" ||
			value.type == "char const *" || type == "char const *")
		{
			if (value.type == typeid(string).name() || type == typeid(string).name())
				if (value.type == type)
					sum.data = new string(*(string*)data + *(string*)value.data);
				else if (value.type == typeid(string).name())
					sum.data = new string(toString(*this) + *(string*)value.data);
				else
					sum.data = new string(*(string*)data + toString(value));
			else
				sum.data = new string(toString(*this) + toString(value));
			sum.type = "string";
		}
		else if (type == value.type)
		{
			if (type == "bool")
				sum.data = new bool(*(bool*)value.data + *(bool*)data);
			else if (type == "int")
				sum.data = new int(*(int*)value.data + *(int*)data);
			else if (type == "double")
				sum.data = new double(*(double*)value.data + *(double*)data);
			else if (type == "__int64")
				sum.data = new long long(*(long long*)value.data + *(long long*)data);
			else if (type == "long double")
				sum.data = new long double(*(long double*)value.data + *(long double*)data);
			sum.type = type;
		}
		else
		{
			if (type == "double" && value.type == "int")
			{
				sum.data = new double((double)*(int*)value.data + *(double*)data);
				sum.type = type;
			}
			else if (type == "int" && value.type == "double")
			{
				sum.data = new double(*(double*)value.data + (double)*(int*)data);
				sum.type = value.type;
			}
			else if (type == "__int64" && value.type == "int")
			{
				sum.data = new long long(*(int*)value.data + *(long long*)data);
				sum.type = type;
			}
			else if (type == "int" && value.type == "__int64")
			{
				sum.data = new long long(*(long long*)value.data + *(int*)data);
				sum.type = value.type;
			}
			else if (type == "long double" && value.type == "int")
			{
				sum.data = new long double((double)*(int*)value.data + *(long double*)data);
				sum.type = type;
			}
			else if (type == "int" && value.type == "long double")
			{
				sum.data = new long double(*(long double*)value.data + (double)*(int*)data);
				sum.type = value.type;
			}
			else if (type == "__int64" && value.type == "double")
			{
				sum.data = new double(*(double*)value.data + (double)*(long long*)data);
				sum.type = value.type;
			}
			else if (type == "double" && value.type == "__int64")
			{
				sum.data = 
					new double((double)*(long long*)value.data + *(double*)data);
				sum.type = "double";
			}
			else if (type == "long double")
				sum.data = new long double(*(long double*)value.data + *(long double*)data);
			else if (type == "bool")
				sum.data = new bool(*(bool*)value.data + *(bool*)data);
			else if (type == "int")
				sum.data = new int(*(int*)value.data + *(int*)data);
			else if (type == "double")
				sum.data = new double(*(double*)value.data + *(double*)data);
			else if (type == "__int64")
				sum.data = new long long(*(long long*)value.data + *(long long*)data);
			else if (type == "long double")
				sum.data = new long double(*(long double*)value.data + *(long double*)data);
		}
		return sum;
	}

	friend ostream& operator<<(ostream& stream, const Type& value)
	{
		if (value.type == "bool")
			stream << *(bool*)value.data;
		else if (value.type == "int")
			stream << *(int*)value.data;
		else if (value.type == "double")
			stream << *(double*)value.data;
		else if (value.type == "char")
			stream << *(char*)value.data;
		else if (value.type == "char const *")
			stream << *(char**)value.data;
		else if (value.type == "string")
			stream << (*(string*)value.data);
		else if (value.type == "__int64")
			stream << *(long long*)value.data;
		else if (value.type == "long double")
			stream << *(long double*)value.data;
		else
			cout << *(string*)value.data;
		return stream;
	}
};
// - * / => 
struct Node
{
	string name;
	Type item;
};

int main()
{
	
}
