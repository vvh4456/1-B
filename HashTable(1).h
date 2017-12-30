#ifndef _HASHTABLE_
#define _HASHTABLE_
#include<string>
#include<fstream>
#include<iostream>
#include<math.h>
#include<cstdio>
#include<cstdarg>
using namespace std;
#define DefaultSize 100								//��ඥ����
void MaxPrime(int &m) {
	int y, t1 = 0, t2 = 0;
	int sig = 0;
	int x = DefaultSize;
	for (int i = 2; i <= x; i++)
	{
		sig = 0;
		for (y = 2; y <= sqrt(x); y++)
			if (i%y == 0)
			{
				sig = 1;
				break;
			}
		if (sig == 0)
		{
			t1 = i;
		}
	}
	m = t1;
}
template<class T>
struct Node{
	T *pointer;			          //hash�������ָ��
	string  data[2];           //hash��������,�������ƻ���
	int sign;                //hash��λ���Ƿ�Ϊ��
	Node() { 
		sign = 0;
		pointer = NULL; 
	}
};
template<class T>
class HashTable
{
public:
	HashTable();
	~HashTable() {}
	//void input();									//����ʵ�
	T* search(int nCount, ...);						//�ߵĲ��ҺͶ���
		void add(T *p, int ncount, ...);
	//void remove(string da1,...);
private:
	Node<T> *ht;									//hash��
	int divitor,num;                        //numΪ�ɱ��������
	int CurrentSize, TableSize;
	//int GetPos(string da1, ...);		   //hash��ַ���ɺ���
};
template<class T>
HashTable<T>::HashTable()
{
	int x, y;
	MaxPrime(x);						//�õ�100֮����������
	divitor = x;
	TableSize = DefaultSize, CurrentSize = 0;
	ht = new Node<T>[TableSize];
}
template<class T>
T* HashTable<T>::search(int nCount, ...)//���������ض����λ��,
{
	string str;
	double sum = 0;
	string tem[2];
	int start = 0, pos = 0,i=0,j=0,t=1;
	int* p = &nCount;
	for (i = 0; i<nCount; ++i)
	{
		char* pTemp = (char*)*(++p);
		tem[i] = pTemp;
		str += pTemp;
	}
	for( i = 0; i < str.size(); i++)
	{
		sum += str[i] * pow(3, str[i] - 'A');
	}
	start = pos = fmod(sum, divitor);
	for (i = 0; i<nCount; ++i)
	if (ht[pos].data[i] != tem[i])		//�ж��Ƿ����
	{							
		t = 0;
	}
	if(t==0)
	{
		if (ht[pos].sign == 1)
			while (j < 5)
			{
				if (pos == start)
				{
					cout << "������" << endl;
					return false;
				}
				pos++;
				j++;
				for (i = 0; i < num; i++)
					if (ht[pos].data[i] == tem[i])
						return ht[pos].pointer;
			}
		else
		{
			cout << "������" << endl;
			return NULL;
		}
		}
	else
	{
		cout << "cc" << endl;
		return ht[pos].pointer;
	}
}
template<class T>
void HashTable<T>::add(T *point, int nCount, ...) {
	double sum=0;
	int start = 0, pos = 0,y=0,t=0;
	string str;
	string[]tem = new string[nCount];
	num = nCount;
	int* p = &nCount;
	for (int i = 0; i<nCount; ++i)
	{
		char* pTemp = (char*)*(++p);
		cout << pTemp << endl;
		tem[i] = pTemp;
		str += pTemp;
	}
	for (int i = 0; i < str.size; i++)
	{
		sum += str[i]*pow(3,str[i]-'A');

	}
	start = pos = fmod(sum, divitor);
		if (ht[pos].sign == 0)
		{
			t = 1;
		}
		else {
			while (ht[pos].sign != 0)
			{
				y++;
				pos= (pos+ 1) % TableSize;
				if (pos == start)
				{
					cout << "����" << endl;
					break;
				}
			}
			if (ht[pos].sign == 0)
				t = 1;
		}
		if (t==1)
		{
			for(i=0;i<nCount;i++)
			ht[pos].data[i] = tem[i];
			ht[pos].pointer = p1;
			ht[pos].sign = 1;
			CurrentSize++;
		}
		else {
			cout << "hash���Ȳ���" << endl;
		}
	cout << "������ͻ����" << y << endl;

}
/*template<class T, class E>
void HashTable<T,E>::input(T Vertex1) {
	int i = 0, vertexnum = 0, start = 0, y = 0;
	bool t = false;
	vertexnum = Q.getvertices();
	Node<T> *p = Q.gethead();
	p = p->next;
	while (vertexnum--) {
		GetPosAndTest(p->data, i);
		start = i;
		if (ht[i].sign == 0)
		{
			t = true;
		}
		else {
			while (ht[i].sign != 0)
			{
				y++;
				i = (i + 1) % TableSize;
				if (i == start)
				{
					cout << "����" << endl;
					break;
				}
			}
			if (ht[i].sign == 0)
				t = true;
		}
		if (t)
		{
			ht[i].data = p->data;
			ht[i].sign = 1;
			CurrentSize++;
		}
		else {
			cout << "hash���Ȳ���" << endl;
		}
		p = p->next;
	}
	cout << "������ͻ����" << y << endl;

}
template<class T>
void HashTable<T,E>::output() {
	int i = 0, t = 0;
	while (i<TableSize)
	{
		if (ht[i].sign == 1)
		{
			cout << ht[i].data << endl;
			t++;
			if (t == CurrentSize)
				break;
		}i++;
	}
*/
#endif // !_HASHTABLE_
