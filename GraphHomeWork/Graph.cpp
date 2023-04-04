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
{//�������� ������� ����� � vertexes
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

//����� ������� �������������
void Graph::traversal()
{
	for (int i = 0; i < vertexCount; i++)
		tree_hands(i);
}

//
void Graph::tree_hands(int index)
{//������� ����� �������� ������ ��� ���� �����������
	SocNet = new int* [extender * SIZE];

	for (int i = 0; i < extender * SIZE; i++)
	{
		SocNet[i] = new int[extender * SIZE];
	}
	//��������
	for (int i = 0; i < extender * SIZE; i++)
	{
		for (int j = 0; j < extender * SIZE; j++)
		{
			SocNet[i][j] = 0;
		}
	}
		
	//������� �������������� ������ ��� ���� ����������� ��� ������ ������������
	vizited = new int[extender * SIZE];

	for (int i = 0; i < extender * SIZE; i++)
	{
		vizited[i] = 0;
	}
		
	//��������������� ��������� ����� ����� (1, 2, 3-�� ��������)
	tree_hands_sweep(index, vizited);

	//������������ ����� �� ���������������� ������� � ��������
	for (int i = 0; i < extender * SIZE; i++)
	{
		SocNet[index][i] = vizited[i];
	}
		
	//������ �������� ������� ��� ��������� �������� ���
	for (int i = 1; i < extender * SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (SocNet[i][j]) cout << vertexes[i] << " " << vertexes[j] << endl;
		}
	}
}

void Graph::tree_hands_sweep(int index, int* vizited)
{//��������� ���� �������� 1-�� �����������
	int counter = 0;

	for (int i = 0; i < vertexCount; i++)
	{
		//���� ���� ����� �/� index � ������� �������������, ������������ vizited
		if (edgeExists(vertexes[index], vertexes[i]))
		{
			vizited[i] = 1;
		}
	}
	//��������� ���� �������� hand_num-�� �����������
	while (counter < hand_num - 1)
	{
		for (int i = 0; i < vertexCount; i++)
		{
			for (int j = 0; j < vertexCount; j++)
			{//���� ���� ����� �/� i � j , ������������ vizited
				if (vizited[i] && edgeExists(vertexes[i], vertexes[j]))
				{
					vizited[j] = 1;
				}
					
			}
		}
		counter++;
	}
}
//�� ������ ������ �� ������� �������
void Graph::extend_matrix()
{
	extender++;//����������� ���������

	//������� ��������� ������
	int** tempMat = new int* [(extender - 1) * SIZE];
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		tempMat[i] = new int[(extender - 1) * SIZE];
	}
	//��������� ������
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			tempMat[i][j] = 0;
		}
	}
		
	//������������ �� �������
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			tempMat[i][j] = matrix[i][j];
		}
	}
		
	//������� matrix
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		delete[]matrix[i];
	}
	//�������� ������ ��� ����� ������
	matrix = new int* [extender * SIZE];
	for (int i = 0; i < extender * SIZE; i++)
	{
		matrix[i] = new int[extender * SIZE];
	}

	//�������� ����� matrix
	for (int i = 0; i < extender * SIZE; i++)
	{
		for (int j = 0; j < extender * SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
		
	//������������ �� ���������� � ����������� matrix
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		for (int j = 0; j < (extender - 1) * SIZE; j++)
		{
			matrix[i][j] = tempMat[i][j];
		}
	}
		
	//������� ���������� ������
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		delete[]tempMat[i];
	}
	//������� ��������� ������
	string* temp_vertexes = new string[(extender - 1) * SIZE];
	//������������
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		temp_vertexes[i] = vertexes[i];
	}
		
	//������� �������
	delete[]vertexes;
	//�������� ������(extender) * SIZE
	vertexes = new string[(extender)*SIZE];
	//������������
	for (int i = 0; i < (extender - 1) * SIZE; i++)
	{
		vertexes[i] = temp_vertexes[i];
	}
		
	//������� ���������
	delete[]temp_vertexes;
}
