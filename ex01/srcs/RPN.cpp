/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:05:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/09 13:05:56 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/RPN.hpp"

RPN::RPN(void) { return; }

RPN::RPN(RPN const &) { return; }

RPN::~RPN(void) { return; }

RPN RPN::operator=(RPN const &) { return (*this); }

int RPN::process(std::string const &expression) throw(std::invalid_argument, std::overflow_error, std::underflow_error)
{

	std::string const nbrtokens("0123456789");
    std::string const oprtokens("+-/*");
	std::stringstream sstream(expression);
	std::string str;
	std::stack<int, std::list<int> > stack;
    int item;

    while (sstream >> str)
    {
        if (str.length() > 1 || (nbrtokens.find(str.at(0)) == std::string::npos && oprtokens.find(str.at(0)) == std::string::npos))
			throw std::invalid_argument("Error: invalid expression");

        if (nbrtokens.find(str.at(0)) != std::string::npos)
        {
            //Is a nbr
            stack.push(str.at(0) - '0');
        }
        else
        {
            //Is a operator
            item = stack.top();
            stack.pop();

            switch (str.at(0))
            {
                case '+':
                    if (item > 0 && stack.top() > std::numeric_limits<int>::max() - item)
					    throw std::overflow_error("Error: overflow");
				    else if (item < 0 && stack.top() < std::numeric_limits<int>::min() - item)
					    throw std::underflow_error("Error: underflow");

				    item = stack.top() + item;

				    break;


                case '-':
                    if (item < 0 && stack.top() > std::numeric_limits<int>::max() + item)
					    throw std::overflow_error("Error: overflow");
				    else if (item > 0 && stack.top() < std::numeric_limits<int>::min() + item)
					    throw std::underflow_error("Error: underflow");

				    item = stack.top() - item;

				    break;


                case '/':
                    if (item == 0)
					    throw std::invalid_argument("Error: division by zero");
				    else if (stack.top() == std::numeric_limits<int>::min() && item == -1)
					    throw std::overflow_error("Error: overflow");

				    item = stack.top() / item;

				    break;


                default:

                    if ((stack.top() == -1 && item == std::numeric_limits<int>::min()) || (item == -1 && stack.top() == std::numeric_limits<int>::min()))
					    throw std::overflow_error("Error: overflow");
				    else if (stack.top() > 0)
                    {
                        if (item > 0 && stack.top() > std::numeric_limits<int>::max() / item)
                            throw std::overflow_error("Error: overflow");
                        else if (item < -1 && stack.top() > std::numeric_limits<int>::min() / item)
                            throw std::underflow_error("Error: underflow");
                    }
                    else if (stack.top() < 0)
                    {
                        if (item < 0 && stack.top() < std::numeric_limits<int>::max() / item)
                            throw std::overflow_error("Error: overflow");
                        else if (item > 0 && stack.top() < std::numeric_limits<int>::min() / item)
                            throw std::underflow_error("Error: underflow");
                    }

				    item = stack.top() * item;

				    break;
            }

            stack.pop();
            stack.push(item);

            //More than 2 nbrs
            if (stack.size() > 1)
		        throw std::invalid_argument("Error: invalid expression");
        }
    }

    item = stack.top();
    stack.pop();
    return (item);
}