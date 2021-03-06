﻿#include "pch.h"
#include "mpi.h"
#include <iostream>
#include <random>
#include <ctime>
#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>

std::vector<std::vector <int>> getRandomMatrix(int n, int m) {
  std::vector <std::vector <int>> Matrix(n, std::vector <int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      Matrix[i][j] = (rand() % 100 + 1);;
    }
  }
  return Matrix;
}

  int main(int argc, char** argv) {
    int answ = 0;
    int size, rank;
    int a=4, b=4;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector <std::vector<int>> Matrix = getRandomMatrix(a, b);
    if (rank == 0) {
      for (int i = 0; i < b; i++) {
        if (i % size) {
          MPI_Send(&Matrix[i][0], b, MPI_INT, i % size, 0, MPI_COMM_WORLD);
        }
      }
    }
    MPI_Status status;
    std::vector <int> s(b);
    int ans = 0;
    if (rank == 0) {
      for (int i = 0; i < a; i += size) {
        ans = *min_element(Matrix[i].begin(), Matrix[i].end()), ans;
      }
    }
    else {
      for (int i = rank; i < a; i += size) {
        MPI_Recv(&s[0], b, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        ans = ans, *min_element(s.begin(), s.end());
      }
    }
    MPI_Reduce(&ans, &answ, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "min_elem " << answ << std::endl;
    MPI_Finalize();
    return 0;
  }
