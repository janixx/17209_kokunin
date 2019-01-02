#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>
#include "strategy.h"

template<class ID , class Creator = Strategy * (*)()>
class Factory {
	std::map < ID, Creator > creators;
public:
	Strategy * createStrategyByID(const ID & id) {
		auto it = creators.find(id);
		if (creators.end() == it) {
			return nullptr;
		}
		Creator creator = it->second;
		auto s = creator();
		return s;
	}
	bool regStrategy(const ID & id, const Creator & creator) {
		auto s = createStrategyByID(id);
		if (s == nullptr) {
			creators[id] = creator;
			return true;
		}
		else {
			delete s;
			return false;
		}
	}

	static Factory * getInstance() {
		static Factory f;
		return &f;
	}
private:
	Factory() = default;
	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;//методы удалены(их нет, фабрику нельзя создать)

};
#endif