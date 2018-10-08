// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp >= 0) MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
	BitField=bf;
}

TSet::operator TBitField()
{
	return (TBitField)*this;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if ((Elem<0) || (Elem>MaxPower)) throw "Error!!!";
  if (BitField.GetBit(Elem)) return 1;
	else return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem<0) || (Elem>MaxPower)) throw "Error!!!";
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem<0) || (Elem>MaxPower)) throw "Error!!!";
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;

	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (BitField == s.BitField)
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s) return 0;
	else return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(BitField | s.BitField);;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem<0) || (Elem>MaxPower)) throw "Error!!!";
	BitField.SetBit(Elem);
  return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem<0) || (Elem>MaxPower)) throw "Error!!!";
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp=*this;
	tmp.BitField=~tmp.BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int num;
	istr >> num;
	while ((num >= 0) && (num < s.MaxPower))
	{
		s.InsElem(num);
		istr >> num;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i)) ostr << i << " ";
	return ostr;
}
