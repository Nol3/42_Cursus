/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:59:44 by alcarden          #+#    #+#             */
/*   Updated: 2025/03/01 15:45:55 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"
#include <iostream>

int main()
{
    std::cout << "\n=== Testing array of animals ===" << std::endl;
    {
        const int arraySize = 4;
        Animal* animals[arraySize];

        // Fill array with half dogs and half cats
        for (int i = 0; i < arraySize; i++)
        {
            if (i < arraySize / 2)
            {
                std::cout << "\nCreating Dog " << i << std::endl;
                animals[i] = new Dog();
            }
            else
            {
                std::cout << "\nCreating Cat " << i << std::endl;
                animals[i] = new Cat();
            }
        }

        // Delete all animals
        std::cout << "\nDeleting all animals" << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            delete animals[i];
        }
    }

    std::cout << "\n=== Testing deep copy ===" << std::endl;
    {
        // Test deep copy with Dog
        Dog originalDog;
        originalDog.getBrain()->setIdea(0, "I love bones!");

        originalDog.getBrain()->setIdea(1, "I want to chase cats!");

        // Test copy constructor
        Dog copiedDog(originalDog);
        std::cout << "Original dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copied dog idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

        // Modify copied dog to prove deep copy
        copiedDog.getBrain()->setIdea(0, "I hate bones!");
        std::cout << "After modification:" << std::endl;
        std::cout << "Original dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
        std::cout << "Modified copied dog idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;
    }

    std::cout << "\n=== Basic test from subject ===" << std::endl;
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        delete j;
        delete i;
    }

    return 0;
}
