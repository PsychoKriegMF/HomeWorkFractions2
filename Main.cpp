#include <iostream>
#include <cmath>


template <typename T>
class Fractions {
public:
	Fractions(): numerator_(0), denominator_(1){}

	Fractions(T num, T den)
	{
		if (den == 0)
		{
			throw - 1;
		}
		numerator_ = num;
		denominator_ = den;
	}
	// Методы доступа к полям
	T getNumerator()const { return numerator_; }
	T getDenominator()const { return denominator_; }

	// Методы изменения полей
	void setNumerator(T num) { numerator_ = num; }
	void setDenumerator(T den) { denominator_ = den; }
	
	//Конструкторы для создания дроби из целых чисел и чисел с плавающей запятой
	explicit Fractions(int integer) : numerator_(integer), denominator_(1) {}

	explicit Fractions(double num)
	{
		int sign = (num < 0) ? -1 : 1; // определяем знак числа
		num = std::abs(num); // для работы с положительными чилами 

		const double epsilon = 1e9; // для определения погрешности 
		int wholePart = static_cast<int>(num); // отбрасываем дроную часть 
		double fractionPart = num - wholePart; // вычисляем дробную часть 

		int gcd = gcd(static_cast<int>(fractionPart * 1e9), 1e9);  // вычисление наибольшего общего делителя
		numerator_ = (wholePart * 1e9 + static_cast<int>(fractionPart * 1e9)) / gcd * sign; // вычисление числителя
		denominator_ = 1e9 / gcd; //вычисление знаменателя
	}

	// операторы математики
	Fractions operator+(const Fractions& other) {
		T num = numerator_ * other.denominator_ + denominator_ * other.numerator_;
		T den = denominator_ * other.denominator_;
		return Fractions(num, den);
	}

	Fractions operator- (const Fractions& other) {
		T num = numerator_ * other.denominator_ - other.numerator_ * denominator_;
		T den = denominator_ * other.denominator_;
		return Fractions(num, den);
	}

	Fractions operator / (const Fractions& other) {
		T num = numerator_ * other.denominator_;
		T den = denominator_ * other.numerator_;
		return Fractions(num, den);
	}

	Fractions operator*(const Fractions& other) {
		T num = numerator_ * other.numerator_;
		T den = denominator_ * other.denominator_;
		return Fractions(num, den);
	}

	Fractions operator +() {
		return Fractions(numerator_, denominator_);
	}

	Fractions operator -() {
		return Fractions(-numerator_, denominator_);
	}

	Fractions& operator ++() {
		numerator_ += denominator_;
		return*this;
	}

	Fractions& operator--() {
		numerator_ = numerator_ - denominator_;
		return*this;
	}

	// операторы работы с потоками
	friend std::ostream& operator << (std::ostream& out, const Fractions& fraction)
	{
		out << fraction.numerator_ << '/' << fraction.denominator_;
		return out;
	}
	friend std::istream& operator >> (std::istream& in, Fractions& fraction)
	{
		in >> fraction.numerator_;
		in.ignore();
		in >> fraction.denominator_;
		return in;
	}

	// методы предикаты
	bool CorrectFraction() 
	{
		if (denominator_ > numerator_)
			return true;
		else
			return false;
	}

	bool InCorrectFraction() 
	{
		if (numerator_ > denominator_)
			return true;
		else
			return false;
	}

	bool IntegerFraction() 
	{
		if (numerator_ == denominator_) {
			return true;
		}
		else
			return false;
	}

	// методы предоставляющие данные из дроби
	int FullPart() 
	{
		int full;
		return full = numerator_ / denominator_;;
	}

	void FractionalPart() 
	{
		int num_ = numerator_ % denominator_;
		std::cout << num_ << '/' << denominator_;
	}

	void Reverse()
	{
		std::swap(numerator_, denominator_);
		std::cout << numerator_ << '/' << denominator_;
	}
private:
	T numerator_;
	T denominator_;
};

int main() {
	setlocale(LC_ALL, "ru");

	Fractions<int> fra1;
	Fractions<int> fra2;

	std::cout << "Введите дробь 1 -> ";
	std::cin >> fra1;
	std::cout << fra1;
	std::cout << std::endl;

	std::cout << "Введите дробь 2 -> ";
	std::cin >> fra2;
	std::cout << fra2;
	std::cout << std::endl;

	Fractions<int> Sum = fra1 + fra2;
	std::cout << "Сумма = " << Sum;

	Fractions<int> Dif = fra1 - fra2;
	std::cout << std::endl;

	std::cout << "Разность = " << Dif;
	Fractions<int> Def = fra1 / fra2;
	std::cout << std::endl;

	std::cout << "Частное = " << Def;
	Fractions<int> Mult = fra1 * fra2;
	std::cout << std::endl;

	std::cout << "Произведение = " << Mult << std::endl;

	++fra1;
	std::cout << fra1 << std::endl; 
	
	--fra1;
	std::cout << fra1 << std::endl; 
	

	return 0;
}