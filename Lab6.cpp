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

	int** graf = new int* [size];

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
		for (int j = 0; arr[j] != -1; j++)
		{
			if (arr[j] == i)
			{
				count++;

				break;
			}
		}

		if (i != count - 1)
		{
			return 0;
		}
	}

	return count == size;
}

bool ifGrafEmpty(int** grafCopy, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grafCopy[i][j] == 1)
			{
				return 0;
			}
		}
	}

	return 1;
}

void getInputAndOutput(int* input, int* output, int size, int** grafCopy)
{
	int pointer = 0;

	int i = 0;

	int j = 0;

	while (true)
	{
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
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

		if (i == j && i == size)
		{
			if (ifGrafEmpty(grafCopy, size))
			{
				break;
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

	int* bufferinput = new int[normSize + 1];

	int* bufferoutput = new int[normSize + 1];

	for (int i = 0; i < normSize + 1; i++)
	{
		bufferinput[i] = -1;

		bufferoutput[i] = -1;
	}

	int j = 0;

	bool b1;

	bool b2;

	for (int i = 0; output[i] != -1; i++)
	{
		for (j = 0; output[j] != -1; j++)
		{
			bufferinput[j] = input[j];

			bufferoutput[j] = output[j];

			if (output[i] == input[j])
			{
				b1 = IsArrHasAllDots(bufferoutput, size);

				if (b1)
				{

					b2 = IsArrHasAllDots(bufferinput, size);

					if (b2)
					{
						std::cout << "Yra)";

						break;
					}
				}
			}
		}

		if (output[i] == input[j])
		{
			if (b1)
			{
				if (b2)
				{
					break;
				}
			}
		}

		for (int k = 0; k < normSize; k++)
		{
			bufferinput[k] = -1;

			bufferoutput[k] = -1;
		}
	}

	delete[] bufferinput;

	delete[] bufferoutput;

	delete[] input;

	delete[] output;

}

void START()
{
	int** graf = getGrafFromFile();

	int size = getSize();                             

	int** copyGraf = new int* [pow(size, 0.5)];

	for (int i = 0; i < pow(size, 0.5); i++)
	{
		copyGraf[i] = new int[pow(size, 0.5)];

		for (int j = 0; j < pow(size, 0.5); j++)
		{
			std::cout << graf[i][j] << " ";

			copyGraf[i][j] = graf[i][j];
		}

		std::cout << std::endl;
	}

	findWay(pow(size, 0.5), copyGraf);

	for (int i = 0; i < pow(size, 0.5); i++)
	{
		delete[] graf[i];
	}

	delete[] graf;

	for (int i = 0; i < pow(size, 0.5); i++)
	{
		delete[] copyGraf[i];
	}

	delete[] copyGraf;
}

int main()
{
	srand(time(0));

	START();
}

