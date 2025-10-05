// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem >= MaxPower || Elem < 0)
		throw("Неправильный индекс");

	return BitField.GetBit(Elem);

}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw("Неправильный индекс");

	return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw("Неправильный индекс");

	return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;

	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	if (MaxPower != s.MaxPower || BitField != s.BitField)
		return 0;
	else
		return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
  return (*this == s) == 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
  int mp = (MaxPower >= s.MaxPower) ? MaxPower: s.MaxPower;
  int mm = (MaxPower == mp) ? s.MaxPower : MaxPower;
  TBitField mpp = (MaxPower == mp) ? BitField : s.BitField;

  TSet bf(mp);
  for (int i = 0; i < mm; i++) 
	  if (BitField.GetBit(i) || s.IsMember(i))
		  bf.InsElem(i);

  if (mp != mm) {
	  for (int i = mm; i < mp; i++)
		  if (mpp.GetBit(i))
			  bf.InsElem(i);
  }

  return bf;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem >= MaxPower || Elem < 0)
		throw("Неправильный индекс");

	TSet bf(MaxPower);

	for (int i = 0; i < MaxPower; i++)
		if (BitField.GetBit(i))
			bf.InsElem(i);
	bf.InsElem(Elem);
  return bf;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem >= MaxPower || Elem < 0)
		throw("Неправильный индекс");

	TSet bf(MaxPower);

	for (int i = 0; i < MaxPower; i++)
		if (BitField.GetBit(i))
			bf.InsElem(i);
	bf.DelElem(Elem);
	return bf;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	int mp = (MaxPower >= s.MaxPower) ? MaxPower : s.MaxPower;
	int mm = (MaxPower == mp) ? s.MaxPower : MaxPower;
	TBitField mpp = (MaxPower == mp) ? BitField : s.BitField;

	TSet bf(mp);
	for (int i = 0; i < mm; i++)
		if (BitField.GetBit(i) && s.IsMember(i))
			bf.InsElem(i);

	return bf;
}

TSet TSet::operator~(void) // дополнение
{
  TSet bf(MaxPower);
  for (int i = 0; i < MaxPower; i++)
	  if (BitField.GetBit(i) == 0)
		  bf.InsElem(i);
  return bf;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{

  return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	return ostr;
}
