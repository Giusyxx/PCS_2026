#pragma once
#include <iostream>
#include <concepts>
#include <numeric>

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
	
	void semplifica() {
		if (den_== 0) return;
		
		I mcd = std::gcd(num_, den_);
		num_ /= mcd;
		den_ /= mcd;
		
		if (den_ < 0) { // sposta il segno - al num
			num_ = -num_;
			den_ = -den_;
		}
	}
		
		
public:
	rational () //costruttore di default
		: num_(0), den_(1) 
	{} 
		
	rational(I num, I den) // costruttore user-defined
		: num_(num), den_(den) 
	{
		if (den_ == 0) {
			if (num_ == 0) {
				// caso 0/0 --> NaN
				num_ = 0; den_ = 0;
			} else {
				// caso num/0 --> Inf
				if (num_ > 0) {
					num_ = 1; // Inf
				} else {
					num_ = -1; // -Inf
				}
				den_ = 0;
			}
		} else { 
			semplifica ();
		}
		
	}
	
	// Restituiscono i valori di num e den
	I num() const { return num_; }
	I den() const { return den_; }
	
	// Somma : (a/b) + (c/d) = (ad + bc)/ (bd)
	rational& operator+=(const rational& other) {
		
		// Se uno dei due è NaN, il risultato è NaN
		if ((den_ == 0 && num_ == 0) || (other.den_ == 0 && other.num_ == 0)) {
			num_ = 0; den_ = 0;
			return *this;
		}
		// se uno dei due è Inf, il risultato è Inf
		if (den_ == 0 || other.den_ == 0 ) {
			if (den_ == 0 && other.den_ == 0) { // inf + inf
				if (num_ != other.num_ ) { // + Inf +(-Inf) oppure -Inf + (+Inf) = NaN
					num_ = 0; den_ = 0;
				}
			} else if (den_!= 0) {
				num_ = other.num_;
				den_ = 0;
			}
			
			return *this;
		}
					
		// num_ e den_ finiti
		num_ = num_ * other.den_ + other.num_ * den_;
		den_ = den_ * other.den_;
		
		semplifica();
		return *this;
	}
	
	// Prodotto
	rational& operator*=(const rational& other) {
		
		// se uno dei due è NaN , il risulatto è NaN
		if ((den_ == 0 && num_== 0) || (other.den_ == 0 && other.num_ == 0)) {
			num_ = 0; den_ = 0;
			return *this;
		}
		
		// 0 * inf oppure Inf * 0 --> NaN
		if (( num_ == 0 && other.den_ == 0) || ( den_ == 0 && other.num_ == 0)) {
			num_ = 0; den_ = 0;
			return *this;
		}
		 // Inf * finito --> Inf
		if (den_ == 0 || other.den_ == 0) {
			// se sono concordi --> + Inf
			if ((num_ > 0 && other.num_ > 0) || (num_ < 0 && other.num_ < 0)) {
				num_ = 1;
			} else { // se sono discordi--> -Inf
				num_ = -1;
			}
			den_ = 0;
			return *this; 
		}
		
		// finito * finito 
		num_ *= other.num_;
		den_ *= other.den_;
		
		semplifica();
		return *this;
	}
	
	// Sottrazione
	rational& operator-=(const rational& other) {
		rational neg_other(-other.num(), other.den());
		*this += neg_other;
		return *this;
	}
	
	//Divisione
	rational& operator/=(const rational& other) {
		rational reciproco(other.den(), other.num());
		*this *= reciproco;
		return *this;
	}
	
	
	// operatori bianri
	
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;
	}
	
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;
	}
	
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
		
};


template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r) {
	if (r.den() == 0) {
		if (r.num() == 0) os << "NaN";
		else {
			// se num è > 0 --> Inf
			if (r.num() > 0) os << "Inf";
			else // se num < 0 --> -Inf
			os << "-Inf";
		}
	} else {
		os << r.num() << "/" << r.den();
	}
	return os;
}