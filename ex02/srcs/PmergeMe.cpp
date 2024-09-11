/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:57:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/10 21:15:39 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

#include <iomanip>

const int K = 7;

PmergeM::PmergeM(void) { return; }

PmergeM::PmergeM(PmergeM const &) { return; }

PmergeM::~PmergeM(void) { return; }

PmergeM PmergeM::operator=(PmergeM const &) { return (*this); }

template <typename T>
void printContainer(T& container, int start, int size)
{
    for (int i = start; i < size; i++)
    {
        std::cout << container[i] << " ";
    }
    std::cout << std::endl;
}

bool isValid(char * str)
{
    if (str == NULL || *str == '\0')
        return false;

    char* endptr;
    long value = strtol(str, &endptr, 10);

    return (*endptr == '\0' && value >= 0 && value <= INT_MAX);
}

template <typename T>
void insertionSort(T& A, int start, int end)
{
    for (int i = start; i < end; i++) {
        int tempVal = A[i + 1];
        int j = i + 1;

        while (j > start && A[j - 1] > tempVal) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tempVal;
    }
}

template <typename T>
void merge(T& A, int leftStart, int leftEnd, int rightEnd)
{
    int sizeLeft = leftEnd - leftStart + 1;
    int sizeRight = rightEnd - leftEnd;

    T LA(sizeLeft);
    T RA(sizeRight);

    std::copy(A.begin() + leftStart, A.begin() + leftEnd + 1, LA.begin());
    std::copy(A.begin() + leftEnd + 1, A.begin() + rightEnd + 1, RA.begin());

    int LI = 0, RI = 0;

    for (int i = leftStart; i <= rightEnd; i++)
    {
        if (RI == sizeRight)
        {
            A[i] = LA[LI++];
        }
        else if (LI == sizeLeft)
        {
            A[i] = RA[RI++];
        }
        else if (RA[RI] > LA[LI])
        {
            A[i] = LA[LI++];
        }
        else
        {
            A[i] = RA[RI++];
        }
    }
}

template <typename T>
double sort(T& A, int start, int end)
{
    clock_t startTime = clock();
    if (end - start > K)
    {
        int mid = start + (end - start) / 2;
        sort(A, start, mid);
        sort(A, mid + 1, end);
        merge(A, start, mid, end);
    }
    else
    {
        insertionSort(A, start, end);
    }
    clock_t endTime = clock();
    double elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;
    return elapsed;
}

void PmergeM::process(char **argv) throw(std::invalid_argument, std::runtime_error)
{
    std::deque<int> nbrDeque;
    std::vector<int> nbrVector;

    while (*argv)
    {
        if (isValid((*argv)) == false)
            throw std::invalid_argument("Invalid arguments");

        long value = strtol(*argv, NULL, 10);
        nbrDeque.push_back(static_cast<int>(value));
        nbrVector.push_back(static_cast<int>(value));
        argv++;
    }

    std::cout << "Before ";
    printContainer(nbrDeque, 0, nbrDeque.size());

    double timeDeque = sort(nbrDeque, 0, nbrDeque.size() - 1);
    double timeVector = sort(nbrVector, 0, nbrVector.size() - 1);

    std::cout << "After  ";
    printContainer(nbrVector, 0, nbrVector.size());

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Time to process a range of " << nbrDeque.size()  << " elements with std::deque<int> :  "  << timeDeque << " us" << std::endl;
    std::cout << "Time to process a range of " << nbrVector.size()  << " elements with std::vector<int> : "  << timeVector << " us" << std::endl;
}