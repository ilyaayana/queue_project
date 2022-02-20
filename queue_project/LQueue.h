#pragma once

#include <iostream>
#include <string>
using namespace std;

enum Priority;

class LQueue
{
private:
	struct QItem {

		int info;
		QItem* next;
		QItem(int Ainfo) : info(Ainfo), next(NULL) {};
	};
	QItem* front, * rear;
	unsigned size;
	void Erase();
	void Clone(const LQueue&);
public:
	LQueue() : front(NULL), rear(NULL), size(0) {};
	LQueue(const LQueue&);
	~LQueue();
	LQueue& operator = (const LQueue&);
	void Push(int Ainfo);
	bool Pop();
	int GetFirst() const;
	bool IsEmpty() const;
	unsigned GetSize() const;
	int& operator [] (unsigned);
	void Browse(void ItemWork(int)) const;
	void Browse(void ItemWork(int&));
	void* PtrByIndex(unsigned) const;
	const int& GetByIndex(unsigned ) const;
	void SetByIndex(int, unsigned);
};

