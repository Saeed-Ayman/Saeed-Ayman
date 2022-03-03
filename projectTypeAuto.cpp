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
	//input all data from console, Syntax is [ object.setvalue<Type>();  ]
	template<typename dataType>
	void setValue()
	{
		delete data;
		data = new dataType;
		if (typeid(dataType).name() == typeid(string).name())
		{
			getline(cin, *(string*)data);
			type = "string";
		}
		else
		{
			cin >> *(dataType*)data;
			type = typeid(dataType).name();
		}
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
	Node categore[4] = { {"saeed ayman","name"},{3000210074705,"ID"},{20,"Age"},{"Cs","position"} };
	for (int i = 0; i < 4; i++)
	{
		cout << categore[i].name << ':' << categore[i].item << endl;
	}
	cout << "New Name : ";
	categore[0].item.setValue<string>();
	cout << categore[0].name << ':' << categore[0].item;
}
