//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EXACT_SOLUTION_INFRA_H
#define EXACT_SOLUTION_INFRA_H

#include "eigen_port.h"

struct SI_Problem
{
  SI_Problem(const Matrix& t_A1, const Matrix& t_A2) : A1(t_A1), A2(t_A2), v1(t_A1.rows()), v2(t_A2.rows()) {}

  const Matrix& A1;
  const Matrix& A2;
  long v1;
  long v2;
};

struct SI_State
{
  SI_State(const std::vector<bool>& t_cols, const Matrix& t_M, const long t_R) : cols(t_cols), M(t_M), R(t_R) {}
  void serialNextState(const int col) { M(R,col) = 1; R++; cols[col] = true; }
  void serialPrevState(const int col) { cols[col] = false; R--; M(R, col) = 0; }
  std::vector<bool> cols;
  Matrix M;
  long R;
};

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, int t_k);
void subgraphIsomorphismSerial(const SI_Problem &P, SI_State &state);

#endif // EXACT_SOLUTION_INFRA_H
