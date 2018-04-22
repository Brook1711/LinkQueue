#include<iostream>

using namespace std;

template<class T>
struct Node
{
	T data;
	struct Node<T> * next;
}; //定义节点

template<class T>
class LinkQueue
{
private:
	Node<T> * front; //队头指针
	Node<T> * rear; //队尾指针
public:
	LinkQueue()
	{
		front = rear = new Node<T>;
		front->next = NULL;
	} //构造函数
	~LinkQueue(); //析构函数
	void EnQueue(T x); //入队
	T DeQueue(); //出队
	T GetFront(); //访问队头元素
	bool Empty()
	{
		return (!front->next) ? true : false;
	}//判队空
	void Print() //遍历函数
	{
		Node<T>*p = front->next;
		if (!p)
		{
			cout << "Print:队列已空";
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
LinkQueue<T>::~LinkQueue() //析构函数的实现
{
	while (front)
	{
		rear = front->next;
		delete front;
		front = rear;
	}
}

template<class T>
void LinkQueue<T>::EnQueue(T x) //入队函数的实现
{
	rear->next = new Node<T>;//①	令指针rear->next指向申请的Node型堆空间。
	rear = rear->next;//②	令rear指向新的节点。
	rear->data = x;//③	初始化新节点中的data数据。
	rear->next = NULL;//④	将新节点中的next指针置空。
}

template<class T>
T LinkQueue<T>::DeQueue() //出队函数的实现
{
	Node<T> *p = front->next;
	if (!p)
		throw"下溢";//②	（若p为空则抛出错误信息“下溢”）原队头元素出列。
	front->next = p->next;//①	新建指针p使其指向front->next。
	T x = p->data;//③	将队头数据暂存到T型变量x中。
	delete p;//④	释放原队列队头元素。
	if (!front->next)
		rear = front;//⑤	若队列变为空队，修改队尾指针。
	return x;
}

template<class T>
T LinkQueue<T>::GetFront() //访问队首元素
{
	if (!front->next)
		throw"上溢";
	return front->next->data;
}

int main()
{
	LinkQueue<int> M;
	for (int i = 0; i < 20; i++)
	{
		M.EnQueue(i + 1); 
	}
	M.Print();//检验入队操作
	for (int i = 0; i < 10; i++)
	{
		M.DeQueue();
	}
	M.Print(); //检验出队操作
	cout << M.GetFront() << endl; //检验获取队首
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
	} //检验异常处理机制
	try
	{
		M.GetFront();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	} //检验异常处理机制
	M.Print();
	if (M.Empty())
		cout << "原队列已空" << endl; //检验判空
	system("pause");
	return 0;
}