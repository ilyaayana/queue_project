#include "LQueue.h"

#pragma warning(disable : 4996)

enum Priority {
	REAR_HIGH,
	REAR_MEDIUM,
	REAR_LOW,
};

void LQueue::Erase() {
	while (Pop());
	size = 0;
}
void LQueue::Clone(const LQueue& Q) {
	//for (unsigned i=0; i<Q.size; i++)
	// Push(Q[i]);
	QItem* tmp = Q.front;
	for (unsigned i = 0; i < Q.size; i++) {
		Push(tmp->info);
		tmp = tmp->next;
	}
}
LQueue::LQueue(const LQueue& Q) {
	size = 0; Clone(Q);
}
LQueue::~LQueue() {
	Erase();
}
LQueue& LQueue::operator = (const LQueue& Q) {
	if (this != &Q) {
		Erase();
		Clone(Q);
	}
	return *this;
}
void LQueue::Push(int Ainfo) {
	QItem* tmp = new QItem(Ainfo);
	if (size > 0)
		rear->next = tmp;
	else
		front = tmp;
	rear = tmp;
	size++;
}
bool LQueue::Pop() {
	if (size == 0)
		return false;
	QItem* tmp = front;
	front = front->next;
	delete tmp;
	size--;
	if (size == 0)
		rear = NULL;
	return true;
}
int LQueue::GetFirst() const {
	if (size == 0)
		throw exception("Impossible to execute GetFirst: queue is empty");
			return front->info;
}
bool LQueue::IsEmpty() const {
	return (size == 0);
}
unsigned LQueue::GetSize() const {
	return size;
}
int& LQueue::operator [] (unsigned k)
{
	return (((QItem*)PtrByIndex(k))->info);
}
void LQueue::Browse(void ItemWork(int)) const {
	QItem* tmp = front;
	for (unsigned i = 0; i < size; i++) {
		ItemWork(tmp->info);
		tmp = tmp->next;
	}
}
void LQueue::Browse(void ItemWork(int&)) {
	QItem* tmp = front;
	for (unsigned i = 0; i < size; i++) {
		ItemWork(tmp->info);
		tmp = tmp->next;
	}
}
void* LQueue::PtrByIndex(unsigned k) const {
	if ((k < 0) || (k >= size))
		throw exception("Impossible to obtain queue item : invalid index");
			QItem * tmp = front;
	for (unsigned i = 0; i < k; i++)
		tmp = tmp->next;
	return tmp;
}
const int& LQueue::GetByIndex(unsigned k) const {
	return ((QItem*)PtrByIndex(k))->info;
}

void LQueue::SetByIndex(int AInfo,	unsigned k) {
	((QItem*)PtrByIndex(k))->info = AInfo;
}
