/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:04:57 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/09 13:04:57 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/RPN.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
	{
		std::cout << "Usage: RPN expression" << std::endl;
		return (2);
	}

	try
	{
		std::cout << RPN::process(argv[1]) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}