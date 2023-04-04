#include "Graph.h"
#include <iostream>

Graph::Graph() 
{
	matrix = new int* [extender * SIZE];

	for (int i = 0; i < extender * SIZE; i++)
	{
		matrix[i] = new int[extender * SIZE];
	}
		
	for (int i = 0; i < extender * SIZE; i++)
	{
		for (int j = 0; j < extender * SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
		
	vertexes = new string[extender * SIZE];
	vertexCount = 0;
}

Graph::~Graph()
{
	for (int i = 0; i < extender * SIZE; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
	delete[] vertexes;

	for (int i = 0; i < extender * SIZE; i++)
	{
		delete[] SocNet[i];
	}

	delete[] SocNet;
	delete[] vizited;
}

void Graph::addVertex(string name)
{
	if (vertexCount == extender * SIZE)
	{
		extend_matrix();
	}
		
	if (name.size())
	{
		vertexes[vertexCount++] = name;
	}
	else
	{
		cout << "Error of addVertex" << endl;
		return;
	}
}

int Graph::getIndexbyName(string name)
{
	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == name)
		{
			return i;
		}
	}
}

void Graph::addEdge(string name1, string name2)
{//проверка наличия имени в vertexes
	int check = 0;

	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == name1)
		{
			check++;
			break;
		}
	}

	if (check != 1) {
		cout << "Error: Invalid name " << name1 << endl;
		return;
	}

	for (int i = 0; i < vertexCount; i++)
	{
		if (vertexes[i] == name2)
		{
			check++;
			break;
		}
	}

	if (check != 2) {
		cout << "Error: Invalid name " << name2 << endl;
		return;
	}

	if (name1.size() && name2.size() && name1 != name2)
	{
		int v1 = getIndexbyName(name1);
		int v2 = getIndexbyName(name2);

		matrix[v1][v2] = 1;
		matrix[v2][v1] = 1;
	}
	else 
	{
		cout << "Error of addEdge" << endl;
		return;
	}
}

bool Graph::edgeExists(string name1, string name2)
{
	return matrix[getIndexbyName(name1)][getIndexbyName(name2)] > 0;
}

//обход массива пользователей
void Graph::traversal()
{
	for (int i = 0; i < vertexCount; i++)
		tree_hands(i);
}

//
void Graph::tree_hands(int index)
{//создаем новый основной массив для всех рукопожатий
	SocNet = new int* [extender * SIZE];

	for (int i = 0; i < extender * SIZE; i++)
	{
		SocNet[i] = new int[extender * SIZE];
	}
	//зануляем
	for (int i = 0; i < extender * SIZE; i++)
	{
		for (int j = 0; j < extender * SIZE; j++)
		{
			SocNet[i][j] = 0;
		}
	}
		
	//создаем дополнительный массив для всех рукопожатий для одного пользователя
	vizited = new int[extender * SIZE];

	for (int i = 0; i < extender * SIZE; i++)
	{
		vizited[i] = 0;
	}
		
	//последовательно добавляет новые ребра (1, 2, 3-го порядков)
	tree_hands_sweep(index, vizited);

	//переписываем ребра из дополнительнорго массива в основной
	for (int i = 0; i < extender * SIZE; i++)
	{
		SocNet[index][i] = vizited[i];
	}
		
	//печать половины матрицы для избежания повторов пар
	for (int i = 1; i < extender * SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (SocNet[i][j]) cout << vertexes[i] << " " << vertexes[j] << endl;
		}
	}
}

void Graph::tree_hands_sweep(int index, int* vizited)
{//добавляем всех знакомых 1-го рукопожатия
	int counter = 0;

	for (int i = 0; i < vertexCount; i++)
	{
		//если есть ребро м/у index с другими пользователем, модифицируем vizited
		if (edgeExists(vertexes[index], vertexes[i]))
		{
			vizited[i] = 1;
		}
	}
	//добавляем всех знакомых hand_num-го рукопожатия
	while (counter < hand_num - 1)
	{
		for (int i = 0; i < vertexCount; i++)
		{
			for (int j = 0; j < vertexCount; j++)
			{//если есть ребро м/у i и j , модифицируем vizited
				if (vizited[i] && edgeExists(vertexes[i], vertexes[j]))
				{
					vizited[j] = 1;
				}
					
			}
		}
		counter++;
	}
}
//на случай выхода за пределы массива
void Graph::extend_matrix()
{
	extender++;//увеличиваем множитель

	//создаем временный массив
	int** tempMat = new int* [(extender - 1) * SIZE];
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		tempMat[i] = new int[(extender - 1) * SIZE];
	}
	//заполняем нулями
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			tempMat[i][j] = 0;
		}
	}
		
	//переписываем из старого
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			tempMat[i][j] = matrix[i][j];
		}
	}
		
	//убираем matrix
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		delete[]matrix[i];
	}
	//выделяем память под новый массив
	matrix = new int* [extender * SIZE];
	for (int i = 0; i < extender * SIZE; i++)
	{
		matrix[i] = new int[extender * SIZE];
	}

	//обнуляем новый matrix
	for (int i = 0; i < extender * SIZE; i++)
	{
		for (int j = 0; j < extender * SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
		
	//переписываем из временного в увеличенный matrix
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			matrix[i][j] = tempMat[i][j];
		}
	}
		
	//удаляем вренменный массив
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		delete[]tempMat[i];
	}
	//создаем временный массив
	string* temp_vertexes = new string[(extender - 1) * SIZE];
	//переписываем
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		temp_vertexes[i] = vertexes[i];
	}
		
	//удаляем страрый
	delete[]vertexes;
	//выделяем память(extender) * SIZE
	vertexes = new string[(extender)*SIZE];
	//переписываем
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		vertexes[i] = temp_vertexes[i];
	}
		
	//удаляем временный
	delete[]temp_vertexes;
}
