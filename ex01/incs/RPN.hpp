/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:05:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/09 13:05:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <limits>
#include <list>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <iostream>
#include <exception>

class RPN
{
    public:
        static int process(std::string const &expression) throw(std::invalid_argument, std::overflow_error, std::underflow_error);

    private:
        RPN(void);
        RPN(RPN const &);
        ~RPN(void);

        RPN operator=(RPN const &);
};

#endif