#ifndef GRAPHINC_H 
#define GRAPHINC_H 
#include<iostream>
#include<fstream>
#include"HashTable(1).h"

template<class T, class E>
struct Edge
{
	T dest1;          //边上顶点
	T dest2;			//边的另一个顶点
	E cost;				//边上的权值
	Edge<T, E> * link;	//下一条边链指针
	Edge<T, E>*next;    //邻接表中的下一个指针
	Edge<T, E>*last;    //邻接表中的上一个指针
	Edge<T, E>*brother; //邻接表的兄弟指针，可以指向自身
	Edge(T Vertex1, T Vertex2, E dis):dest1(Vertex1), dest2(Vertex2), cost(dis), next(NULL), last(NULL), brother(NULL) {};
	Edge():next(NULL),last(NULL),brother(NULL) {};
};
template<class T,class E>
struct Vertex
{
	T data;                    //顶点元素值
	Edge<T, E> *adj;			//边链表的头指针
	Vertex<T,E>*next;        //指向下一点
	Vertex<T,E>*last;       //指向上一点
	int degree;//顶点的度
	Vertex(T Vertex1, Vertex<T,E>*left, Vertex<T,E>*right) data(Vertex1), last(left), next(right) {};
	Vertex():adj(NULL),next(NULL),last(NULL){};
};

template<class T, class E>
class graphinc
{
public:
	graphinc()	//构造函数1
	{
		last = first = new Vertex<T,E>();
		first->last = last;
		last->next = first;
		input();
	};
	~graphinc() {};				//析构函数
	bool IsEmpty()const						//判断表空否，空返回true
	{
		return first->next == NULL ? true : false;
	}
	bool IsFull()const //表不会满
	{
		return false;
	};
	Vertex<T, E> *gethead()
	{
		return first;
	};
	int getvertices() //返回顶点个数
	{
		return num;
	};
	//int vertexCount();//返回图中的顶点数 O(1)
	int edgeCount（）;// 返回图中的边数 O(1)
	//getVertices();// 返回包含所有顶点的数组 O（ | v | ）
	void addVertex(T vertex1);// 添加顶点 O(1)
	//void removeVertex(T vertex1);//删除顶点 O(d)
	Vertex<T>* isVertex(T v);// 判断该顶点是否在图中 O(1),在的话，返回地址。不在的话，返回值为空
	int degree(T v);// 顶点的度 O(1)
	Edge<T,E>* getFirstNeighbor(T v);// 返回第一个邻接顶点 O(1)
	//int getNextNeighbor(T v1, T v2);// 返回下一个邻接顶点 O(d)
	void addEdge(T v1, T v2);// 添加边 O(1)
	//void removeEdge(T v1, T v2);// 删除边 O(1)
	//int isEdge(Object, Object);// 判断是否为边 O(1)
	//int weight(Object, Object);//
protected:
	Vertex<T,E> * first;					//链表头指针
	Vertex<T,E> *last;
	int num = 0;
	HashTable<T> V;
	HashTable<T> E;
};
template<class T, class E>
void graphinc<T, E>::input() {
	ifstream ifile;
	T vertex1;
	ifile.open("Vertices.txt");
	ifile >> vertex1;
	num++;
	Vertex<T,E> * p1 = new Vertex<T,E>(vertex1);
	first->next = p1;
	first->last = p1;
	p1->last = first;
	p1->next = first;
	last = p1;
	while (1) {
		ifile >> vertex1;
		if (ifile.eof() != 0)
			break;
		num++;
		Vertex<T> * newVertex = new Vertex<T>(vertex1);
		if (newVertex == NULL)
		{
			cout << "内存分配错误！" << endl;
			exit(1);
		}
		last->next = newVertex;
		newVertex->last = last;
		newVertex->next = first;
		first->last = newVertex;				//将新节点与前面一个节点以及后面一个结点的四条边连起来
		last = newVertex;
		p1 = newVertex;
	}
}
template<class T, class E>
void graphinc<T, E>::output() {
	Vertex<T> *p = first->next;
	while (p != first) {
		cout << p->data << endl;
		p = p->next;
	}
}
template<class T, class E>
int graphinc<T, E>::degree(T v)//顶点的度数
{
	Vertex<T> *curr;
	curr = ht.search(v);
	return curr->degree;
}
template<class T, class E>             //判断顶点
Vertex<T, E>* graphinc<T, E>::isVertex(T v)
{
	Vertex<T>* curr;
	curr = ht.search(v);
	return curr;
}

template<class T, class E>//添加边
void graphinc<T, E>::addEdge(T v1, T v2)
{
	E i;
	cout >> "输入边上的权值:";
	cin >> i;
	Vertex<T>* pre, *newEdge1 = new Edge<T, E>(T v1, T v2, E i), *newEdge2 = new Edge<T, E>(T v2, T v1, E i);
	pre = ht.search(v1);
	newEdge1->next = pre->adj->next;
	pre->adj->next = newEdge1;
	newEdge1->last = pre->adj;
	ht.add(newEdge1, 2, v1, v2);
	pre = ht.search(v2);
	newEdge2->last = pre->adj;
	newEdge2->next = pre->adj->next;
	pre->adj->next = newEdge2;
	newEdge1->brother = newEdge2;
	newEdge2->brother = newEdge1;
	ht.add(newEdge2,2,v2,v1);//之后这里要把边加入hash表里
}
template<class T, class E>
Vertex<T, E>* graphinc<T, E>::getFirstNeighbor(T v)//返回第一个临界顶点
{
	Vertex<T>*curr;
	curr = ht.search(v);
	return curr->adj->next;
}
template<class T, class E>
void graphinc<T, E>::addVertex(T vertex)//添加定点
{
	T newVertex;
	cout >> "输入添加新节点名称：";
	cin >> newVertex;
	Vertex<T>* newnode = new Vertex<T>*(newVertex);


}
template<class T,class E>
void graphinc<T, E>::removeVertex(T vertex1)
{


}
template<class T,class E>
void graphinc<T, E>::removeEdge(T v1, T v2)
{


}
#endif