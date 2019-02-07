//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Roland Shum
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Matrix2D.h"
#include <assert.h>
#include <AEEngine.h>
#include <math.h>
#include <float.h>
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static int float_isequal(float one, float two);
static int matrix_checkEql(AEMtx33 *AEmtx, Matrix2D *OWNmtx);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// We test against AE's matrix.
void TestMatrix2D(void)
{
  // Create our own 0 matrix.
  Matrix2D own_matrix = { 0 };
  // Create an AE matrix
  AEMtx33 AE_matrix = { 0 };

  // Check identity matrix.
  Matrix2DIdentity(&own_matrix);
  AEMtx33Identity(&AE_matrix);
  assert(matrix_checkEql(&AE_matrix, &own_matrix));

  // Check transpose matrix
  // Lets create a matrix
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      own_matrix.m[i][j] = (float)(rand() % 10);
    }
  }
  // Copy over that matrix to AE.
  memcpy(&AE_matrix, &own_matrix, sizeof(Matrix2D));
  assert(matrix_checkEql(&AE_matrix, &own_matrix));
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static int float_isequal(float one, float two)
{
  return (fabs(one - two) <= 0.00001);
}

static int matrix_checkEql(AEMtx33 *AEmtx, Matrix2D *OWNmtx)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      // If there is even one value that is not the same.
      if (!float_isequal(AEmtx->m[i][j],OWNmtx->m[i][j]))
      {
        // Not the same.
        return 0;
      }
    }
  }
  // All values are the same.
  return 1;
}