#pragma once

#include <memory>

// copied from class
namespace SpriteEngine {
	template<typename T>
	struct TT {
	};

	template<typename T>
	struct abstract_creator {
		virtual std::unique_ptr<T> doCreate(TT<T>&&) = 0;
	};

	template<typename... Ts>
	struct abstract_factory : public abstract_creator<Ts>... {

		template<class U> std::unique_ptr<U> create() {
			abstract_creator<U>& creator = *this;
			return creator.doCreate(TT<U>());
		}
		virtual ~abstract_factory() = default;
	};

	template<typename AbstractFactory, typename Abstract, typename Concrete>
	struct concrete_creator : virtual public AbstractFactory {
		std::unique_ptr<Abstract> doCreate(TT<Abstract>&&) override {
			return std::make_unique<Concrete>();
		}
	};

	template<typename AbstractFactory, typename... ConcreteTypes>
	struct concrete_factory;

	template<typename... AbstractTypes, typename... ConcreteTypes>
	struct concrete_factory
		<abstract_factory<AbstractTypes...>, ConcreteTypes...>
		: public concrete_creator<abstract_factory<AbstractTypes...>,
		AbstractTypes, ConcreteTypes>... {
	};
}
