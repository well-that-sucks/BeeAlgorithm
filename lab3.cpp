#include <iostream>
#include <iomanip>

int** copy2DArray(int**, int, int);

void deleteArray(int**, int, int);

template <typename T>
void fillArray(T*, int, T);

void deleteElement(int*, int&, int);

void generateGraph(int**, int, int, int);

void fixVerticiesCovering(int**, int**, int, int);

void generateSolutions(int**, int**, int, int);

int countOnes(int*, int);

int findMinSolution(int**, int, int);

void qsort(int**, int*, int, int, int);

int deleteExcessReds(int**, int*, int);

void markNeighboringVerticies(int**, bool*, int, int);

void processArea(int**, int**, int, int, int);

void beeUpgrade(int**, int**, int, int, int, int);

int main() {
	std::clock_t cstart = std::clock();
	int n = 300;
	int areas = 720;
	int scoutBees = 20;
	int workerBees = 210;
	int bestAreas = 10;
	int bestScoutBees = 5;
	int bestWorkerBees = 4;
	int** g = new int*[n];
	for (int i = 0; i < n; i++) {
		g[i] = new int[n + 1];
		fillArray(g[i], n + 1, 0);
	}
	generateGraph(g, n, 2, 30);
	srand(time(NULL));
	int** solutions = new int*[10000];
	for (int i = 0; i < 10000; i++) {
		solutions[i] = new int[n];
		fillArray(solutions[i], n, 0);
	}
	generateSolutions(g, solutions, n, 10000);
	/*for (workerBees = 20; workerBees <= 300; workerBees += 5) {
		int minSolution = n * n;
		int** tSol = copy2DArray(solutions, areas, n);
		//std::cout << "Best solution in the beginning is " << findMinSolution(tSol, areas, n) << std::endl;
		beeUpgrade(g, tSol, n, areas, scoutBees, workerBees);
		//std::cout << "Best solution on iteration 1 is " << findMinSolution(tSol, areas, n) << std::endl;
		for (int i = 1; i <= 100; i++) {
			beeUpgrade(g, tSol, n, areas, scoutBees, workerBees);
			//if (i % 20 == 0)
				//std::cout << "Best solution on iteration " << i << " is " << findMinSolution(tSol, areas, n) << std::endl;
		}
		if (findMinSolution(tSol, areas, n) < minSolution) {
			minSolution = findMinSolution(tSol, areas, n);
			bestWorkerBees = workerBees;
		}
		std::cout << workerBees << ": " << minSolution << std::endl;
		deleteArray(tSol, bestAreas, n);
	}*/
	std::cout << "Best solution in the beginning is " << findMinSolution(solutions, areas, n) << std::endl;
	beeUpgrade(g, solutions, n, areas, scoutBees, workerBees);
	std::cout << "Best solution on iteration 1 is " << findMinSolution(solutions, areas, n) << std::endl;
	for (int i = 1; i <= 500; i++) {
		beeUpgrade(g, solutions, n, areas, scoutBees, workerBees);
		if (i % 20 == 0)
			std::cout << "Best solution on iteration " << i << " is " << findMinSolution(solutions, areas, n) << std::endl;
	}
	/*for (int k = 0; k < 5; k++) {
		int minSolution = n * n;
		for (areas = 160; areas <= 1000; areas += 20) {
			int** tSol = copy2DArray(solutions, areas, n);
			//std::cout << "Best solution in the beginning is " << findMinSolution(tSol, areas, n) << std::endl;
			beeUpgrade(g, tSol, n, areas, bestScoutBees, bestWorkerBees);
			//std::cout << "Best solution on iteration 1 is " << findMinSolution(tSol, areas, n) << std::endl;
			for (int i = 1; i <= 100; i++) {
				beeUpgrade(g, tSol, n, areas, bestScoutBees, bestWorkerBees);
				//if (i % 20 == 0)
					//std::cout << "Best solution on iteration " << i << " is " << findMinSolution(tSol, areas, n) << std::endl;
			}
			if (findMinSolution(tSol, areas, n) < minSolution) {
				minSolution = findMinSolution(tSol, areas, n);
				bestAreas = areas;
			}
			deleteArray(tSol, areas, n);
		}
		minSolution = n * n;
		for (scoutBees = 15; scoutBees <= 50; scoutBees += 5) {
			int** tSol = copy2DArray(solutions, bestAreas, n);
			for (int i = 0; i <= 100; i++)
				beeUpgrade(g, tSol, n, bestAreas, scoutBees, bestWorkerBees);
			if (findMinSolution(tSol, bestAreas, n) < minSolution) {
				minSolution = findMinSolution(tSol, bestAreas, n);
				bestScoutBees = scoutBees;
			}
			deleteArray(tSol, bestAreas, n);
		}
		minSolution = n * n;
		for (workerBees = bestScoutBees; workerBees <= 200; workerBees += 5) {
			int** tSol = copy2DArray(solutions, bestAreas, n);
			for (int i = 0; i <= 100; i++)
				beeUpgrade(g, tSol, n, bestAreas, bestScoutBees, workerBees);
			if (findMinSolution(tSol, bestAreas, n) < minSolution) {
				minSolution = findMinSolution(tSol, bestAreas, n);
				bestWorkerBees = workerBees;
			}
			deleteArray(tSol, bestAreas, n);
		}
		std::cout << "Best areas number on iteration " << k + 1 << " is " << bestAreas << std::endl;
		std::cout << "Best scout bees number on iteration " << k + 1 << " is " << bestScoutBees << std::endl;
		std::cout << "Best worker bees number on iteration " << k + 1 << " is " << bestWorkerBees << std::endl;
	}*/
	deleteArray(solutions, areas, n);
	deleteArray(g, n, n);
	std::clock_t cend = std::clock();
	long long timeElapsed = (cend - cstart) / CLOCKS_PER_SEC;
	long long hours = timeElapsed / 3600;
	long long mins = (timeElapsed - hours * 3600) / 60;
	long secs = (timeElapsed - hours * 3600 - mins * 60);
	std::cout << "Time elapsed: " << hours << "h " << mins << "m " << secs << "s" << std::endl;
	return 0;
}

int** copy2DArray(int** b, int n, int m) {
	int** a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			a[i][j] = b[i][j];
	return a;
}

void deleteArray(int** a, int n, int m) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
}

template <typename T>
void fillArray(T* a, int n, T element) {
	for (int i = 0; i < n; i++)
		a[i] = element;
}

void deleteElement(int* a, int& n, int index) {
	n--;
	for (int i = index; i < n; i++)
		a[i] = a[i + 1];
}

void generateGraph(int** g, int n, int leftBorder, int rightBorder) {
	for (int i = 0; i < n; i++) {
		if (g[i][n] < rightBorder) {
			int* availVerticies = new int[n];
			fillArray(availVerticies, n, 0);
			int m = 0;
			for (int j = 0; j < n; j++) {
				if (j != i && g[i][j] == 0 && g[j][n] < rightBorder)
					availVerticies[m++] = j;
			}
			if (m > 0) {
				int newVerticies = 0;
				if (g[i][n] == 0)
					newVerticies = rand() % (rightBorder - leftBorder) + leftBorder;
				else
					newVerticies = (rand() % m) % (rightBorder - g[i][n]);
				for (int j = 0; j < newVerticies; j++) {
					int rndIndex = rand() % m;
					g[i][availVerticies[rndIndex]] = 1;
					g[availVerticies[rndIndex]][i] = 1;
					g[i][n]++;
					g[availVerticies[rndIndex]][n]++;
					deleteElement(availVerticies, m, rndIndex);
				}
			}
			delete[] availVerticies;
		}
	}
}

void fixVerticiesCovering(int** g, int** s, int n, int ind) {
	for (int i = 0; i < n; i++) {
		if (s[ind][i] == 0)
			for (int j = 0; j < n; j++)
				if (g[i][j] == 1)
					s[ind][j] = 1;
	}
}

void generateSolutions(int** g, int** s, int n, int m) {
	int rndVerticies = n - n / 4;
	for (int i = 0; i < m; i++) {
		int* vRnd = new int[n];
		int tn = n;
		for (int j = 0; j < n; j++)
			vRnd[j] = j;
		for (int j = 0; j < rndVerticies; j++) {
			int rndInd = rand() % tn;
			s[i][vRnd[rndInd]] = 1;
			deleteElement(vRnd, tn, rndInd);
		}
		fixVerticiesCovering(g, s, n, i);
		delete[] vRnd;
	}
}

int countOnes(int* a, int n) {
	int c = 0;
	for (int i = 0; i < n; i++)
		if (a[i] == 1)
			c++;
	return c;
}

int findMinSolution(int** s, int areas, int n) {
	int min = countOnes(s[0], n);
	for (int i = 1; i < areas; i++) {
		int t = countOnes(s[i], n);
		if (t < min)
			min = t;
	}
	return min;
}

void qsort(int** s, int* a, int n, int l, int r) {
	int i = l;
	int j = r;
	int m = s[a[(i + j) / 2]][n];
	while (i <= j) {
		while (s[a[i]][n] > m)
			i++;
		while (s[a[j]][n] < m)
			j--;
		if (i <= j) {
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	}
	if (i < r)
		qsort(s, a, n, i, r);
	if (j > l)
		qsort(s, a, n, l, j);
}

int deleteExcessReds(int** g, int* vertexType, int n) {
	int deletedReds = 0;
	for (int i = 0; i < n; i++) {
		if (vertexType[i] == 1) {
			int c = 0;
			for (int j = 0; j < n; j++)
				if (g[i][j] == 1 && vertexType[j] == 1)
					c++;
			if (c == g[i][n]) {
				vertexType[i] = 0;
				deletedReds++;
			}
		}
	}
	return deletedReds;
}

void markNeighboringVerticies(int** g, bool* isLocked, int n, int i) {
	for (int j = 0; j < n; j++)
		if (g[i][j] == 1)
			isLocked[j] = true;
}

void processArea(int** g, int** s, int n, int sol, int workerBees) {
	int imax = 0;
	bool* isLocked = new bool[n];
	fillArray(isLocked, n, false);
	for (int k = 0; k < workerBees; k++) {
		while (imax < n && (s[sol][imax] == 1 || isLocked[imax]))
			imax++;
		if (imax < n) {
			for (int i = 0; i < n; i++)
				if (g[i][n] > g[imax][n] && s[sol][i] == 0 && !isLocked[i])
					imax = i;
			int* testSolution = new int[n];
			for (int j = 0; j < n; j++)
				testSolution[j] = s[sol][j];
			testSolution[imax] = 1;
			int rBefore = 0, rAfter = 0;
			for (int i = 0; i < n; i++)
				if (s[sol][i] == 1)
					rBefore++;
			rAfter = rBefore - deleteExcessReds(g, testSolution, n) + 1;
			if (rAfter < rBefore) {
				markNeighboringVerticies(g, isLocked, n, imax);
				for (int i = 0; i < n; i++)
					s[sol][i] = testSolution[i];
			}
			delete[] testSolution;
			isLocked[imax] = true;
		}
	}
	delete[] isLocked;
}

void beeUpgrade(int** g, int** s, int n, int solNumber, int scoutBees, int workerBees) {
	int iterationNum = scoutBees * 3;
	int* rndArray = new int[solNumber];
	int m = solNumber;
	int* areas = new int[iterationNum];
	for (int i = 0; i < solNumber; i++)
		rndArray[i] = i;
	for (int i = 0; i < iterationNum; i++) {
		int rndInd = rand() % m;
		areas[i] = rndInd;
		deleteElement(rndArray, m, rndInd);
	}
	qsort(s, areas, n, 0, iterationNum - 1);
	processArea(g, s, n, areas[0], workerBees / 5);
	scoutBees--;
	int offset = 1;
	if (scoutBees >= 2 && workerBees / 5 > 2) {
		processArea(g, s, n, areas[1], workerBees / 5);
		scoutBees--;
		offset++;
	}
	workerBees = workerBees - (workerBees / 5 + workerBees / 5);
	int workerBeesPerArea = workerBees / scoutBees;
	int workerBeesUtilized = 0;
	for (int i = 0; i < scoutBees; i++) {
		if (workerBeesUtilized + workerBeesPerArea > workerBees) {
			processArea(g, s, n, areas[i + offset], workerBees - workerBeesUtilized);
			workerBeesUtilized = workerBees;
		} else {
			processArea(g, s, n, areas[i + offset], workerBeesPerArea);
			workerBeesUtilized += workerBeesPerArea;
		}
	}
	delete[] rndArray;
	delete[] areas;
}