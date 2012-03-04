#ifndef INC_vcParserTokenTypes_hpp_
#define INC_vcParserTokenTypes_hpp_

/* $ANTLR 2.7.7 (2006-11-01): "vc.g" -> "vcParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API vcParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		LIFO = 4,
		PIPE = 5,
		UINTEGER = 6,
		DEPTH = 7,
		MEMORYSPACE = 8,
		UNORDERED = 9,
		LBRACE = 10,
		RBRACE = 11,
		CAPACITY = 12,
		DATAWIDTH = 13,
		ADDRWIDTH = 14,
		MAXACCESSWIDTH = 15,
		OBJECT = 16,
		COLON = 17,
		FOREIGN = 18,
		PIPELINE = 19,
		MODULE = 20,
		SIMPLE_IDENTIFIER = 21,
		EQUIVALENT = 22,
		LPAREN = 23,
		RPAREN = 24,
		OPEN = 25,
		DIV_OP = 26,
		ENTRY = 27,
		EXIT = 28,
		CONTROLPATH = 29,
		PLACE = 30,
		TRANSITION = 31,
		DEAD = 32,
		SERIESBLOCK = 33,
		PARALLELBLOCK = 34,
		BRANCHBLOCK = 35,
		MERGE = 36,
		BRANCH = 37,
		FORKBLOCK = 38,
		JOIN = 39,
		FORK = 40,
		DATAPATH = 41,
		PLUS_OP = 42,
		MINUS_OP = 43,
		MUL_OP = 44,
		SHL_OP = 45,
		SHR_OP = 46,
		UGT_OP = 47,
		UGE_OP = 48,
		EQ_OP = 49,
		ULT_OP = 50,
		ULE_OP = 51,
		NEQ_OP = 52,
		BITSEL_OP = 53,
		CONCAT_OP = 54,
		OR_OP = 55,
		AND_OP = 56,
		XOR_OP = 57,
		NOR_OP = 58,
		NAND_OP = 59,
		XNOR_OP = 60,
		SHRA_OP = 61,
		SGT_OP = 62,
		SGE_OP = 63,
		SLT_OP = 64,
		SLE_OP = 65,
		NOT_OP = 66,
		StoS_ASSIGN_OP = 67,
		StoU_ASSIGN_OP = 68,
		UtoS_ASSIGN_OP = 69,
		FtoS_ASSIGN_OP = 70,
		FtoU_ASSIGN_OP = 71,
		StoF_ASSIGN_OP = 72,
		UtoF_ASSIGN_OP = 73,
		FtoF_ASSIGN_OP = 74,
		BRANCH_OP = 75,
		SELECT_OP = 76,
		SLICE_OP = 77,
		ASSIGN_OP = 78,
		EQUIVALENCE_OP = 79,
		CALL = 80,
		INLINE = 81,
		IOPORT = 82,
		IN = 83,
		OUT = 84,
		LOAD = 85,
		FROM = 86,
		STORE = 87,
		TO = 88,
		PHI = 89,
		LBRACKET = 90,
		RBRACKET = 91,
		CONSTANT = 92,
		INTERMEDIATE = 93,
		WIRE = 94,
		BINARYSTRING = 95,
		HEXSTRING = 96,
		COMMA = 97,
		INT = 98,
		FLOAT = 99,
		POINTER = 100,
		ARRAY = 101,
		OF = 102,
		RECORD = 103,
		ATTRIBUTE = 104,
		IMPLIES = 105,
		QUOTED_STRING = 106,
		DPE = 107,
		LIBRARY = 108,
		REQS = 109,
		ACKS = 110,
		HIDDEN = 111,
		PARAMETER = 112,
		PORT = 113,
		MAP = 114,
		MIN = 115,
		MAX = 116,
		DPEINSTANCE = 117,
		LINK = 118,
		AT = 119,
		ORDERED_OP = 120,
		UNORDERED_OP = 121,
		WHITESPACE = 122,
		SINGLELINECOMMENT = 123,
		HIERARCHICAL_IDENTIFIER = 124,
		ALPHA = 125,
		DIGIT = 126,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_vcParserTokenTypes_hpp_*/
