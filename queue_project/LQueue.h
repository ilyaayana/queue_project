#pragma once

#include <iostream>
#include <utility>
#include <exception>
using namespace std;

enum  Priority {
	HIGH,
	MEDIUM,
	LOW,
};

class LQueue
{
private:
	struct QItem {

		int info;
		Priority priority;
		QItem* next;
		QItem(int Ainfo,Priority Apriority) : info(Ainfo), priority(Apriority), next(NULL)  {};
	};
	QItem* front,*rear_high,*rear_medium, * rear_low;
	unsigned size;
	void Erase();
	void Clone(const LQueue&);
	void PushHigh(int Ainfo);
	void PushMedium(int Ainfo);
	void PushLow(int Ainfo);
	void Move(LQueue&);

public:
	LQueue() : front(NULL), rear_high(NULL), rear_medium(NULL), rear_low(NULL), size(0) {};
	LQueue(const LQueue&);
	LQueue(LQueue&&) noexcept;
	~LQueue();
	LQueue& operator = (const LQueue&);
	LQueue& operator=(LQueue&&) noexcept;
	void Push(int Ainfo, Priority = LOW);
	bool Pop();
	int GetFirstValue() const;
	Priority GetFirstPriority() const;
	bool IsEmpty() const;
	unsigned GetSize() const;
	unsigned Count(Priority) const;
	int& operator [] (unsigned);
	void Browse(void ItemWork(int)) const;
	void Browse(void ItemWork(int&));
	void* PtrByIndex(unsigned) const;
	const int& GetByIndex(unsigned ) const;
	void SetByIndex(int, unsigned);
};

