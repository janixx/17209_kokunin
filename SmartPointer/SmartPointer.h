#include <cstdio>
#include <fstream>

template<class T> class SmartPointer {
private:
	struct SmartPtrData {
		size_t counter = 0u;
		T * ptr = nullptr;
	};
	SmartPtrData * spdata = nullptr;
public:
	SmartPointer() {};	//default constructor
	~SmartPointer() {
		if (!spdata)
			return;
		if (1 == spdata->counter) {
			delete spdata->ptr;
			delete spdata;
			return;
		}
		--spdata->counter;
		spdata = nullptr;
	}
	SmartPointer(T * a = nullptr) {
		spdata = new SmartPtrData;
		spdata->counter = 1u;
		spdata->ptr = a;
	}	//����������� ����������� ������
	SmartPointer(const SmartPointer& other) {
		if (!other.spdata) {
			this = nullptr;
			return;
		}
		spdata = other.spdata;
		++spdata->counter;
	}	//�-� �����������
	SmartPointer& operator=(const SmartPointer& other) {
		if (*this!=other) {
			this->~SmartPointer();
			spdata = other.spdata;
			++spdata->counter;
		}
		return *this;
	}	// �� ������� - ���������� ��������� �����������
	T * get() {
		return spdata->ptr;//???????????????
							//What is doing this method?
	}// �������� ���������
	void reset(T * other) {
		this->~SmartPointer();
		spdata = new SmartPtrData;
		spdata->ptr = other;
		spdata->counter = 1u;
	}// ���������� ������ ������, ������ �����
	//operator* , operator->
	T& operator*() {
		return *(spdata->ptr);
	}
	T * operator->() {
		return spdata->ptr;
	}
};


	// ������� 1: ����������� ����������� (std::auto_ptr)
	// ������� 2: ���������� ���-������� ������ ������ ��� ������ ������
	// ������� 3: ������ ������� ����� �� ����� (std::shared_ptr) + ������
	// ������� extra: ������� ������ (������� ���-�� ������ �� ��� ������) (������ ������� ����� ������� ��� ���������)
			//��� � �������
	// ������� 4: base::linker_ptr (chromium)
	// ������� 5: ������� ������ ������� ����� � ������� (boost::instructive_ptr, refcounte
	// ������� 6: ��������� ����������� (boost::scoped_ptr)
	// ������� 7: ��������� �����������, �� ��������� ����������� (std::unique_ptr)
					// - ������������ ����������� (� �� ������ ����, � ��� �����)