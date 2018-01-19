/* nesting */
int x;

int main() {

	int array[20];
	int x;

	{
		int x;
		char array[30];

		{
			int i;
			while (i > 10) {
				int j;
				j = i;
			}

		}
		{
			int k;
			k = 10;
		}
		x = 10;
	}
}
