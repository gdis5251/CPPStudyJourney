template <class T>
class Vector
{
public:
	Vector(size_t capacity)
		:_array(new T[capacity]),
		_size(0),
		_capacity(capacity)
	{}

	~Vector();//在类里面声明，在类外面进行定义

	//顺序表的一些基本操作


private:
	T *_array;
	size_t _size;
	size_t _capacity;
};

template <class T>
Vector<T>::~Vector()
{
	if (_array)
	{
		delete[] _array;
		_array = nullptr;
	}
}