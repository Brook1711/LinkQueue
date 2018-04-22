#include<iostream>

using namespace std;

template<class T>
struct Node
{
	T data;
	struct Node<T> * next;
}; //����ڵ�

template<class T>
class LinkQueue
{
private:
	Node<T> * front; //��ͷָ��
	Node<T> * rear; //��βָ��
public:
	LinkQueue()
	{
		front = rear = new Node<T>;
		front->next = NULL;
	} //���캯��
	~LinkQueue(); //��������
	void EnQueue(T x); //���
	T DeQueue(); //����
	T GetFront(); //���ʶ�ͷԪ��
	bool Empty()
	{
		return (!front->next) ? true : false;
	}//�жӿ�
	void Print() //��������
	{
		Node<T>*p = front->next;
		if (!p)
		{
			cout << "Print:�����ѿ�";
		}
		else
		{
			while (p)
			{
				cout << p->data << " ";
				p = p->next;
			}
		}
		cout << endl;
	}
};

template<class T>
LinkQueue<T>::~LinkQueue() //����������ʵ��
{
	while (front)
	{
		rear = front->next;
		delete front;
		front = rear;
	}
}

template<class T>
void LinkQueue<T>::EnQueue(T x) //��Ӻ�����ʵ��
{
	rear->next = new Node<T>;//��	��ָ��rear->nextָ�������Node�Ͷѿռ䡣
	rear = rear->next;//��	��rearָ���µĽڵ㡣
	rear->data = x;//��	��ʼ���½ڵ��е�data���ݡ�
	rear->next = NULL;//��	���½ڵ��е�nextָ���ÿա�
}

template<class T>
T LinkQueue<T>::DeQueue() //���Ӻ�����ʵ��
{
	Node<T> *p = front->next;
	if (!p)
		throw"����";//��	����pΪ�����׳�������Ϣ�����硱��ԭ��ͷԪ�س��С�
	front->next = p->next;//��	�½�ָ��pʹ��ָ��front->next��
	T x = p->data;//��	����ͷ�����ݴ浽T�ͱ���x�С�
	delete p;//��	�ͷ�ԭ���ж�ͷԪ�ء�
	if (!front->next)
		rear = front;//��	�����б�Ϊ�նӣ��޸Ķ�βָ�롣
	return x;
}

template<class T>
T LinkQueue<T>::GetFront() //���ʶ���Ԫ��
{
	if (!front->next)
		throw"����";
	return front->next->data;
}

int main()
{
	LinkQueue<int> M;
	for (int i = 0; i < 20; i++)
	{
		M.EnQueue(i + 1); 
	}
	M.Print();//������Ӳ���
	for (int i = 0; i < 10; i++)
	{
		M.DeQueue();
	}
	M.Print(); //������Ӳ���
	cout << M.GetFront() << endl; //�����ȡ����
	try 
	{
		for (int i = 0; i < 11; i++)
		{
			M.DeQueue();
		}
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	} //�����쳣�������
	try
	{
		M.GetFront();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	} //�����쳣�������
	M.Print();
	if (M.Empty())
		cout << "ԭ�����ѿ�" << endl; //�����п�
	system("pause");
	return 0;
}