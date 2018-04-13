
typedef enum {
	op_add,
	op_mul,
	op_div,
	op_sub
} OpCode;

char * oc_string(OpCode op);

char * oc_string(OpCode op) {
	switch(op) {
	case op_add:
		return "ADD";
	case op_sub:
			return "SUB";
	case op_mul:
		return "MUL";
	case op_div:
		return "DIV";
	default:
		return "###unknown###";
	}
}