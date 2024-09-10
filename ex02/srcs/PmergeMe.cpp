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

const int K = 5;

PmergeM::PmergeM(void) { return; }

PmergeM::PmergeM(PmergeM const &) { return; }

PmergeM::~PmergeM(void) { return; }

PmergeM PmergeM::operator=(PmergeM const &) { return (*this); }

void printDeque(std::deque<int>& nbrDeque, int start, int size)
{
    for (int i = start; i < size; i++)
    {
        std::cout << nbrDeque[i] << " ";
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

// Función para el Insertion Sort usando deque
void insertionSort(std::deque<int>& A, int start, int end)
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

// Función para el Merge usando deque
void merge(std::deque<int>& A, int leftStart, int leftEnd, int rightEnd)
{
    int sizeLeft = leftEnd - leftStart + 1;
    int sizeRight = rightEnd - leftEnd;

    std::deque<int> LA(sizeLeft);
    std::deque<int> RA(sizeRight);

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

// Función para ordenar (mezcla o inserción) usando deque
void sort(std::deque<int>& A, int start, int end)
{
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
}

void PmergeM::process(char **argv) throw(std::invalid_argument, std::runtime_error)
{
    std::deque<int> nbrDeque;
    
	clock_t start = clock();
    while (*argv)
    {
        if (isValid((*argv)) == false)
                throw std::invalid_argument("Invalid arguments");
        
        long value = strtol(*argv, NULL, 10);
        nbrDeque.push_back(static_cast<int>(value));

        argv++;
    }

    
    std::cout << "Before ";
    printDeque(nbrDeque, 0, nbrDeque.size());
    
    //mergeInsertSort(nbrDeque);
    sort(nbrDeque, 0, nbrDeque.size() - 1);

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "After  ";
    printDeque(nbrDeque, 0, nbrDeque.size());

    std::cout << "Time to process a range of " << nbrDeque.size()  << " elements with std::deque<int> :"  << elapsed * 10 << " us" << std::endl;
}