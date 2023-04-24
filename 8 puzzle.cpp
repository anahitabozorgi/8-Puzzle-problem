#include <iostream>
#include <vector> 

using namespace std;
#define _size 3
enum Moves {
	NONE = -1,
	_up = 0,
	_down = 1,
	_left = 2,
	_right = 3
};
//int moves[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int lastId = 0;
int ans[][_size] = { {0,1,2},{3,4,5},{6,7,8} };
class Node {
public:
	Node(Moves move) {
		ThisNodeGeneratedWithMove = move;
		id = ++lastId;
	}
	Moves ThisNodeGeneratedWithMove;
	int id;
	int data[_size][_size];
	int i_, j_;
	void FindZero() {
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				if (data[i][j] == 0)
				{
					i_ = i;
					j_ = j;
					return;
				}

			}
		}
	}
	void print() {
		cout << " #" << id << endl;
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool canMove(Moves move)//up
	{
		if (move == _up && ThisNodeGeneratedWithMove == _down)	return false;
		if (move == _down && ThisNodeGeneratedWithMove == _up)	return false;
		if (move == _left && ThisNodeGeneratedWithMove == _right)	return false;
		if (move == _right && ThisNodeGeneratedWithMove == _left)	return false;
		if (move == _up)
		{
			if (i_ == 0)return false;
		}
		else if (move == _down)
		{
			if (i_ == _size - 1)return false;
		}
		else if (move == _left)
		{
			if (j_ == 0)return false;
		}
		else if (move == _right)
		{
			if (j_ == _size - 1)return false;
		}
		return true;
	}
	Node Move(Moves move) {
		Node n(move);
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				n.data[i][j] = data[i][j];
			}
		}

		if (move == _up)
		{
			n.data[i_][j_] = data[i_ - 1][j_];
			n.data[i_ - 1][j_] = 0;
			n.j_ = j_;
			n.i_ = i_ - 1;
		}
		else if (move == _down)
		{
			n.data[i_][j_] = data[i_ + 1][j_];
			n.data[i_ + 1][j_] = 0;
			n.j_ = j_;
			n.i_ = i_ + 1;
		}
		else if (move == _left)
		{
			n.data[i_][j_] = data[i_][j_ - 1];
			n.data[i_][j_ - 1] = 0;
			n.j_ = j_ - 1;
			n.i_ = i_;
		}
		else if (move == _right)
		{
			n.data[i_][j_] = data[i_][j_ + 1];
			n.data[i_][j_ + 1] = 0;
			n.j_ = j_ + 1;
			n.i_ = i_;
		}
		return n;
	}
};





bool IsEqual(int A[][_size], int B[][_size]) {
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (A[i][j] != B[i][j])
				return false;
		}
	}
	return true;
}
vector<Node> currentQueue;
vector<Node> visited;

bool isvisitedBefore(Node n) {
	for (int i = 0; i < visited.size(); i++)
	{
		if (IsEqual(visited[i].data, n.data))
			return true;
	}
	return false;
}
void InitRandom(int A[][_size]) {
	bool temp[_size * _size] = { false, false, false, false, false, false, false, false, false };
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			while (true)
			{
				int t = rand() % (_size * _size);
				if (temp[t] == false)
				{
					A[i][j] = t;
					temp[t] = true;
					break;
				}
			}
		}
		cout << endl;
	}
}
bool Solve() {
	cout << endl;
	if (currentQueue.size() == 0)
	{
		cout << endl << "Can not found solution!";
		return true;
	}
	Node x = currentQueue.front();
	cout << "checking: ";
	x.print();
	currentQueue.erase(currentQueue.begin());
	if (IsEqual(x.data, ans))
	{
		cout << endl << "Doneeeeeeeeee!";
		return true;
	}
	if (isvisitedBefore(x)) {
		return false;
	}
	visited.push_back(x);
	if (x.canMove(_up)) {
		Node y = x.Move(_up);
		if (!isvisitedBefore(y))
		{
			currentQueue.push_back(y);
			cout << "generate by moving up";
			currentQueue.back().print();
		}
	}
	if (x.canMove(_down)) {
		Node y = x.Move(_down);
		if (!isvisitedBefore(y))
		{
			currentQueue.push_back(y);
			cout << "generate by moving down";
			currentQueue.back().print();
		}
	}
	if (x.canMove(_left)) {
		Node y = x.Move(_left);
		if (!isvisitedBefore(y))
		{
			currentQueue.push_back(y);
			cout << "generate by moving left";
			currentQueue.back().print();
		}
	}
	if (x.canMove(_right))
	{
		Node y = x.Move(_right);
		if (!isvisitedBefore(y))
		{
			currentQueue.push_back(y);
			cout << "generate by moving right";
			currentQueue.back().print();
		}
	}
	return false;
}
int main() {
	Node n(NONE);
	InitRandom(n.data);
	//n.data[0][0] = 1;
	//n.data[0][1] = 0;
	//n.data[0][2] = 2;

	//n.data[1][0] = 3;
	//n.data[1][1] = 4;
	//n.data[1][2] = 5;

	//n.data[2][0] = 6;
	//n.data[2][1] = 7;
	//n.data[2][2] = 8;
	n.FindZero();
	currentQueue.push_back(n);
	while (true)
	{
		if (Solve())break;
		getchar();
	}
}