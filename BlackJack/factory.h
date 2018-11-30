#pragma once

#include <map>
#include <string>
#include "strategy.h"
#ifndef FACTORY_H
#define FACTORY_H

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
		//вызвать креэйтор
		Creator creator = it->second;
		Strategy * s = creator();
		return s;
	}
	bool regStrategy(const ID & id, const Creator & creator) {
		creators[id] = creator;//грабли -- перерегистрация (register twice)
		return true;
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