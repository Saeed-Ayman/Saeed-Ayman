#include <iostream>
#include <string>

using namespace std;

class Type {
	
private:
	void* data;
	string type;
public:
	Type() :data(NULL), type("") {}
	template<typename dataType>
	Type(dataType value) 
	{
		data = new dataType(value);
		type = typeid(dataType).name();
	}
	template<typename dataType>
	void getValue()
	{
		delete data;
		data = new dataType;
		cout << type;
		cin >> *(dataType*)data;
	}
	void getValue_s()
	{
		delete data;
		data = new string;
		type = "string";
		getline(cin, *(string*)data);
	}
	friend ostream& operator<<(ostream& stream, const Type& value)
	{
		if (value.type == "bool")
		{
			stream << *(bool*)value.data;
		}
		else if (value.type == "int")
		{
			stream << *(int*)value.data;
		}
		else if (value.type == "float")
		{
			stream << *(float*)value.data;
		}
		else if (value.type == "double")
		{
			stream << *(double*)value.data;
		}
		else if (value.type == "char")
		{
			stream << *(char*)value.data;
		}
		else if (value.type == "char const *")
		{
			stream << *(char**)value.data;
		}
		else if (value.type == "string")
		{
			stream << (*(string*)value.data);
		}
		else if (value.type == "long")
		{
			stream << *(long*)value.data;
		}
		else if (value.type == "long long" || value.type == "__int64")
		{
			stream << *(long long*)value.data;
		}
		else if (value.type == "long double")
		{
			stream << *(long double*)value.data;
		}
		else
		{
			cout << "somethin wrong. \n";
			stream << -1;
		}
		return stream;
	}
};

struct Node
{
	Type item;
	string name;
};

int main()
{
	Node categore[4] = { {"saeed ayman","name"},{3020210074785,"ID"},{20,"Age"},{"Cs","position"} };
	for (int i = 0; i < 4; i++)
	{
		cout << categore[i].name << ':' << categore[i].item << endl;
	}
}
