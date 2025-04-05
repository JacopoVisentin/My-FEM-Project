/*
 *  main.c
 *  Library for EPL1110 : Finite Elements for dummies
 *  Elasticite lineaire plane
 *  
 * Preprocessor for the finite element method
 *
 *  Copyright (C) 2024 UCL-IMMC : Vincent Legat
 *  All rights reserved.
 *
 */
 
 #include "glfem.h"
 #include <stdlib.h>

 #include "preProcessorMain.h"

void preProcessorMain(void) {
   

   //
   // -1- Defining the geometry
   //

   // Initializing a default geometry structure for this problem called theGeometry
   geoInitialize();
   femGeo *theGeometry = geoGetGeometry();
   
   // setting the global geometry mesh size
   theGeometry->h = 0.05;
   
   // creating the geometry and the mesh
   geoMeshGenerate();
   
   // importing the mesh into the theGeometry structure
   geoMeshImport();
   printf("\n>> From main:\n");
   printf("\tNumber of raw nodes: %d\n", theGeometry->theNodes->nNodes);
   printf("\tNumber of domains: %d\n", theGeometry->nDomains);
   printf("\n>> Raw mesh successfully imported into theGeometry structure\n\n");

   
   //
   // -2- Defining the problem
   //

   // material and physical constants
   double E = 211.e9; // Young's modulus
   double nu = 0.3; // Poisson's ratio
   double rho = 7.85e3;
   double g = -9.81;

   // creating the problem structure
   femProblem *theProblem = femElasticityCreate(theGeometry, E, nu, rho, g, PLANAR_STRESS);
   printf(">> theProblem created\n");

   
   // iteratively naming the boundaries and setting the condition if needed
   int numberOfDomains = theProblem->geometry->nDomains;
   for (int iDom = 0; iDom < numberOfDomains; iDom++) {
      
      if (iDom == 12) {
         geoSetDomainName(iDom, "Bottom Contact Surface");
         femElasticityAddBoundaryCondition(theProblem, "Bottom Contact Surface", DIRICHLET_Y, 0.0);
      }
      if (iDom == 13) {
         geoSetDomainName(iDom, "Top Contact Surface");
         femElasticityAddBoundaryCondition(theProblem, "Top Contact Surface", NEUMANN_Y, 5e9);
      }

   }

   // display and export theProblem into problem.txt for use in solver and postProcessor
   femElasticityPrint(theProblem);

   // exporting the entire raw mesh into the mesh_fixed.txt file and cleaning it up
   geoMeshWrite("../data/mesh_raw.txt");
   printf("\n>> Finished exporting raw mesh data to PreProcessor/data/mesh_raw.txt\n");
   printf("\n>> Cleaning up raw mesh data\n");
   system("python3 ../src/PreProcessor/src/fixmesh.py ../data/mesh_raw.txt ../data/mesh_fixed.txt");
   printf(">> Done cleaning mesh. New connected mesh at /data/mesh_fixed.txt\n");

   // reloading fixed mesh into theGeometry
   geoMeshRead("../data/mesh_fixed.txt");

}