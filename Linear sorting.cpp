#include <iostream>

struct Pair
{
	int key;
	int value;
};

//---------------INPUT FUNCTIONS:
int exp(int base, int index)
{
	int x = 1;

	for (int i = 0; i < index; i++)
	{
		x *= base;
	}

	return x;
}

int input_int(char *&pointer)
{
	int x = 0;
	int k = 0;

	while (*pointer != ' ' && *pointer != '\n' && *pointer != '\0')
	{
		k++;
		pointer++;
	}
	for (int i = 0; i < k; i++)
	{
		pointer--;
		x = x + ((*pointer - 48) * exp(10, i));
	}
	pointer = pointer + k;

	return x;
}

int search_max(Pair array_out[], int n)
{
	int max = array_out[0].key;
	for (int i = 1; i < n; i++)
	{
		if (array_out[i].key > array_out[i - 1].key)
		{
			max = array_out[i].key;
		}
	}

	return max;
}

//SORTING FUNCTIONS:
void count(Pair array_out[], int how_many[], int buffor[], int n)
{
	for (int i = 0; i < n; i++)
	{
		how_many[array_out[i].key]++;
		buffor[array_out[i].key]++;
	}
}

void set_position(int how_many[], int max)
{
	for (int i = 1; i <= max; i++)
	{
		how_many[i] = how_many[i - 1] + how_many[i];
	}
}

void sort(Pair array_out[], int how_many[],int buffor[], int n, Pair sorted[])
{
	int position;
	for (int i = 0; i < n; i++)
	{
		position = how_many[array_out[i].key] - buffor[array_out[i].key] + 1; 
		how_many[array_out[i].key]++;
		sorted[position].key = array_out[i].key;	
		sorted[position].value = array_out[i].value;
	}
}

//MAIN:
int main()
{
	int *how_many; int n; bool test = true; char array_in[10]; char *pointer; int max; int *buffor;
	Pair *array_out; Pair *sorted;
	std::cin >> n;
	std::cin.ignore();

	array_out = new Pair[n + 1];
	sorted = new Pair[n + 1];

	//Input the pairs of numbers:
	for (int i = 0; i < n; i++)
	{
		fgets(array_in, 10, stdin);
		pointer = array_in;

		if (array_in != '\0' && *array_in != '\n')
		{
			array_out[i].key = input_int(pointer);
			pointer++;
			array_out[i].value = input_int(pointer);
			pointer++;
		}
	}
	max = search_max(array_out, n) + 1;
	how_many = new int[max+1];
	buffor = new int[max + 1];

	for (int i = 0; i <= max; i++)
	{
		how_many[i] = 0;
		buffor[i] = 0;
	}
	
	//sorting:
	count(array_out, how_many, buffor, n);

	set_position(how_many, max);
	
	sort(array_out, how_many,buffor, n, sorted);


	//choose option:
	std::cin >> test;
	std::cin.ignore();

	//view the sorting solution:
	if (test == true)
	{
		for (int i = 1; i <= n; i++)
		{
			std::cout << sorted[i].key << ',' << sorted[i].value << '\n';
		}
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			std::cout << sorted[i].key << '\n';
		}
	}
	
	return 0;
}