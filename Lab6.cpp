#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int getSize()
{
	std::ifstream f;

	f.open("D:\\Lab6\\GrafData.txt");

	std::string buffer;

	int size;

	f >> buffer;

	size = std::stoi(buffer);

	f.close();

	return size;
}

int** getGrafFromFile()
{
	std::ifstream f;

	f.open("D:\\Lab6\\GrafData.txt");

	std::string buffer;

	f >> buffer;

	int size = std::stoi(buffer);

	int** graf = new int*[size];

	for (int i = 0; i < size; i++)
	{
		graf[i] = new int[size];
	}
	
	std::string* buffer2 = new std::string[size];

	for (int i = 0; f; i++)
	{
		f >> buffer2[i];
	}

	int pointer = 0;

	for (int i = 0; i < pow(size, 0.5); i++)
	{
		for (int j = 0; j < pow(size, 0.5); j++)
		{
			graf[i][j] = std::stoi(buffer2[pointer]);

			pointer++;
		}
	}

	f.close();

	return graf;
}

bool IsArrHasAllDots(int* arr, int size) // pow(size,0.5)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < pow(size,2); j++)
		{
			if (arr[j] == i)
			{
				count++;

				break;
			}
		}
	}

	return count == size;
}

void getInputAndOutput(int* input, int* output, int size, int** grafCopy)
{
	int pointer = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j && grafCopy[i][j] == 1)
			{
				output[pointer] = i;

				input[pointer] = j;

				grafCopy[i][j] = 0;
				
				i = j;

				j = -1;

				pointer++;
			}
		}
	}
}

int getCountOfOutputs(int* output)
{
	int count = 0;

	for (int i = 0; output[i] != -1; i++)
	{
		count++;
	}

	return count;
}

void findWay(int size, int** grafCopy) // pow(size,0.5)
{
	int pointer = 0;

	int* input = new int[pow(size, 2)];

	int* output = new int[pow(size, 2)];

	for (int i = 0; i < pow(size, 2); i++)
	{
		input[i] = -1;

		output[i] = -1;
	}

	getInputAndOutput(input, output, size, grafCopy);

	int normSize = getCountOfOutputs(output);

	std::cout << std::endl;

	for (int i = 0; input[i] != -1; i++)
	{
		std::cout << output[i] << " " << input[i] << std::endl;
	}

	std::cout << std::endl;

	int* bufferinput = new int[normSize];

	int* bufferoutput = new int[normSize];

	for (int i = 0; i < normSize; i++)
	{
		bufferinput[i] = -1;

		bufferoutput[i] = -1;
	}

	int j = 0;

	for (int i = 0; i < normSize; i++)
	{
		for ( j = 0; j < normSize; j++)
		{
			bufferinput[j] = input[j];

			bufferoutput[j] = output[j];

			if (output[i] == input[j])
			{
				if (IsArrHasAllDots(bufferoutput, size))
				{
					if (IsArrHasAllDots(bufferinput, size))
					{
						std::cout << "Yra)";

						break;
					}
				}
			}
		}

		if (output[i] == input[j])
		{
			if (IsArrHasAllDots(bufferoutput, size))
			{
				if (IsArrHasAllDots(bufferinput, size))
				{
					break;
				}
			}
		}

		for (int i = 0; i < normSize; i++)
		{
			bufferinput[i] = -1;

			bufferoutput[i] = -1;
		}
	}
}

void START()
{
	int** graf = getGrafFromFile();
	
	int size = getSize();

	/*int size = pow(rand() % 4 + 2,2);              ....... ПРОВЕРКА .........

	int** graf = new int* [pow(size,0.5)];

	for (int i = 0; i < pow(size, 0.5); i++)
	{
		graf[i] = new int[pow(size, 0.5)];

		for (int j = 0; j < pow(size, 0.5); j++)
		{
			graf[i][j] = rand() % 2;

			if (i == j)
			{
				graf[i][j] = 0;
			}
		}                                             ........ПРОВЕРКА.......
	}*/                                              

	int** copyGraf = new int*[pow(size,0.5)];

	for (int i = 0; i < pow(size,0.5); i++)
	{
		copyGraf[i] = new int[pow(size, 0.5)];

		for (int j = 0; j < pow(size, 0.5); j++)
		{
			std::cout << graf[i][j] << " ";

			copyGraf[i][j] = graf[i][j];
		}

		std::cout << std::endl;
	}

	findWay(pow(size,0.5), copyGraf);
}

int main()
{
	srand(time(0));

	START();
}

