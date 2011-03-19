// UnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <gtest/gtest.h>

#pragma comment(lib, "gtest")

int _tmain(int argc, _TCHAR* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();	
}

