//#include"2048Kernel.h"
//#include<stdlib.h>
//#include<time.h>
//#include<stdio.h>
//Stack MakeStack()
//{
//	Stack s;
//	s.top = 4;
//	return s;
//}
//bool stackpush(lStack s, int element)
//{
//	if (s->top <= 0)
//	{
//		return false;
//	}
//	s->element[s->top - 1] = element;
//	s->top--;
//}
//int stackpop(lStack s)
//{
//	if (s->top >= 4)return 0;
//	int t;
//	t = s->element[s->top];
//	++s->top;
//	return t;
//}
//Queue MakeEmptyQueue()
//{
//	Queue queue;
//	queue.front = 0;
//	queue.rear = 0;
//	queue.count = 0;
//	queue.tail = 0;
//	return queue;
//}
//bool push(lQueue queue, int element)
//{
//	if (queue->count == SIZE)return false;
//	if (element == queue->tail)
//	{
//		queue->element[queue->rear - 1] = element * 2;
//		queue->tail = element * 2;
//		return true;
//	}
//	queue->element[queue->rear] = element;
//	queue->tail = element;
//	queue->rear = (queue->rear + 1) % SIZE;
//	++queue->count;
//	return true;
//}
//int pop(lQueue queue)
//{
//	int temp;
//	if (queue->count == 0)return 0;
//	if (queue->count == 1)queue->tail = 0;
//	temp = queue->element[queue->front];
//	queue->front = (queue->front + 1) % SIZE;
//	--queue->count;
//	return temp;
//}
//
//extern Queue queue;
//Map InitialMap()
//{
//	Map init;
//	for (int x = 0; x < SIZE; ++x)
//	{
//		for (int y = 0; y< SIZE; ++y)
//		{
//			srand(unsigned(time(NULL)) + x + y);
//			init.map[x][y] = (rand()%2 == 1 ? 0 : 2);
//		}
//	}
//	return init;
//}
//void TopMove(pMap m)
//{
//	int x, y;
//	for (y = 0; y < SIZE; ++y)
//	{
//		queue = MakeEmptyQueue();
//		for (x = 0; x < SIZE ; ++x)
//		{
//			if (m->map[x][y]!=0)
//			{
//				push(&queue, m->map[x][y]);
//			}
//		}
//		m->map[0][y] = pop(&queue);
//		m->map[1][y] = pop(&queue);
//		m->map[2][y] = pop(&queue);
//		m->map[3][y] = pop(&queue);
//	}
//	GerenralNew(m);
//}
//void BottomMove(pMap m)
//{
//	int x, y;
//	for (y = 0; y < SIZE; ++y)
//	{
//		queue = MakeEmptyQueue();
//		for (x = SIZE-1; x >=0; --x)
//		{
//			if (m->map[x][y] != 0)
//			{
//				push(&queue, m->map[x][y]);
//			}
//		}
//
//		m->map[3][y] = pop(&queue);
//		m->map[2][y] = pop(&queue);
//		m->map[1][y] = pop(&queue);
//		m->map[0][y] = pop(&queue);
//	}
//	GerenralNew(m);
//}
//void LeftMove(pMap m)
//{
//	int x, y;
//	for (x = 0; x < SIZE; ++x)
//	{
//		queue = MakeEmptyQueue();
//		for (y = 0; y < SIZE ; ++y)
//		{
//			if (m->map[x][y] != 0)
//			{
//				push(&queue, m->map[x][y]);
//			}
//		}
//
//		m->map[x][0] = pop(&queue);
//		m->map[x][1] = pop(&queue);
//		m->map[x][2] = pop(&queue);
//		m->map[x][3] = pop(&queue);
//	}
//	GerenralNew(m);
//}
//void RightMove(pMap m)
//{
//	int x, y;
//	for (x = 0; x < SIZE; ++x)
//	{
//		queue = MakeEmptyQueue();
//		for (y = SIZE-1; y >= 0; --y)
//		{
//			if (m->map[x][y] != 0)
//			{
//				push(&queue, m->map[x][y]);
//			}
//		}
//
//		m->map[x][3] = pop(&queue);
//		m->map[x][2] = pop(&queue);
//		m->map[x][1] = pop(&queue);
//		m->map[x][0] = pop(&queue);
//	}
//	GerenralNew(m);
//}
//bool IsFailure(const Map m)
//{
//	for (int i = 0; i < SIZE; ++i)
//	{
//		for (int j = 0; j < SIZE; ++j)
//		{
//			if (m.map[i][j] == 0)
//			{
//				return false;
//			}
//		}
//	}
//
//	int x, y;
//	for (y = 0; y < SIZE; ++y)
//	{
//		for (x = 0; x < SIZE - 1; ++x)
//		{
//			if (m.map[x][y] == m.map[x + 1][y])
//			{
//				return false;
//			}
//
//		}
//	}
//
//	for (x = 0; x < SIZE; ++x)
//	{
//		for (y = 0; y < SIZE - 1; ++y)
//		{
//			if (m.map[x][y] == m.map[x][y + 1])
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}
//unsigned short SquareRandom(int limit)
//{
//	srand(unsigned(time(NULL)));
//	if(limit==2)return rand();
//	return rand() % 4;
//}
//int GetInfo(Map m)
//{
//	int i, j, x = 0;
//	int Array[16];
//	int Temp, Max = 0;
//	for (i = 0; i < SIZE; ++i)
//	{
//		for (j = 0; j < SIZE; ++j);
//		{
//			Array[x] = m.map[i][j];
//			++x;
//		}
//	}
//	for (x = 0; x < 16; ++x)
//	{
//		if (Max < Array[x])
//		{
//			Max = Array[x];
//		}
//	}
//	return Max;
//}
//bool Save(Map m)
//{
//	/*FILE * save;
//	save = fopen("2048.cons", "w+");
//	if (save == NULL)
//	{
//		return false;
//	}
//	for (int x = 0; x < SIZE; ++x)
//	{
//		for (int y = 0; y < SIZE; ++y)
//		{
//			fwrite(&m.map[x][y], sizeof(m.map[x][y]), 1, save);
//		}
//	}
//	fclose(save);*/
//	return false;
//}
//void GerenralNew(pMap m)
//{
//	int x, y;
//	for (y = 0; y < SIZE; ++y)
//	{
//		for (x = 0; x < SIZE; ++x)
//		{
//			if (m->map[x][y] == 0)
//			{
//				m->map[x][y] = 2;
//				return;
//			}
//		}
//	}
//}
