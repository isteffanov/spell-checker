#include "gtest/gtest.h"
#include"ULAShadow.h"

TEST(GenerateBitVectors, WithTolerance0) {
	vector<bit_vector_t> result = ULAShadow::generate_bit_vectors_from_tolerance(0);
	vector<bit_vector_t> expected = { {} };

	EXPECT_EQ(result, expected);
}

TEST(GenerateBitVectors, WithTolerance1) {
	vector<bit_vector_t> result = ULAShadow::generate_bit_vectors_from_tolerance(1);
	vector<bit_vector_t> expected = { {}, {0}, {1} };

	EXPECT_EQ(result, expected);
}

TEST(GenerateBitVectors, WithTolerance2) {
	vector<bit_vector_t> result = ULAShadow::generate_bit_vectors_from_tolerance(2);
	vector<bit_vector_t> expected = { 
		{},
		{0}, {1},
		{0, 0}, {0, 1}, {1, 0}, {1, 1},
	};

	EXPECT_EQ(result, expected);
}

TEST(GenerateBitVectors, WithTolerance3) {
	vector<bit_vector_t> result = ULAShadow::generate_bit_vectors_from_tolerance(3);
	vector<bit_vector_t> expected = {
		{},
		{0}, {1},
		{0, 0}, {0, 1}, {1, 0}, {1, 1},
		{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
	};

	EXPECT_EQ(result, expected);
}

TEST(TestGenerateULAShadow, WithTolerance0) {

	ULAShadow ula_shadow = ULAShadow(0);

	vector<vector<ULAState>> expected_matrix = { { ULAState(-1, 0), ULAState(-1, 0), ULAState(0, 1)} };
	vector<bit_vector_t> expected_bit_vectors = { {}, {0}, {1} };
	vector<int> expected_max_i_minus_e = { 0 };

	EXPECT_EQ(ula_shadow.matrix, expected_matrix);
	EXPECT_EQ(ula_shadow.bit_vectors, expected_bit_vectors);
	EXPECT_EQ(ula_shadow.max_i_minus_e, expected_max_i_minus_e);
}

TEST(TestGenerateULAShadow, WithTolerance1) {

	ULAShadow ula_shadow = ULAShadow(1);

    vector<vector<ULAState>> expected_matrix = {
        {   ULAState(1, 0),
            ULAState(2, 0),
            ULAState(0, 1),
            ULAState(2, 0),
            ULAState(4, 0),
            ULAState(0, 1),
            ULAState(0, 1),
            ULAState(2, 0),
            ULAState(2, 0),
            ULAState(4, 0),
            ULAState(4, 0),
            ULAState(0, 1),
            ULAState(0, 1),
            ULAState(0, 1),
            ULAState(0, 1)
        },
        {   ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState( 1, 1),
            ULAState( 1, 1),
            ULAState( 1, 1)
        },
        {   ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState( 1, 2),
            ULAState( 1, 1),
            ULAState( 2, 1),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 2),
            ULAState( 1, 2),
            ULAState( 1, 1),
            ULAState( 1, 1),
            ULAState( 2, 1),
            ULAState( 2, 1)
        },
        {   ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState( 1, 3),
            ULAState(-1, 0),
            ULAState( 1, 3),
            ULAState( 1, 1),
            ULAState( 3, 1),
            ULAState( 1, 1),
            ULAState( 3, 1)
        },
        {   ULAState(-1, 0),
            ULAState(-1, 0),
            ULAState( 1, 1),
            ULAState(-1, 0),
            ULAState( 1, 2),
            ULAState( 1, 1),
            ULAState( 2, 1),
            ULAState(-1, 0),
            ULAState( 1, 3),
            ULAState( 1, 2),
            ULAState( 2, 2),
            ULAState( 1, 1),
            ULAState( 3, 1),
            ULAState( 2, 1),
            ULAState( 4, 1)
        }
    };

	EXPECT_EQ(ula_shadow.matrix, expected_matrix);
}

/*

    {  result                                                                         v                                                                                  v                v                                                                         
        { ULAState(1, 0),  ULAState(2, 0),  ULAState(0, 1), ULAState(2, 0),  ULAState(2, 0),  ULAState(0, 1), ULAState(0, 1), ULAState(2, 0),  ULAState(2, 0),  ULAState(2, 0),  ULAState(2, 0),  ULAState(0, 1), ULAState(0, 1), ULAState(0, 1), ULAState(0, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(1, 1), ULAState(1, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 1), ULAState(2, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 2),  ULAState(1, 1), ULAState(1, 1), ULAState(2, 1), ULAState(2, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 3),  ULAState(-1, 0), ULAState(1, 3),  ULAState(1, 1), ULAState(3, 1), ULAState(1, 1), ULAState(3, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 1), ULAState(2, 1), ULAState(-1, 0), ULAState(1, 3),  ULAState(1, 2),  ULAState(2, 2),  ULAState(1, 1), ULAState(3, 1), ULAState(2, 1), ULAState(4, 1) } }

    { expected  
        { ULAState(1, 0),  ULAState(2, 0),  ULAState(0, 1), ULAState(2, 0),  ULAState(4, 0),  ULAState(0, 1), ULAState(0, 1), ULAState(2, 0),  ULAState(2, 0),  ULAState(4, 0),  ULAState(4, 0),  ULAState(0, 1), ULAState(0, 1), ULAState(0, 1), ULAState(0, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(1, 1), ULAState(1, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 1), ULAState(2, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 2),  ULAState(1, 1), ULAState(1, 1), ULAState(2, 1), ULAState(2, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 3),  ULAState(-1, 0), ULAState(1, 3),  ULAState(1, 1), ULAState(3, 1), ULAState(1, 1), ULAState(3, 1) }, 
        { ULAState(-1, 0), ULAState(-1, 0), ULAState(1, 1), ULAState(-1, 0), ULAState(1, 2),  ULAState(1, 1), ULAState(2, 1), ULAState(-1, 0), ULAState(1, 3),  ULAState(1, 2),  ULAState(2, 2),  ULAState(1, 1), ULAState(3, 1), ULAState(2, 1), ULAState(4, 1) } }
*/