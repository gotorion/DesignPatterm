#include <format>
#include <iostream>

struct EatParams {
  int amount;
  int speed;
};

struct DrinkParams {
  int volume;
  int temperature;
};

struct FoodVisitor {
  virtual ~FoodVisitor() = default;
  virtual void visit(struct Eatable *eat) {}
  virtual void visit(struct Drinkable *drin) {}
};

struct Food {
  virtual ~Food() = default;
  virtual void accept(FoodVisitor *visitor) = 0;
};

#define DEF_FOOD_ACCEPT                                                        \
  void accept(FoodVisitor *visitor) override { visitor->visit(this); }

struct Eatable : virtual Food {
  virtual void eat(EatParams eatParams) = 0;
  DEF_FOOD_ACCEPT
};

struct Drinkable : virtual Food {
  virtual void drink(DrinkParams drinkParams) = 0;
  DEF_FOOD_ACCEPT
};

struct Cake : Eatable {
  void eat(EatParams eatParams) override {
    std::cout << std::format("{}", "Eat cake") << std::endl;
  }
};

struct Milk : Drinkable {
  void drink(DrinkParams drinkParams) override {
    std::cout << std::format("{}", "Drink milk") << std::endl;
  }
};

struct Pudding : Eatable, Drinkable {
  void eat(EatParams eatParams) override { std::cout << "Eat pudding\n"; }
  void drink(DrinkParams drinkParams) override {
    std::cout << "Drink pudding\n";
  }
  void accept(FoodVisitor *visitor) override {
    Eatable::accept(visitor);
    Drinkable::accept(visitor);
  }
};

struct User : FoodVisitor {
  void visit(Eatable *eat) override { eat->eat({5, 10}); }
  void visit(Drinkable *drink) override { drink->drink({10, 20}); }
};

int main() {
  Cake cake;
  Milk milk;
  User user;

  milk.accept(&user);
  cake.accept(&user);
  return 0;
}