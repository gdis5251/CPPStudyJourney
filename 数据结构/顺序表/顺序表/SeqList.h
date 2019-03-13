#pragma once
#include <iostream>
#include <stdio.h>

typedef int SLDataType;

constexpr auto CAPSIZE = 100;

class SeqList
{
public:
	void SeqListInit(size_t capicity);
	void SeqListDestory();
	void SeqListPushBack(SLDataType val);
	void SeqListPopBack();
	void SeqListPushFront(SLDataType val);
	void SeqListPopFront();
	int SeqListFind(SLDataType val);
	void SeqListInsert(size_t pos, SLDataType val);
	void SeqListErase(size_t pos);
	void SeqListRemove(SLDataType val);
	void SeqListModify(size_t pos, SLDataType val);
	void SeqListPrint();
	void SeqListBubbleSort();
	int SeqListBinaryFind(SLDataType val);
	void SeqListRemoveAll(SLDataType val);
	
private:
	void CheckCapicity();
	SLDataType *_array;
	size_t _size;
	size_t _capicity;
};
