#ifndef GRAPHINC_H 
#define GRAPHINC_H 
#include<iostream>
#include<fstream>
#include"HashTable(1).h"

template<class T, class E>
struct Edge
{
	T dest1;          //���϶���
	T dest2;			//�ߵ���һ������
	E cost;				//���ϵ�Ȩֵ
	Edge<T, E> * link;	//��һ������ָ��
	Edge<T, E>*next;    //�ڽӱ��е���һ��ָ��
	Edge<T, E>*last;    //�ڽӱ��е���һ��ָ��
	Edge<T, E>*brother; //�ڽӱ���ֵ�ָ�룬����ָ������
	Edge(T Vertex1, T Vertex2, E dis):dest1(Vertex1), dest2(Vertex2), cost(dis), next(NULL), last(NULL), brother(NULL) {};
	Edge():next(NULL),last(NULL),brother(NULL) {};
};
template<class T,class E>
struct Vertex
{
	T data;                    //����Ԫ��ֵ
	Edge<T, E> *adj;			//�������ͷָ��
	Vertex<T,E>*next;        //ָ����һ��
	Vertex<T,E>*last;       //ָ����һ��
	int degree;//����Ķ�
	Vertex(T Vertex1, Vertex<T,E>*left, Vertex<T,E>*right) data(Vertex1), last(left), next(right) {};
	Vertex():adj(NULL),next(NULL),last(NULL){};
};

template<class T, class E>
class graphinc
{
public:
	graphinc()	//���캯��1
	{
		last = first = new Vertex<T,E>();
		first->last = last;
		last->next = first;
		input();
	};
	~graphinc() {};				//��������
	bool IsEmpty()const						//�жϱ�շ񣬿շ���true
	{
		return first->next == NULL ? true : false;
	}
	bool IsFull()const //������
	{
		return false;
	};
	Vertex<T, E> *gethead()
	{
		return first;
	};
	int getvertices() //���ض������
	{
		return num;
	};
	//int vertexCount();//����ͼ�еĶ����� O(1)
	int edgeCount����;// ����ͼ�еı��� O(1)
	//getVertices();// ���ذ������ж�������� O�� | v | ��
	void addVertex(T vertex1);// ��Ӷ��� O(1)
	//void removeVertex(T vertex1);//ɾ������ O(d)
	Vertex<T>* isVertex(T v);// �жϸö����Ƿ���ͼ�� O(1),�ڵĻ������ص�ַ�����ڵĻ�������ֵΪ��
	int degree(T v);// ����Ķ� O(1)
	Edge<T,E>* getFirstNeighbor(T v);// ���ص�һ���ڽӶ��� O(1)
	//int getNextNeighbor(T v1, T v2);// ������һ���ڽӶ��� O(d)
	void addEdge(T v1, T v2);// ��ӱ� O(1)
	//void removeEdge(T v1, T v2);// ɾ���� O(1)
	//int isEdge(Object, Object);// �ж��Ƿ�Ϊ�� O(1)
	//int weight(Object, Object);//
protected:
	Vertex<T,E> * first;					//����ͷָ��
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
			cout << "�ڴ�������" << endl;
			exit(1);
		}
		last->next = newVertex;
		newVertex->last = last;
		newVertex->next = first;
		first->last = newVertex;				//���½ڵ���ǰ��һ���ڵ��Լ�����һ������������������
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
int graphinc<T, E>::degree(T v)//����Ķ���
{
	Vertex<T> *curr;
	curr = ht.search(v);
	return curr->degree;
}
template<class T, class E>             //�ж϶���
Vertex<T, E>* graphinc<T, E>::isVertex(T v)
{
	Vertex<T>* curr;
	curr = ht.search(v);
	return curr;
}

template<class T, class E>//��ӱ�
void graphinc<T, E>::addEdge(T v1, T v2)
{
	E i;
	cout >> "������ϵ�Ȩֵ:";
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
	ht.add(newEdge2,2,v2,v1);//֮������Ҫ�ѱ߼���hash����
}
template<class T, class E>
Vertex<T, E>* graphinc<T, E>::getFirstNeighbor(T v)//���ص�һ���ٽ綥��
{
	Vertex<T>*curr;
	curr = ht.search(v);
	return curr->adj->next;
}
template<class T, class E>
void graphinc<T, E>::addVertex(T vertex)//��Ӷ���
{
	T newVertex;
	cout >> "��������½ڵ����ƣ�";
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