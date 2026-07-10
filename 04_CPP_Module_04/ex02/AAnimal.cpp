#include "AAnimal.hpp"
#include <iostream>

AAnimal::AAnimal() : type("Animal") {
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type) : type(type) {
    std::cout << "AAnimal parametrized constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &src) {
    std::cout << "AAnimal copy constructor called" << std::endl;
    *this = src;
}

AAnimal::~AAnimal() {
    std::cout << "AAnimal destructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &rhs) {
    if (this != &rhs)
        this->type = rhs.type;
    return *this;
}

std::string AAnimal::getType() const {
    return this->type;
}

// No implementación de makeSound() ya que es un método virtual puro

Brain* AAnimal::getBrain() const {
    return NULL;
}
