#include"tbitfield.h"
TBitField::TBitField(int len)
{
	if (len <= 0)
		throw false;
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	else
		throw false;
}

TBitField::TBitField(const TBitField& bf) // ����������� �����������
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	else
		throw false;
}

TBitField::~TBitField()
{
	if (pMem != NULL)
		delete pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
	return 0x01 << (n & 31);
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
	if (n > -1 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw false;
}

void TBitField::ClrBit(const int n) // �������� ���
{
	if (n > -1 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw false;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
	if (n > -1 && n < BitLen)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else
		throw false;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField& bf) // ������������
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	else
		throw false;
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // ���������
{
	int ans = 1;
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			ans = 0;
			break;
		}
	}
	return ans;
}

int TBitField::operator!=(const TBitField& bf) const // ���������
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // �������� "���"
{
	int len = (bf.BitLen > BitLen) ? bf.BitLen : BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // �������� "�"
{
	int len = (bf.BitLen > BitLen) ? bf.BitLen : BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // ���������
{
	int dif = MemLen * 32 - BitLen;
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = ~pMem[i];
	temp.pMem[MemLen - 1] &= ~(0xFFFFFFFF << (32 - dif));
	return temp;
}

// ����/�����

istream& operator>>(istream& istr, TBitField& bf) // ����
{
	int i = 0;
	char ch;
	do
	{
		istr >> ch;
	} while (ch != ' ');

	while (1)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1')
			bf.SetBit(i++);
		else
			break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // �����
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	return ostr;
}
