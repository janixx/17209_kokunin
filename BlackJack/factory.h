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
		//вызвать креэйтор
		Creator creator = it->second;
		Strategy * s = creator();
		return s;
		//или return it->second();
	}
	bool regStrategy(const ID & id, const Creator & creator) {
		creators[id] = creator;//грабли -- перерегистрация (register twice)
		return true;
	}

	static Factory * getInstance() {
		static Factory f;//время жизни -- от первого входа в функцию до конца прогаммы
						//область видимости -- эта функция
						//в первый раз создаём, в отсальные не меняем
		return &f;
	}
	//статический метод -- метод для которого не нужен объект:
	//нет this'a
	//может обращаться к приватной части
private:
	Factory() = default;
	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;//методы удалены(их нет, фабрику нельзя создать)

};
