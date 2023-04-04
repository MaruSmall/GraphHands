#pragma once
#include <string>
#define SIZE 10
#define hand_num 3
using namespace std;

class Graph
{
public:
    Graph();
    ~Graph();
    // ���������� �������
    void addVertex(string name);
    // ���������� �����
    void addEdge(string v1, string v2);
    void traversal();
    int getIndexbyName(string name);
    void tree_hands(int index);
    void tree_hands_sweep(int index, int* vizited);
    void extend_matrix();

private:
    bool edgeExists(string name1, string name2);
    int** matrix = new int* [SIZE];
    string* vertexes;
    int vertexCount; // ���������� ����������� ������
    int extender = 1;//��������� SIZE
    int** SocNet;//������� ���� �����������
    int* vizited;//�������������� ������ ��� ���������� SocNet
};

