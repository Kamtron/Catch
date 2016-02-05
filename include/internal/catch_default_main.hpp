/*
 *  Created by Phil on 20/05/2011.
 *  Copyright 2011 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED

#ifndef __OBJC__

#ifdef CATCH_MPI_ENABLED
#include <mpi.h>
#endif

// Standard C/C++ main entry point
int main (int argc, char * argv[]) {
#ifdef CATCH_MPI_ENABLED
  MPI_Init(NULL,NULL);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  printf("Catch running in parallel (Rank %i)\n",my_rank);
  auto test_results = Catch::Session().run( argc, argv );
  MPI_Finalize();
  return test_results;
#else
    return Catch::Session().run( argc, argv );
#endif
}

#else // __OBJC__

// Objective-C entry point
int main (int argc, char * const argv[]) {
#if !CATCH_ARC_ENABLED
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#endif

    Catch::registerTestMethods();
    int result = Catch::Session().run( argc, (char* const*)argv );

#if !CATCH_ARC_ENABLED
    [pool drain];
#endif

    return result;
}

#endif // __OBJC__

#endif // TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED
