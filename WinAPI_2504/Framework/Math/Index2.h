#pragma once
struct Index2
{
	int row; // ROW
	int col; //COL
	Index2() :row(0), col(0)
	{
	}
	Index2(int row, int x) : row(row), col(x)
	{
	}

	Index2 operator+(const Index2& other) const
	{
		return Index2(row + other.row, col + other.col);
	}
	Index2 operator-(const Index2& other) const
	{
		return Index2(row - other.row, col - other.col);
	}
	Index2 operator*(const Index2& other) const
	{
		return Index2(row * other.row, col * other.col);
	}
	Index2 operator/(const Index2& other) const
	{
		return Index2(row / other.row, col / other.col);
	}

	Index2 operator*(const int& scala) const
	{
		return Index2(row * scala, col * scala);
	}
	bool operator==(const Index2& other)const
	{
		if (row != other.row)
			return false;
		if (col != other.col)
			return false;

		return true;
	}
	bool operator!=(const Index2& other)const
	{
		if (row != other.row)
			return true;
		if (col != other.col)
			return true;

		return false;
	}
	bool operator<(const Index2& other)const
	{
		if (row < other.row && col < other.col)
			return true;
		return false;
	}
	bool operator<=(const Index2& other)const
	{
		if (row <= other.row && col <= other.col)
			return true;
		return false;
	}
	bool operator>(const Index2& other)const
	{
		if (row > other.row && col > other.col)
			return true;
		return false;
	}
	bool operator>=(const Index2& other)const
	{
		if (row >= other.row && col >= other.col)
			return true;
		return false;
	}
	void operator+=(const Index2& other)
	{
		row += other.row;
		col += other.col;
	}
	void operator-=(const Index2& other)
	{
		row -= other.row;
		col -= other.col;
	}
	void operator*=(const Index2& other)
	{
		row *= other.row;
		col *= other.col;
	}
	void operator/=(const Index2& other)
	{
		row /= other.row;
		col /= other.col;
	}
	void operator*=(const int& scala)
	{
		row *= scala;
		col *= scala;
	}
	int ChangeToInt(const int& num)//왼쪽 위 0기준
	{
		if (row < 0 || col < 0) return -1;
		return row * num + col;

	}
	void ChangeToIndex(const int& index, const int& num)//왼쪽 아래 0 기준
	{
		row = index / num;
		col = index % num;
	}

	static const Index2 Zero() { return Index2(0, 0); }
	static const Index2 One() { return Index2(1, 1); }

	static const Index2 Right() { return Index2(0, 1); }
	static const Index2 Left() { return Index2(0, -1); }
	static const Index2 Down() { return Index2(-1, 0); }
	static const Index2 Up() { return Index2(1, 0); }

};