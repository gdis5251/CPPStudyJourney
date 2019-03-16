#include  "SeqList.h"

void SeqList::SeqListInit(size_t capicity)
{
	_array = new SLDataType[CAPSIZE];
	_size = 0;
	_capicity = CAPSIZE;
}




void SeqList::SeqListDestory()
{
	delete[] _array;
	_size = 0;
	_capicity = 0;
}




void SeqList::CheckCapicity()
{
	if (_size == _capicity)
	{
		SLDataType *p = nullptr;
		p = (int *)realloc(p, 2 * _capicity);
		if (!p)
		{
			std::cout << "realloc ERROR!" << std::endl;
			exit(EXIT_FAILURE);
		}

		_array = p;
		_capicity *= 2;

		p = NULL;
	}
}




void SeqList::SeqListPushBack(SLDataType val)
{
	CheckCapicity();

	_array[_size] = val;
	_size++;
}




void SeqList::SeqListPopBack()
{
	_size--;
}




void SeqList::SeqListPushFront(SLDataType val)
{
	CheckCapicity();

	//所有数据往后搬一个
	for (int i = _size; i > 0; i--)
	{
		_array[i] = _array[i - 1];
	}

	_array[0] = val;
	_size++;
}




void SeqList::SeqListPopFront()
{
	for (int i = 0; i < _size; i++)
	{
		_array[i] = _array[i + 1];
	}

	_size--;
}