
int a;
int b; 
int c;

int q2(int a, int b, int c) {

	int rv;

	switch (a) {

		case 10:
				rv = b + c;
				break;

		case 12:
				rv = b - c;
				break;

		case 14:
				if (b - c > 0) {

					rv = 1;

				} else {

					rv = 0;
				}

				break;

		case 16: 
				if (c - b > 0) {

					rv = 1;

				} else {

					rv = 0;
				}

				break;

		case 18:
				if (b - c == 0) {

					rv = 1;

				} else {

					rv = 0;
				}

				break;

		default:
				rv = 0;
				break;	
	}

	return rv;
}