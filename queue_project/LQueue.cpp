#include "LQueue.h"

#pragma warning(disable : 4996)


void LQueue::Erase() {
	while (Pop());
	size = 0;
}
void LQueue::Clone(const LQueue& Q) {
	QItem* tmp = Q.front;
	for (unsigned i = 0; i < Q.size; i++) {
		Push(tmp->info,tmp->priority);
		tmp = tmp->next;
	}
}
LQueue::LQueue(const LQueue& Q) {
	size = 0; 
	Clone(Q);
}
LQueue::LQueue(LQueue&& Q) noexcept {

	Move(Q);

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
LQueue& LQueue::operator=(LQueue&& Q) noexcept
{
	if (&Q == this)
		return *this;
	Erase();
	Move(Q);

	return *this;
}
void LQueue::Move(LQueue& Q) {
	size = Q.size;
	front = Q.front;
	rear_high = Q.rear_high;
	rear_medium = Q.rear_medium;
	rear_low = Q.rear_low;
	Q.front = nullptr;
	Q.rear_high = nullptr;
	Q.rear_medium = nullptr;
	Q.rear_low = nullptr;
	Q.size = 0;
};
void LQueue::Push(int Ainfo, Priority priority) {
	switch (priority)
	{
	case HIGH:
		PushHigh(Ainfo);
		break;
	case MEDIUM:
		PushMedium(Ainfo);
		break;
	case LOW:
		PushLow(Ainfo);
		break;
	}
	size++;
}
void LQueue::PushHigh(int Ainfo) {
	QItem* tmp = new QItem(Ainfo, HIGH);
	if (size == 0) 
		front = tmp;
	else if (rear_high == NULL) {
		tmp->next = front;
		front = tmp;
	}
	else {
		tmp->next = rear_high->next;
		rear_high->next = tmp;
	}
	rear_high = tmp;
}
void LQueue::PushMedium(int Ainfo) {
	QItem* tmp = new QItem(Ainfo, MEDIUM);
	if (size == 0)
		front = tmp;
	else if(rear_medium == NULL){
		if (rear_high != NULL) {
			tmp->next = rear_high->next;
			rear_high->next = tmp;
		}
		else {
			tmp->next = rear_low;
			front = tmp;
		}
	}
	else {
		tmp->next = rear_medium->next;
		rear_medium->next = tmp;
	}
	rear_medium = tmp;
}
void LQueue::PushLow(int Ainfo) {
	QItem* tmp = new QItem(Ainfo, LOW);
	if (size == 0)
		front = tmp;
	else if (rear_low == NULL) 
	{
		if (rear_medium != NULL) 
			rear_medium->next = tmp;	
		else
			rear_high->next = tmp;
	}
	else 
		rear_low->next = tmp;

	rear_low = tmp;
}
bool LQueue::Pop() {
	if (size == 0)
		return false;

	QItem* tmp = front;
	if (size == 1 || front->priority != front->next->priority) {
		switch (front->priority) {
		case HIGH:
			rear_high = NULL;
			break;
		case MEDIUM:
			rear_medium = NULL;
			break;
		case LOW:
			rear_low = NULL;
			break;
		}
	}

	front = front->next;
	delete tmp;
	size--;
	
	return true;
}
int LQueue::GetFirstValue() const {
	if (size == 0)
		throw exception("Impossible to execute GetFirst: queue is empty");
			return front->info;
}
Priority LQueue::GetFirstPriority() const {
	if (size == 0)
		throw exception("Impossible to execute GetFirst: queue is empty");
	return front->priority;
}
bool LQueue::IsEmpty() const {
	return (size == 0);
}
unsigned LQueue::Count(Priority priority) const
{
	int counter = 0;
	QItem* tmp = front;
	for (unsigned i = 0; i < size; i++) {
		if (tmp->priority == priority)
			counter++;
		tmp = tmp->next;
	}
	return counter;
}
//Не актуально
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
