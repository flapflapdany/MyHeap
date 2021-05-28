#pragma once
#include<vector>
#include<iostream>

using namespace std;

template<typename T>
class Node
{
public:
	int  pr;//key
	T data;
	Node(int _pr, T _data)
	{
		pr = _pr;
		data = _data;
	}
	Node& operator=(const Node& a)
	{
		data = a.data;//key
		pr = a.pr;
		return *this;
	}
	Node(int prior) : pr(prior) {}//for change priority
	bool operator==(const Node& a) { return (pr == a.pr); }
	bool operator!=(const Node& a) { return (pr != a.pr); }
	bool operator<(const Node& a) { return (pr < a.pr); }
	bool operator>(const Node& a) { return (pr > a.pr); }
};

template<typename T>
class Heap
{
	vector<Node<T>> heap;
	int size;
	int d;
public:
	Heap(int dem = 2) :d(dem), size(0) {}
	Heap(const Heap& a)//����������� �����������
	{
		heap = a.heap;
		d = a.d;
		size = a.size;
	}
	Heap(const vector<int>& prior, int _size, int d)
	{
		this->d = d;
		for (int i = 0; i < _size; i++)
		{
			Node<T> tmp(prior[i]);//change
			heap.push_back(tmp);
		}
		size = _size;
		MakeHeap();
		HeapSort();
	}
	void HeapSort()
	{
		vector<Node<T>> new_heap;
		int new_size = size;
		for (int i = 0; i < new_size; i++)
		{
			new_heap.push_back(heap[0]);
			DeleteMin();
		}
		heap = new_heap;
		size = new_size;
	}
	int Parent(int i)
	{
		int p = (i - 1) / d;
		return (i > 0) ? p : 0;
	}
	int RightChild(int i)
	{
		int rightchild = d * i + d;
		int d1 = (rightchild > (size - 1)) ? (size - 1) : rightchild;
		return d1;
	}
	int LeftChild(int i)
	{
		int rightchild = d * i + 1;
		int d1 = (rightchild > (size - 1)) ? 0 : rightchild;
		return d1;
	}
	int MinChild(int i)
	{
		int left = LeftChild(i);
		if (left == 0) return 0;
		int	right = RightChild(i);
		Node<T> min = heap[left];
		int minindex = left;
		for (int i = left + 1; i <= right; i++)
		{
			if (heap[i] < min)
			{
				min = heap[i];
				minindex = i;
			}
		}
		return minindex;
	}
	void Diving(int i)//����������
	{
		int j1, j2;
		j1 = i;
		j2 = MinChild(i);
		while (j2 != 0 && heap[j1]>heap[j2])
		{
			Node<T> tmp = heap[j1];
			heap[j1] = heap[j2];
			heap[j2] = tmp;
			j1 = j2;
			j2 = MinChild(j1);
		}
	}
	void Emersion(int i)
	{
		int j1, j2;
		j1 = i;
		j2 = Parent(i);
		while (heap[j1] < heap[j2] && j2 != 0)
		{
			Node<T> tmp = heap[j1];
			heap[j1] = heap[j2];
			heap[j2] = tmp;
			j1 = j2;
			j2 = Parent(j1);
		}
	}
	void Insert(T data, int pr)
	{
		Node<T> M(data, pr);
		heap.push_back(M);
		Emersion(heap.size() - 1);
		size++;
	}
	void DeleteMin()
	{
		heap[0] = heap[size - 1];
		heap.pop_back();
		size--;
		if (size > 1)
		{
			Diving(0);
		}
	}
	void Delete(int i)
	{
		heap[i].pr = 0;
		Emersion(i);
		DeleteMin();
	}
	void MakeHeap()
	{
		for (int i = (size - 1); i >= 0; i--)
		{
			Diving(i);
		}
	}
	~Heap() {}
};

template<typename T>
class  QueuePr
{
	vector<Node<T>> queue;
	int size;
	int d;
public:
	QueuePr(int dem = 2) :d(dem), size(0) {}
	QueuePr(const QueuePr& a)
	{
		queue = a.queue;
		d = a.d;
		size = a.size;
	}
	int Parents(int i)
	{
		int p = (i - 1) / d;
		return (i > 0) ? p : 0;
	}
	int Right_Child(int i)
	{
		int rightchild = d * i + d;
		int d1 = (rightchild > (size - 1)) ? (size - 1) : rightchild;
		return d1;
	}
	int Left_Child(int i)
	{
		int rightchild = d * i + 1;
		int d1 = (rightchild > (size - 1)) ? 0 : rightchild;
		return d1;
	}
	int Min_Child(int i)
	{
		int left = Left_Child(i);
		if (left == 0) return 0;
		int	right = Right_Child(i);
		Node<T> min = queue[left];
		int minindex = left;
		for (int i = left + 1; i <= right; i++)
		{
			if (queue[i] <queue)
			{
				min = queue[i];
				minindex = i;
			}
		}
		return minindex;
	}
	void Div(int i)//����������
	{
		int j1, j2;
		j1 = i;
		j2 = Min_Child(i);
		while (j2 != 0 && queue[j1]>queue[j2])
		{
			Node<T> tmp = queue[j1];
			queue[j1] = queue[j2];
			queue[j2] = tmp;
			j1 = j2;
			j2 = Min_Child(j1);
		}
	}
	void Emer(int i)
	{
		int j1, j2;
		j1 = i;
		j2 = Parents(i);
		while (queue[j1] < queue[j2] && j2 != 0)
		{
			Node<T> tmp = queue[j1];
			queue[j1] = queue[j2];
			queue[j2] = tmp;
			j1 = j2;
			j2 = Parents(j1);
		}
	}
	void Ins(T data, int pr)
	{
		Node<T> M(data, pr);
		queue.push_back(M);
		Emer(heap.size() - 1);
		size++;
	}
	void Delete_Min()
	{
		queue[0] = queue[size - 1];
		queue.pop_back();
		size--;
		if (size > 1)
		{
			Div(0);
		}
	}
	void Del(int i)
	{
		queue[i].pr = 0;
		Emer(i);
		Delete_Min();
	}
	void MakeHeap()
	{
		for (int i = (size - 1); i >= 0; i--)
		{
			Div(i);
		}
	}
	void decreaseWeight(int i, int  delta)
	{
		queue[i].pr -= delta;
		Emer(i);
	}
	int TopinPt()
	{
		return(queue[0]);
	}
	~QueuePr() {}
};