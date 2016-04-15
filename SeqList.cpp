# SeqListCpp
c++实现顺序表
#include <iostream>
using namespace std;

const int DEAFAULT_CAPACITY = 5;//默认容量
const int DEAFAULT_INC = 3;//默认增加的空间

typedef int DataType;
class SeqList
{
	friend ostream& operator<<(ostream& os, SeqList& s);
public:
	//构造函数
	SeqList()
		:_size(0)
		,_capacity(DEAFAULT_CAPACITY)
		,_pData(NULL)
	{
		_pData = new DataType[DEAFAULT_CAPACITY];
	}

	//拷贝构造
	SeqList(const SeqList& s)
		:_size(s._size)
		,_capacity(s._capacity)
		, _pData(NULL)
	{
		_pData = new DataType[_capacity];
		memcpy(_pData, s._pData, _size*sizeof(DataType));
	}

	//赋值
	SeqList& operator =(const SeqList& s)
	{
		if (this != &s)//自赋值
		{
			delete[]_pData;
			_pData = new DataType[s._capacity];
			memcpy(_pData, s._pData, s._size*sizeof(DataType));
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}

	//析构函数
	~SeqList()
	{
		if (_pData != NULL)
		{
			delete[]_pData;
		}
	}

public:
	void PushBack(const DataType& d)
	{
		CheckCapacity();
		_pData[_size] = d;
		_size++;
	}
	void PopBack()
	{
		_size--;
	}
	void PushFront(const DataType& d)
	{
		CheckCapacity();
		int start = _size - 1;
		while (start >= 0)
		{
			_pData[start + 1] = _pData[start];
			start--;
		}
		_pData[0] = d;
		_size++;
	}
	void PopFront()
	{
		int i = 0;
		for (i = 0; i < _size-1; i++)
		{
			_pData[i] = _pData[i + 1];
		}
		_size--;
	}
	void Reverse()
	{
		int left = 0;
		int right = _size - 1;
		while (left < right)
		{
			DataType tmp = _pData[left];
			_pData[left] = _pData[right];
			_pData[right] = tmp;
			left++; right--;
		}
	}
	DataType* Find(const DataType& d)
	{
		int i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_pData[i] == d)
			{
				return &_pData[i];
			}
		}
		return NULL;
	}

	void Insert(int pos, const DataType& x)
	{
		if ((pos > 0) && (pos <= _size))//判断参数是否正确
		{
			CheckCapacity();
			int i = 0;
			for (i = _size-1; i >=pos-1; i--)
			{
				_pData[i + 1] = _pData[i];
			}
			_pData[pos - 1] = x;
			_size++;
		}
	}
	void Remove(DataType x)
	{
		int i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_pData[i] == x)
			{
				int pos = i;
				for (i = pos; i < _size; i++)
				{
					_pData[i] = _pData[i + 1];
				}
				_size--;
			}
		}
	}
	void RemoveAll(DataType x)
	{
		int i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_pData[i] == x)
			{
				i--;
				Remove(x);
			}
		}
	}

	void SortList()
	{
		int i = 0;
		bool flag = true;
		for (i = 0; i < _size-1 && flag; i++)
		{
			flag = false;
			int j = 0;
			for (j = 0; j < _size- i-1; j++)
			{
				if (_pData[j] > _pData[j + 1])
				{
					flag = true;
					DataType tmp = _pData[j];
					_pData[j] = _pData[j + 1];
					_pData[j + 1] = tmp;
				}
			}

		}
	}
	DataType* BinarySearch(DataType x)
	{
		int left = 0;
		int right = _size - 1;
		int mid = (left + right) / 2;
		while (left <= right)
		{
			if (_pData[mid] > x)
			{
				right = mid - 1;
				mid = (left + right) / 2;
			}
			else if (_pData[mid] < x)
			{
				left = mid + 1;
				mid = (left + right) / 2;
			}
			else
			{
				return &_pData[mid];
			}
		}
		return NULL;
	}

public:
		DataType& operator[](int index)
		{
			return _pData[index];
		}
private:
	void CheckCapacity()
	{
		if (_size == _capacity)
		{
			DataType* tmp = new DataType[_capacity + DEAFAULT_INC];
			memcpy(tmp, _pData, _size*sizeof(DataType));
			delete[]_pData;
			_pData = tmp;
			_capacity = _capacity + DEAFAULT_INC;
		}
	}

private:
	DataType* _pData;
	int _size;
	int _capacity;
};

ostream& operator<<(ostream& os, SeqList& s)
{
	int i = 0;
	for (i = 0; i < s._size; i++)
	{
		os << s._pData[i] << " ";
	}
	os << endl;
	return os;
}
void test()
{
	SeqList seqlist1;
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		seqlist1.PushFront(i+1);
	}
	seqlist1.PushFront(9);
	seqlist1.PushFront(10);
	seqlist1.PushFront(9);
	SeqList seqlist2(seqlist1);
	SeqList seqlist3;
	seqlist3 = seqlist2;
	/*seqlist3.PopBack();
	seqlist3.PopFront();
	seqlist3.PopBack();
	seqlist3.PopFront();
	seqlist3.PopBack();
	seqlist3.PopFront();
	seqlist3.PopBack();
	seqlist3.PopFront();
	seqlist3.PopBack();
	seqlist3.PopFront()*/;
	/*seqlist3.Reverse();*/
	//seqlist3.Insert(9, 11);
	cout << seqlist3;
	//seqlist3.RemoveAll(9);
	seqlist3.SortList();
	cout << seqlist3;
	cout << seqlist3.BinarySearch(1) << endl;
	cout << seqlist3.BinarySearch(2) << endl;
	cout << seqlist3.BinarySearch(3) << endl;
	cout << seqlist3.BinarySearch(4) << endl;
	cout << seqlist3.BinarySearch(5) << endl;
	cout << seqlist3.BinarySearch(6) << endl;
	cout << seqlist3.BinarySearch(7) << endl;
	cout << seqlist3.BinarySearch(8) << endl;
	cout << seqlist3.BinarySearch(9) << endl;
	cout << seqlist3.BinarySearch(10) << endl;
	cout << seqlist3.BinarySearch(11) << endl;
	cout << seqlist3.BinarySearch(12) << endl;
	cout << seqlist3;
	/*cout << seqlist3.Find(1) << endl;
	cout << seqlist3.Find(2) << endl;
	cout << seqlist3.Find(3) << endl;
	cout << seqlist3.Find(10) << endl;*/
}
int main()
{
	test();
	getchar();
	return 0;
}
