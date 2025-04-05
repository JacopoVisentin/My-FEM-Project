/*
*  main.c
*  Library for EPL1110 : Finite Elements for dummies
*  Elasticite lineaire plane
*  
*  Solver for the finite element method
*
*  Copyright (C) 2024 UCL-IMMC : Vincent Legat
*  All rights reserved.
*
*/

#include "fem.h"
#include "solverMain.h"

/////////////////////////
// WILL USE THOMAS' SOLVER. THIS IS JUST A PLACEHOLDER SO I UNDERSTAND WHAT HAPPENS AND I CAN CREATE THE POSTPROCESSOR
/////////////////////////

// SOLVER SCRIPT TAKES A MESH.TXT AND PROBLEM.TXT FILE DESCRIBING THE GEOMETRY AND PROBLEM PARAMETERS (+ BOUNDARIES)
// OUTPUT IS A NODAL_DISPLACEMENTS.TXT FILE CONTAINING THE UV DISPLACEMENTS VECTOR FOR EVERY NODE, TO BE DECIPHERED BY POSTPROCESSOR


int solverMain(void) {

    // initialize a geometry struct
    femGeo *theGeometry = geoGetGeometry();

    // load the geometry from top level mesh.txt into theGeometry struct
    geoMeshRead("../../../data/mesh.txt");

    // initialize a problem struct and fill it from the problem.txt config file
    femProblem *theProblem = femElasticityRead(theGeometry, "../data/problem.txt");
    // print it


    // here we could add a solvertype argument so that the function can use different types of solvers if we have the time
    double *theSoluce = femElasticitySolve(theProblem);

    // save the solution -nodal displacement- vector into a nodal_displacements.txt file
    femSolutionWrite(theSoluce, "../../../data/nodal_displacements.txt");

    // free allocated memory
    femElasticityFree(theProblem);
    geoFree();
    
    return 0;

}