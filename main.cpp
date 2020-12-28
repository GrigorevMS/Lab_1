#define TEST

#ifdef TEST

#include "tbitfield.h"
#include "tset.h"

int main() {
	// 1. TbitField tests
	{
		std::cout << "TbitField tests:" << std::endl;
		const int N = 20;
		TBitField bitField(N);
		std::cout << "Test 1. bitField.GetLength(). Expected: " << N << " , actual: " << bitField.GetLength() << std::endl;

		TBitField bitField2(bitField);
		std::cout << "Test 2. bitField2 == bitField. Expected: " << true << " , actual: " << (bitField2 == bitField) << std::endl;

		for (int i = 0; i < N / 2; i++) {
			bitField.SetBit(i * 2);
			bitField.ClrBit(i * 2 + 1);
		}
		std::cout << "Test 3. bitField2 == bitField. Expected: " << false << " , actual: " << (bitField2 == bitField) << std::endl;

		std::cout << "Test 4. bitField.GetBit(). Expected: " << 1010 << " , actual: "
			<< bitField.GetBit(0) << bitField.GetBit(1) << bitField.GetBit(16) << bitField.GetBit(17) << std::endl;

		const int N2 = 40;
		TBitField bitField3(N2);
		bitField3 = bitField;
		std::cout << "Test 5. bitField3 == bitField. Expected: " << true << " , actual: " << (bitField3 == bitField) << std::endl;

		const int N3 = 10;
		TBitField bitField4(N3);
		for (int i = 0; i < N3; i++) {
			bitField4.SetBit(i);
		}
		std::cout << "Test 6. bitField4 | bitField." << std::endl
			<< "Expected: 11111111111010101010" << std::endl
			<< "Actual:   " << (bitField4 | bitField) << std::endl;

		std::cout << "Test 7. bitField4 & bitField." << std::endl
			<< "Expected: 10101010100000000000" << std::endl
			<< "Actual:   " << (bitField4 & bitField) << std::endl;

		std::cout << "Test 8. ~bitField." << std::endl
			<< "Expected: 01010101010101010101" << std::endl
			<< "Actual:   " << (~bitField) << "\n\n";
	}

	// 2. TSet tests
	{
		std::cout << "TSet tests:" << std::endl;
		const int N = 20;
		TSet set(N);
		std::cout << "Test 1. set.GetMaxPower(). Expected: " << N << " , actual: " << set.GetMaxPower() << std::endl;

		TSet set2(set);
		std::cout << "Test 2. set2 == set. Expected: " << true << " , actual: " << (set2 == set) << std::endl;

		for (int i = 0; i < N / 2; i++) {
			set.InsElem(i * 2);
			set.DelElem(i * 2 + 1);
		}
		std::cout << "Test 3. set2 == set. Expected: " << false << " , actual: " << (set2 == set) << std::endl;

		TBitField bitField(N);
		for (int i = 0; i < N / 2; i++) {
			bitField.SetBit(i * 2);
			bitField.ClrBit(i * 2 + 1);
		}
		TSet set3(bitField);
		std::cout << "Test 4. set3 == set. Expected: " << true << " , actual: " << (set3 == set) << std::endl;

		std::cout << "Test 5. set.IsMember(). Expected: " << 1010 << " , actual: "
			<< set.IsMember(0) << set.IsMember(1) << set.IsMember(16) << set.IsMember(17) << std::endl;

		const int N2 = 40;
		TSet set4(N2);
		set4 = set;
		std::cout << "Test 6. set4 == set. Expected: " << true << " , actual: " << (set4 == set) << std::endl;

		std::cout << "Test 7. set + 9." << std::endl
			<< "Expected: {  0, 2, 4, 6, 8, 9, 10, 12, 14, 16, 18 }" << std::endl
			<< "Actual:   " << (set + 9) << std::endl;

		std::cout << "Test 8. set - 8." << std::endl
			<< "Expected: {  0, 2, 4, 6, 10, 12, 14, 16, 18 }" << std::endl
			<< "Actual:   " << (set - 8) << std::endl;

		const int N3 = 10;
		TSet set5(N3);
		for (int i = 0; i < N3; i++) {
			set5.InsElem(i);
		}
		std::cout << "Test 9. set5 + set." << std::endl
			<< "Expected: {  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18 }" << std::endl
			<< "Actual:   " << (set5 + set) << std::endl;

		std::cout << "Test 10. set5 * set." << std::endl
			<< "Expected: {  0, 2, 4, 6, 8 }" << std::endl
			<< "Actual:   " << (set5 * set) << std::endl;

		std::cout << "Test 11. ~set." << std::endl
			<< "Expected: {  1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }" << std::endl
			<< "Actual:   " << (~set) << std::endl;
	}

	return 0;
}

#else

#endif