/*
*  main.c
*  Library for EPL1110 : Finite Elements for dummies
*  Elasticite lineaire plane
*  
*  PostProcessor for the finite element method
*
*  Copyright (C) 2024 UCL-IMMC : Vincent Legat
*  All rights reserved.
*
*/

#include "fem.h"
#include "glfem.h"

#include "postProcessorMain.h"

int postProcessorMain(void) {

    printf("\n\n    V : Mesh and displacement norm \n");
    printf("    D : Domains \n");
    // printf("    X : Horizontal residuals for unconstrained equations \n");
    // printf("    Y : Horizontal residuals for unconstrained equations \n");
    printf("    N : Next domain highlighted\n\n\n");

    // initialiser et remplir theGeometry
    femGeo* theGeometry = geoGetGeometry();
    geoMeshRead("../data/mesh.txt");

    femProblem* theProblem;

    // initialiser et remplir theProblem en se basant sur la geometrie
    femProblem* theProblem = femProblemRead(theGeometry, "../data/problem.txt");
    
    // initializer un espace et importer la soluiton
    double* theSoluce = theProblem->soluce;
    int nNodes = theGeometry->theNodes->nNodes;
    femSolutionRead(2*nNodes, theSoluce, "../data/nodal_displacements.txt");
    femElasticityPrint(theProblem);


    

    
    //
    //  -4- Deformation du maillage pour le plot final
    //      Creation du champ de la norme du deplacement
    //

    femNodes *theNodes = theGeometry->theNodes;
    double deformationFactor = 1e0;
    double *normDisplacement = malloc(theNodes->nNodes * sizeof(double));

    for (int i=0; i<theNodes->nNodes; i++){
        theNodes->X[i] += theSoluce[2*i+0]*deformationFactor;
        theNodes->Y[i] += theSoluce[2*i+1]*deformationFactor;
        normDisplacement[i] = sqrt(theSoluce[2*i+0]*theSoluce[2*i+0] + theSoluce[2*i+1]*theSoluce[2*i+1]);
    }

    double hMin = femMin(normDisplacement,theNodes->nNodes);  
    double hMax = femMax(normDisplacement,theNodes->nNodes);  
    printf(" ==== Minimum displacement          : %14.7e [m] \n",hMin);
    printf(" ==== Maximum displacement          : %14.7e [m] \n",hMax);



    //
    //  -6- Visualisation du maillage
    //
    
    int mode = 1; 
    int domain = 0;
    int freezingButton = FALSE;
    double t, told = 0;
    char theMessage[MAXNAME];
   
 
    GLFWwindow* window = glfemInit("EPL1110 : Project 2024-25 : Deformation of a Carabiner Under Longitudinal Load");
    glfwMakeContextCurrent(window);

    do {
        int w,h;
        glfwGetFramebufferSize(window,&w,&h);
        glfemReshapeWindows(theGeometry->theNodes,w,h);

        t = glfwGetTime();  
        if (glfwGetKey(window,'D') == GLFW_PRESS) { mode = 0;}
        if (glfwGetKey(window,'V') == GLFW_PRESS) { mode = 1;}
        // if (glfwGetKey(window,'X') == GLFW_PRESS) { mode = 2;}
        // if (glfwGetKey(window,'Y') == GLFW_PRESS) { mode = 3;}
        if (glfwGetKey(window,'N') == GLFW_PRESS && freezingButton == FALSE) { domain++; freezingButton = TRUE; told = t;}
        if (t-told > 0.5) {freezingButton = FALSE; }
        
        if (mode == 0) {
            domain = domain % theGeometry->nDomains;
            glfemPlotDomain( theGeometry->theDomains[domain]); 
            sprintf(theMessage, "%s : %d ",theGeometry->theDomains[domain]->name,domain);
            glColor3f(1.0,0.0,0.0); glfemMessage(theMessage); }
        if (mode == 1) {
            glfemPlotField(theGeometry->theElements,normDisplacement);
            glfemPlotMesh(theGeometry->theElements); 
            sprintf(theMessage, "Number of elements : %d ",theGeometry->theElements->nElem);
            glColor3f(1.0,0.0,0.0); glfemMessage(theMessage); }
        // if (mode == 2) {
        //     glfemPlotField(theGeometry->theElements,forcesX);
        //     glfemPlotMesh(theGeometry->theElements); 
        //     sprintf(theMessage, "Number of elements : %d ",theGeometry->theElements->nElem);
        //     glColor3f(1.0,0.0,0.0); glfemMessage(theMessage); }
        // if (mode == 3) {
        //     glfemPlotField(theGeometry->theElements,forcesY);
        //     glfemPlotMesh(theGeometry->theElements); 
        //     sprintf(theMessage, "Number of elements : %d ",theGeometry->theElements->nElem);
        //     glColor3f(1.0,0.0,0.0); glfemMessage(theMessage); }
         glfwSwapBuffers(window);
         glfwPollEvents();
    } while( glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) != 1 );
            
    // Check if the ESC key was pressed or the window was closed

    free(normDisplacement);
    // free(forcesX);
    // free(forcesY);
    femElasticityFree(theProblem) ; 
    geoFinalize();
    glfwTerminate(); 
    
    exit(EXIT_SUCCESS);
    return 0;  
}