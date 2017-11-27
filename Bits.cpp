/*
 * Bits.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */

#include "Bits.h"

typedef unsigned int uint;

Bits::Bits()
{
	size_ = 0;
	bits_ = nullptr;
}

Bits::Bits(const Bits& other)
{
	size_ = other.size_;
	bits_ = new unsigned long[other.size_];
	for (int i = 0; i < size_; i++){
		bits_[i] = other.bits_[i];
	}
}

Bits::Bits(Bits&& other)
{
	if (this != &other){
		size_ = other.size_;
		bits_ = other.bits_;
	
		other.size_ = 0;
		other.bits_ = nullptr;
	}
	
}

Bits::~Bits() 
{
	delete[] bits_;
	size_ = 0;
}

void Bits::set(unsigned int loc) 
{
	if (loc > 0){
		int pos = (loc - 1) / 64;
		int bit = ((loc - 1) % 64);
		if (size_ > pos){
			
			bits_[pos] |= ulong_one << bit;
		}
		else {
			int newSize = pos + 1;
			int oldSize = size_;
			unsigned long *temp = new unsigned long[newSize];
			for (int i = 0; i < oldSize; i++){
				temp[i] = bits_[i];
			}
			for (int i = oldSize; i < newSize; i++){
				if (i == newSize -1){
					temp[i] = ulong_one << bit;
				}
				else {
					temp[i] = 0U;
				}
			}
			delete[] bits_;
			size_ = newSize;
			bits_ = new unsigned long[newSize];
			bits_ = temp;
		}
	}
}

void Bits::unset(unsigned int loc) 
{
	if (loc > 0){
		int pos = (loc - 1) / 64;
		if (size_ > pos){
			int bit = ((loc - 1) % 64);
			bits_[pos] &= ~(ulong_one << bit);
		}
	}
	
}

bool Bits::operator[](uint loc) const 
{
	if (loc > 0){
		int pos = (loc - 1) / 64;
		int bit = ((loc - 1) % 64);
		if (size_ > pos){
			return (bits_[pos] >> bit) & ulong_one;	
		}
	}
	return false;
}

Bits& Bits::operator=(const Bits& other) 
{
	if (this != &other){	
		delete[] bits_;
		bits_ = new unsigned long[other.size_];
		size_ = other.size_;
		for (int i = 0; i < size_; i++){
			bits_[i] = other.bits_[i];
		}
	}
	return *this;
}

Bits& Bits::operator=(Bits&& other) 
{
	if (this != &other){
		size_ = 0;
		delete[] bits_;

		size_ = other.size_;
		bits_ = new unsigned long[other.size_];
		for (int i = 0; i < size_; i++){
			bits_[i] = other.bits_[i];
		}
		
		other.size_ = 0;
		other.bits_ = nullptr;
	}
	return *this;
}

Bits Bits::operator|(const Bits& other) const 
{
	if (this != &other){
		if (size_ >= other.size_){
			Bits out = *this;
			for (int i = 0; i < size_; i++){
				out.bits_[i] |= other.bits_[i];
			}
			return out;
		}
		else {
			Bits out = other;
			for (int i = 0; i < size_; i++){
				out.bits_[i] |= bits_[i];
			}
			return out;
		}
	}
	
	return *this;
}

Bits Bits::operator&(const Bits& other) const 
{
	if (this != &other){
		Bits out = *this;
		for (int i = 0; i < size_; i++){
			out.bits_[i] &= other.bits_[i];
		}
		return out;
	}
	
	return *this;
}

unsigned int Bits::size() const 
{
	int count = 0;
	for (int i = 0; i < size_ ; i++){
		unsigned long n = bits_[i];
		while (n){
			count += n & 1;
			n >>= 1;
		}
	}
	return count;
}

unsigned int Bits::maxset() const 
{
	int index = 0;
	for (int i = 0; i < size_ ; i++){
		unsigned long n = bits_[i];
		int count = 0;
		while (n){
			count++;
			if(n & 1)
				index = (64 * i) + count;
			
			n >>= 1;
			
		}
	}
	return index;
}

Bits::operator bool() const 
{
	for (int i = 0; i < size_; i++){
		if (bits_[i] > 0)return true;
	}
	return false;
}

Bits::operator unsigned long() const 
{
	return (size_ >=1) ? bits_[0] : 0;
}


// DO NOT CHANGE
// DO NOT CHANGE
// DO NOT CHANGE
void Bits::set_(unsigned long* bits, unsigned int size) 
{
	if (bits_) {
		delete [] bits_;
	}
	bits_ = bits;
	size_ = size;
}


unsigned long* Bits::get_(unsigned int& size) 
{
	size = size_;
	return bits_;
}
