// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>
#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	BitLen = len;
	if (len < 0)
		throw std::out_of_range("Меньше 0");
	MemLen = (len / BITS_IN_ONE_MEM) + 1;

	pMem = new TELEM[MemLen];

	memset(pMem, 0, MemLen * sizeof(TELEM));

}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	
	pMem = new TELEM[MemLen];

	memcpy(pMem, bf.pMem, bf.MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{

	if (n >= BitLen || n < 0)
		throw std::out_of_range("Такого индекса нет");
	
	
	return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= BitLen || n < 0)
		throw std::out_of_range("Такого индекса нет");

	return TELEM(1) << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
		throw std::out_of_range("Такого индекса нет");

	pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw("Такого бита нет");

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	
	if (n < 0 || n >= BitLen)
		throw("Такого бита нет");

	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	pMem = new TELEM[MemLen];

	memcpy(pMem, bf.pMem, bf.MemLen * sizeof(TELEM));

	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen == bf.BitLen && MemLen == bf.MemLen) {
		
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
		
		return 1;
	}
	else
		return 0;
	
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if ((bf == *this) == 0)
		return 1;
	else
		return 0;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int n, k, d, l;
	
	if (MemLen > bf.MemLen) {
		n = bf.MemLen;
		k = MemLen;
		d = 0;
		l = BitLen;
	}
	else {
		n = MemLen;
		k = bf.MemLen;
		d = 1;
		l = bf.BitLen;
	}
	TBitField bf2(l);

	for (int i = 0; i < n; i++)
		bf2.pMem[i] = pMem[i] | bf.pMem[i];
	for (n; n < k; n++)
	{
		if (d == 0)
			bf2.pMem[n] = pMem[n];
		else
			bf2.pMem[n] = bf.pMem[n];
	}

	return bf2;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{

	int n, k, d, l;

	if (MemLen > bf.MemLen) {
		n = bf.MemLen;
		k = MemLen;
		d = 0;
		l = BitLen;
	}
	else {
		n = MemLen;
		k = bf.MemLen;
		d = 1;
		l = bf.BitLen;
	}
	TBitField bf2(l);

	for (int i = 0; i < n; i++)
		bf2.pMem[i] = pMem[i] & bf.pMem[i];
	for (n; n < k; n++)
	{
		if (d == 0)
			bf2.pMem[n] = 0;
		else
			bf2.pMem[n] = 0;
	}

	return bf2;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
		bf.pMem[i] = ~pMem[i];

//	for (int i = 0; i < BITS_IN_ONE_MEM - (BitLen % BITS_IN_ONE_MEM); i++)
//		bf.pMem[MemLen - 1] &= ~(TELEM(1) << ((BitLen + i) % BITS_IN_ONE_MEM));
	
	if ((BitLen % BITS_IN_ONE_MEM) > 0)
		bf.pMem[MemLen - 1] &= (TELEM(1) << (BitLen % BITS_IN_ONE_MEM)) - 1;

	return bf;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	string input;
	getline(istr, input);
	for (int i = 0; i < bf.BitLen; i++)
		bf.ClrBit(i);


	for (int i = 0; i < input.length(); i++) 
		if (input[i] == '1') 
			bf.SetBit(i);
  
  
  return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);

  return ostr;
}
