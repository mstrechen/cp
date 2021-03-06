#include <stdio.h>
#include <vector>
#include <cassert>
#include <random>
#include <functional>
#include <algorithm>

struct Move {

	int i;

	int j;

	int count;
};

int main() {
	int sizeI, sizeJ;
	scanf("%d %d", &sizeI, &sizeJ);
	std::vector<std::vector<int>> a(sizeI, std::vector<int>(sizeJ));
	const int free = -1;
	const int wall = 0;
	std::mt19937 gen(221351);
	int nFree = 0;
	int startI = -1;
	int startJ = -1;
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			char c;
			scanf(" %c", &c);
			if (c == 'K') {
				assert(startI == -1 && startJ == -1);
				startI = i;
				startJ = j;
				a[i][j] = free;
				nFree++;
			} else if (c == '.') {
				a[i][j] = free;
				nFree++;
			} else {
				assert(c == 'X');
				a[i][j] = wall;
			}
		}
	}
	std::vector<std::vector<int>> freeCount(sizeI, std::vector<int>(sizeJ, 0));
	int di[8] = { -2, -2, -1, -1,  1, 1,  2, 2};
	int dj[8] = { -1,  1, -2,  2, -2, 2, -1, 1};
	
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			for (int m = 0; m < 8; m++) {
				int ni = i + di[m];
				int nj = j + dj[m];
				if (0 <= ni && ni < sizeI && 0 <= nj && nj < sizeJ && a[ni][nj] == free) {
					freeCount[i][j]++;
				}
			}
		}
	}
	
	assert(startI != -1 && startJ != -1);
	assert(nFree >= 1);
	int nWrong = 0;
	bool found = false;
	std::function<void(int, int, int)> find = [&](const int i, const int j, const int step) {
		assert(0 <= i && i < sizeI);
		assert(0 <= j && j < sizeJ);
		assert(1 <= step && step <= nFree);
		assert(a[i][j] == free);
		a[i][j] = step;
		for (int m = 0; m < 8; m++) {
			int ni = i + di[m];
			int nj = j + dj[m];
			if (0 <= ni && ni < sizeI && 0 <= nj && nj < sizeJ) {
				freeCount[ni][nj]--;
			}
		}
		if (step == nFree) {
			found = true;
			return;
		}
		Move moves[8];
		int movesSize = 0;
		for (int m = 0; m < 8; m++) {
			int ni = i + di[m];
			int nj = j + dj[m];
			if (0 <= ni && ni < sizeI && 0 <= nj && nj < sizeJ && a[ni][nj] == free) {
				moves[movesSize] = Move{ni, nj, freeCount[ni][nj]};
				movesSize++;
			}
		}
		if (movesSize > 0) {
			int minCount = 9;
			for (int i = 0; i < movesSize; i++) {
				minCount = std::min(minCount, moves[i].count);
			}
			assert(minCount < 9);
			int newSize = 0;
			for (int i = 0; i < movesSize; i++) {
				if (moves[i].count == minCount) {
					moves[newSize] = moves[i];
					newSize++;
				}
			}
			movesSize = newSize;
			assert(movesSize > 0);
			std::shuffle(moves, moves + movesSize, gen);
			for (int i = 0; i < movesSize; i++) {
				Move move = moves[i];
				find(move.i, move.j, step + 1);
				if (found) {
					return;
				}
				nWrong++;
			}
		}
		assert(a[i][j] == step);
		a[i][j] = free;
		for (int m = 0; m < 8; m++) {
			int ni = i + di[m];
			int nj = j + dj[m];
			if (0 <= ni && ni < sizeI && 0 <= nj && nj < sizeJ) {
				freeCount[ni][nj]++;
			}
		}
	};
	find(startI, startJ, 1);
	assert(found);
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			printf(" %2d", a[i][j]);
		}
		printf("\n");
	}
	fprintf(stderr, "nWrong=%d\n", nWrong);
	return 0;
}
