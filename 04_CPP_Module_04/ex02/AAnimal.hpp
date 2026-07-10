/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:46:25 by alcarden          #+#    #+#             */
/*   Updated: 2025/03/02 16:36:55 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>
#include "Brain.hpp"

class AAnimal {
protected:
    std::string type;

public:
    AAnimal();
    AAnimal(std::string type);
    AAnimal(const AAnimal &other);
    AAnimal &operator=(const AAnimal &other);
    virtual ~AAnimal();

    std::string getType() const;
    virtual void makeSound() const = 0; // Método virtual puro
    virtual Brain* getBrain() const;
};

#endif
