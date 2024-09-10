/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:50:09 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/10 20:47:03 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/PmergeMe.hpp"

//std::contenedor<tipo de dato>::iterator nombre;

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 3001)
	{
		std::cout << "Usage: RPN arg1 arg2 ...(max 3000)" << std::endl;
		return (2);
	}

	try
	{
		//(void)argv;
		PmergeM::process(++argv);
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
