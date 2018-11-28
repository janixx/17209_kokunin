#pragma once

#include <map>
#include <string>
#include "strategy.h"

template<class ID , class Creator>
class Factory {
	std::map < ID, Creator > creators;
public:
	Strategy * createStrategyByID(const ID & id) {
		auto it = creators.find(id);
		if (creators.end() == it) {
			//no creator found
			return nullptr;
		}
		//������� ��������
		Creator creator = it->second;
		Strategy * s = creator();
		return s;
		//��� return it->second();
	}
	bool regStrategy(const ID & id, const Creator & creator) {
		creators[id] = creator;//������ -- ��������������� (register twice)
		return true;
	}

	static Factory * getInstance() {
		static Factory f;//����� ����� -- �� ������� ����� � ������� �� ����� ��������
						//������� ��������� -- ��� �������
						//� ������ ��� ������, � ��������� �� ������
		return &f;
	}
	//����������� ����� -- ����� ��� �������� �� ����� ������:
	//��� this'a
	//����� ���������� � ��������� �����
private:
	Factory() = default;
	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;//������ �������(�� ���, ������� ������ �������)

};
