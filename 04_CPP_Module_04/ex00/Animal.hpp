#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal &src);
    virtual ~Animal();
    Animal &operator=(const Animal &rhs);

    std::string getType() const;
    virtual void makeSound() const;
};

#endif
