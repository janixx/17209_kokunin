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
	}	//конструктор захватывает ресурс
	SmartPointer(const SmartPointer& other) {
		if (!other.spdata) {
			this = nullptr;
			return;
		}
		spdata = other.spdata;
		++spdata->counter;
	}	//к-р копирования
	SmartPointer& operator=(const SmartPointer& other) {
		if (*this!=other) {
			this->~SmartPointer();
			spdata = other.spdata;
			++spdata->counter;
		}
		return *this;
	}	// по желанию - поддержать семантику перемещения
	T * get() {
		return spdata->ptr;//???????????????
							//What is doing this method?
	}// получить указатель
	void reset(T * other) {
		this->~SmartPointer();
		spdata = new SmartPtrData;
		spdata->ptr = other;
		spdata->counter = 1u;
	}// освободить старый ресурс, занять новый
	//operator* , operator->
	T& operator*() {
		return *(spdata->ptr);
	}
	T * operator->() {
		return spdata->ptr;
	}
};


	// вариант 1: разрушающее копирование (std::auto_ptr)
	// вариант 2: глобальная хэш-таблица хранит флажки про каждый ресурс
	// вариант 3: флажок хранить сразу на месте (std::shared_ptr) + нюансы
	// вариант extra: счётчик ссылок (считать кол-во ссылок на наш объект) (каждый поинтер знает сколько ещё поинтеров)
			//его и напишем
	// вариант 4: base::linker_ptr (chromium)
	// вариант 5: счётчик ссылок хранить прямо в объекте (boost::instructive_ptr, refcounte
	// вариант 6: запретить копирование (boost::scoped_ptr)
	// вариант 7: запретить копирование, но разрешить перемещение (std::unique_ptr)
					// - используются повсеместно (и во второй лабе, в том числе)