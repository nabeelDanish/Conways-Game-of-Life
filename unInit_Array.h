#ifndef UNINIT_ARRAY_H
#define UNINIT_ARRAY_H

//The Struct that holds the positon of every cell in X Y, and also stores the liveNeihbourCount of 
//individual cell

struct position
{
	int x;
	int y;
	int liveNeighbourCount;

	//Constructors
	position()
	{
		x = 0;
		y = 0;
		liveNeighbourCount = 0;
	}
	position(int x, int y)
	{
		this->x = x;
		this->y = y;
		liveNeighbourCount = 0;
	}

	//Overloading the Equality Operator
	bool operator==(const position& other) const
	{
		return ((x == other.x) && y == other.y);
	}
};

//The List class, that is used to store both the Living cells and the Dead Cells

template <class Type>
class unInit_array
{
public:
	Type *list;
	int count;
	int maxSize;

public:
	//Constructors
	unInit_array();
	unInit_array(int);
	unInit_array(const unInit_array<Type>&);

	//Main Fucntions
	void insertion(const Type&);
	void deletion(const Type&);

	//Resize Function
	void resize(int);

	//Overloading the operator for easy access of element
	Type& operator[](int);

	//Destructor
	~unInit_array();
};

//************************************************************************************************
//---------------------------------------------[CLASS IMPLEMENTATION]-----------------------------
//************************************************************************************************


template <class Type>
unInit_array<Type>::unInit_array()
{
	list = nullptr;
	count = 0;
	maxSize = 0;
}
template <class Type>
unInit_array<Type>::unInit_array(int s)
{
	count = 0;
	maxSize = 2 * s;

	//Allocating Space for double the required size, as Cellular Growth is 
	//an important step
	list = new Type[maxSize];

}
template <class Type>
unInit_array<Type>::unInit_array(const unInit_array<Type>& otherList)
{
	delete[] list;
	count = otherList.count;
	maxSize = otherList.maxSize;

	list = new Type[maxSize];
	for (int i = 0; i < count; i++)
	{
		list[i] = otherList.list[i];
	}
}
//Resize Function
template <class Type>
void unInit_array<Type>::resize(int s)
{
	delete[] list;
	maxSize = s * 2;
	count = 0;
	list = new Type[maxSize];
}
//Function to Insert
template <class Type>
void unInit_array<Type>::insertion(const Type& x)
{

	//If the List has exceeded the maxSize, than new memory space has to be allocated
	if (count == maxSize)
	{
		maxSize *= 2;
		Type *temp = new Type[maxSize];
		for (int i = 0; i < count; ++i)
		{
			temp[i] = list[i];
		}
		delete[]list;
		list = temp;
	}
	list[count] = x;
	++count;
}

template <class Type>
void unInit_array<Type>::deletion(const Type& x)
{
	//Deletion from the array is done by making a new temporary Array and
	//Storing all the values from the previous Array except the Deleting Element
	Type *temp_list = new Type[maxSize];
	for (int i = 0, j = 0; i < count; i++, ++j)
	{
		if (list[i] == x)
		{
			--j;
		}
		else
		{
			temp_list[j] = list[i];
		}
	}
	delete[] list;
	--count;
	list = temp_list;
}

template <class Type>
Type& unInit_array<Type>::operator[](int index)
{
	return list[index];
}

template <class Type>
unInit_array<Type>::~unInit_array()
{
	delete[] list;
}
#endif // !UNINIT_ARRAY_H
