/*
 *  fem.c
 *  Library for LEPL1110 : Finite Elements for dummies
 *
 *  Copyright (C) 2021 UCL-IMMC : Vincent Legat
 *  All rights reserved.
 *
 */

#include "fem.h"

femGeo theGeometry;

femGeo *geoGetGeometry(void) { // return a pointer to the geometry structure
    return &theGeometry;
}

double geoSizeDefault(double x, double y) { // return the global mesh size
    return theGeometry.h;
}

double geoGmshSize(int dim, int tag, double x, double y, double z, double lc, void *data) { // return size of the mesh
    return theGeometry.geoSize(x, y);
}

void geoInitialize(void) { // ititialize the an empty geometry structure
    int ierr;
    theGeometry.geoSize = geoSizeDefault;
    gmshInitialize(0, NULL, 1, 0, &ierr);
    ErrorGmsh(ierr);
    gmshModelAdd("MyGeometry", &ierr);
    ErrorGmsh(ierr);
    gmshModelMeshSetSizeCallback(geoGmshSize, NULL, &ierr);
    ErrorGmsh(ierr);
    theGeometry.theNodes = NULL;
    theGeometry.theElements = NULL;
    theGeometry.theEdges = NULL;
    theGeometry.nDomains = 0;
    theGeometry.theDomains = NULL;
}


// carabiner open
    // geoSetDomainName(12,"Bottom Contact Surface");
    // geoSetDomainName(13,"Top Contact Surface");
// void geoMeshGenerate() {
//     femGeo* theGeometry = geoGetGeometry();

//     // double w = theGeometry->LxPlate;
//     // double h = theGeometry->LyPlate;

//     int ierr; // the canvas
//     double centerSx = 0.0; // point 1
//     double centerSy = 0.0;
//     double centerBx = 0.0; // point 2
//     double centerBy = 8.0;

//     double z = 0.0; // z component
//     double pointMeshSize = 1.0;
    
//     double radiusBO = 4.0; // big outer
//     double radiusSO = 2.0; // small outer

//     // creating all the points
//     int idCenterS = gmshModelOccAddPoint(centerSx, centerSy, z, pointMeshSize, 1, &ierr); 
//     int idCenterB = gmshModelOccAddPoint(centerBx, centerBy, z, pointMeshSize, 2, &ierr);

//     gmshModelOccAddPoint(-1.2, 0.0, z, pointMeshSize, 3, &ierr);
//     gmshModelOccAddPoint(-0.2, 0.0, z, pointMeshSize, 4, &ierr);
//     gmshModelOccAddPoint(-0.2, -1.0, z, pointMeshSize, 5, &ierr);
//     gmshModelOccAddPoint(0.2, -1.0, z, pointMeshSize, 6, &ierr);
//     gmshModelOccAddPoint(0.2, 0.0, z, pointMeshSize, 7, &ierr);
//     gmshModelOccAddPoint(1.2, 0.0, z, pointMeshSize, 8, &ierr);
//     gmshModelOccAddPoint(0.0, -2.0, z, pointMeshSize, 9, &ierr);
//     gmshModelOccAddPoint(2.0, 0.0, z, pointMeshSize, 10, &ierr);
//     gmshModelOccAddPoint(-2.0, 0.0, z, pointMeshSize, 11, &ierr);
//     gmshModelOccAddPoint(-3.0, 8.0, z, pointMeshSize, 12, &ierr);
//     gmshModelOccAddPoint(-0.2, 8.0, z, pointMeshSize, 13, &ierr);
//     gmshModelOccAddPoint(-0.2, 10.8, z, pointMeshSize, 14, &ierr);
//     gmshModelOccAddPoint(0.2, 10.8, z, pointMeshSize, 15, &ierr);
//     gmshModelOccAddPoint(0.2, 8.0, z, pointMeshSize, 16, &ierr);
//     gmshModelOccAddPoint(3.0, 8.0, z, pointMeshSize, 17, &ierr);
//     gmshModelOccAddPoint(4.0, 8.0, z, pointMeshSize, 18, &ierr);
//     gmshModelOccAddPoint(0.0, 12.0, z, pointMeshSize, 19, &ierr);
//     gmshModelOccAddPoint(-4.0, 8.0, z, pointMeshSize, 20, &ierr);

//     // creating the circle arcs
//     int idArc1 = gmshModelOccAddCircleArc(3, 4, 5, 21, TRUE, &ierr);
//     int idArc2 = gmshModelOccAddCircleArc(6, 7, 8, 22, TRUE, &ierr);
//     int idArc3 = gmshModelOccAddCircleArc(9, 1, 10, 23, TRUE, &ierr);
//     int idArc4 = gmshModelOccAddCircleArc(9, 1, 11, 24, TRUE, &ierr);
//     int idArc5 = gmshModelOccAddCircleArc(12, 13, 14, 25, TRUE, &ierr);
//     int idArc6 = gmshModelOccAddCircleArc(15, 16, 17, 26, TRUE, &ierr);
//     int idArc7 = gmshModelOccAddCircleArc(18, 2, 19, 27, TRUE, &ierr);
//     int idArc8 = gmshModelOccAddCircleArc(19, 2, 20, 28, TRUE, &ierr);

//     // creating the lines
//     int idLine9 = gmshModelOccAddLine(3, 12, 29, &ierr);
//     int idLine10 = gmshModelOccAddLine(8, 17, 30, &ierr);
//     int idLine11 = gmshModelOccAddLine(11, 20, 31, &ierr);
//     int idLine12 = gmshModelOccAddLine(10, 18, 32, &ierr);
//     int idLine13 = gmshModelOccAddLine(5, 6, 33, &ierr);
//     int idLine14 = gmshModelOccAddLine(14, 15, 34, &ierr);

//     // creating the loops
//     int outer_loop_tags[] = {idArc3, idArc4, idLine11, idArc8, idArc7, idLine12};
//     int idLoopO = gmshModelOccAddCurveLoop(outer_loop_tags, 6, 35, &ierr);
//     int inner_loop_tags[] = {idArc2, idLine13, idArc1, idLine9, idArc5, idLine14, idArc6, idLine10};
//     int idLoopI = gmshModelOccAddCurveLoop(inner_loop_tags, 8, 36, &ierr);

//     // creating the surface
//     int surface_tags[] = {idLoopO, idLoopI};
//     int idSurface = gmshModelOccAddPlaneSurface(surface_tags, 2, 37, &ierr);

//     // creating the rectangular slice
//     int idRectSlice = gmshModelOccAddRectangle(2.0, 5.0, z, 2.0, 1.0, 38, 0, &ierr);

//     // perform boolean cut
//     int body[] = {2, idSurface};
//     int cut[] = {2, idRectSlice};

//     int *cutresult;
//     size_t cutresult_n;
//     gmshModelOccCut(body, 2, cut, 2, &cutresult, &cutresult_n, NULL, NULL, NULL, 39, 1, 1, &ierr);
    
//     gmshModelOccSynchronize(&ierr);

//     if (theGeometry->elementType == FEM_QUAD) {
//         gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
//         gmshOptionSetNumber("Mesh.RecombineAll",1,&ierr);
//         gmshOptionSetNumber("Mesh.Algorithm",11,&ierr);  
//         gmshOptionSetNumber("Mesh.SmoothRatio", 21.5, &ierr);  
//         gmshOptionSetNumber("Mesh.RecombinationAlgorithm",1.0,&ierr); 
//         gmshModelGeoMeshSetRecombine(2,1,45,&ierr);  
//         gmshModelMeshGenerate(2,&ierr);  }
    
//     if (theGeometry->elementType == FEM_TRIANGLE) {
//         gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
//         gmshModelMeshGenerate(2,&ierr);}

//     return;
// }

// carabiner closed
// geoSetDomainName(12,"Bottom Contact Surface");
// geoSetDomainName(13,"Top Contact Surface");
void geoMeshGenerate() {
    femGeo* theGeometry = geoGetGeometry();

    // double w = theGeometry->LxPlate;
    // double h = theGeometry->LyPlate;

    int ierr; // the canvas
    double centerSx = 0.0; // point 1
    double centerSy = 0.0;
    double centerBx = 0.0; // point 2
    double centerBy = 8.0;

    double z = 0.0; // z component
    double pointMeshSize = 1.0;
    
    double radiusBO = 4.0; // big outer
    double radiusSO = 2.0; // small outer

    // creating all the points
    int idCenterS = gmshModelOccAddPoint(centerSx, centerSy, z, pointMeshSize, 1, &ierr); 
    int idCenterB = gmshModelOccAddPoint(centerBx, centerBy, z, pointMeshSize, 2, &ierr);

    gmshModelOccAddPoint(-0.2, 0.0, z, pointMeshSize, 4, &ierr);
    gmshModelOccAddPoint(-1.2, 0.0, z, pointMeshSize, 3, &ierr);
    gmshModelOccAddPoint(-0.2, -1.0, z, pointMeshSize, 5, &ierr);
    gmshModelOccAddPoint(0.2, -1.0, z, pointMeshSize, 6, &ierr);
    gmshModelOccAddPoint(0.2, 0.0, z, pointMeshSize, 7, &ierr);
    gmshModelOccAddPoint(1.2, 0.0, z, pointMeshSize, 8, &ierr);
    gmshModelOccAddPoint(0.0, -2.0, z, pointMeshSize, 9, &ierr);
    gmshModelOccAddPoint(2.0, 0.0, z, pointMeshSize, 10, &ierr);
    gmshModelOccAddPoint(-2.0, 0.0, z, pointMeshSize, 11, &ierr);
    gmshModelOccAddPoint(-3.0, 8.0, z, pointMeshSize, 12, &ierr);
    gmshModelOccAddPoint(-0.2, 8.0, z, pointMeshSize, 13, &ierr);
    gmshModelOccAddPoint(-0.2, 10.8, z, pointMeshSize, 14, &ierr);
    gmshModelOccAddPoint(0.2, 10.8, z, pointMeshSize, 15, &ierr);
    gmshModelOccAddPoint(0.2, 8.0, z, pointMeshSize, 16, &ierr);
    gmshModelOccAddPoint(3.0, 8.0, z, pointMeshSize, 17, &ierr);
    gmshModelOccAddPoint(4.0, 8.0, z, pointMeshSize, 18, &ierr);
    gmshModelOccAddPoint(0.0, 12.0, z, pointMeshSize, 19, &ierr);
    gmshModelOccAddPoint(-4.0, 8.0, z, pointMeshSize, 20, &ierr);

    // creating the circle arcs
    int idArc1 = gmshModelOccAddCircleArc(3, 4, 5, 21, TRUE, &ierr);
    int idArc2 = gmshModelOccAddCircleArc(6, 7, 8, 22, TRUE, &ierr);
    int idArc3 = gmshModelOccAddCircleArc(9, 1, 10, 23, TRUE, &ierr);
    int idArc4 = gmshModelOccAddCircleArc(9, 1, 11, 24, TRUE, &ierr);
    int idArc5 = gmshModelOccAddCircleArc(12, 13, 14, 25, TRUE, &ierr);
    int idArc6 = gmshModelOccAddCircleArc(15, 16, 17, 26, TRUE, &ierr);
    int idArc7 = gmshModelOccAddCircleArc(18, 2, 19, 27, TRUE, &ierr);
    int idArc8 = gmshModelOccAddCircleArc(19, 2, 20, 28, TRUE, &ierr);

    // creating the lines
    int idLine9 = gmshModelOccAddLine(3, 12, 29, &ierr);
    int idLine10 = gmshModelOccAddLine(8, 17, 30, &ierr);
    int idLine11 = gmshModelOccAddLine(11, 20, 31, &ierr);
    int idLine12 = gmshModelOccAddLine(10, 18, 32, &ierr);
    int idLine13 = gmshModelOccAddLine(5, 6, 33, &ierr);
    int idLine14 = gmshModelOccAddLine(14, 15, 34, &ierr);

    // creating the loops
    int outer_loop_tags[] = {idArc3, idArc4, idLine11, idArc8, idArc7, idLine12};
    int idLoopO = gmshModelOccAddCurveLoop(outer_loop_tags, 6, 35, &ierr);
    int inner_loop_tags[] = {idArc2, idLine13, idArc1, idLine9, idArc5, idLine14, idArc6, idLine10};
    int idLoopI = gmshModelOccAddCurveLoop(inner_loop_tags, 8, 36, &ierr);

    // creating the surface
    int surface_tags[] = {idLoopO, idLoopI};
    int idSurface = gmshModelOccAddPlaneSurface(surface_tags, 2, 37, &ierr);

    gmshModelOccSynchronize(&ierr);

    if (theGeometry->elementType == FEM_QUAD) {
        gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
        gmshOptionSetNumber("Mesh.RecombineAll",1,&ierr);
        gmshOptionSetNumber("Mesh.Algorithm",11,&ierr);  
        gmshOptionSetNumber("Mesh.SmoothRatio", 21.5, &ierr);  
        gmshOptionSetNumber("Mesh.RecombinationAlgorithm",1.0,&ierr); 
        gmshModelGeoMeshSetRecombine(2,1,45,&ierr);  
        gmshModelMeshGenerate(2,&ierr);  }
  
    if (theGeometry->elementType == FEM_TRIANGLE) {
        gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
        gmshModelMeshGenerate(2,&ierr);}

    return;
}

// square with a hole
// void geoMeshGenerate(void) { // generate the geometry and the mesh

        // geoSetDomainName(0, "Top");
        // geoSetDomainName(1, "Right");
        // geoSetDomainName(2, "Bottom");
        // geoSetDomainName(3, "Left");
        // geoSetDomainName(4, "Hole");

//     femGeo* theGeometry = geoGetGeometry(); // pointer to the structure that will be filled

//     theGeometry->elementType = FEM_TRIANGLE; // setting mesh type

//     // setting the basic geometry dimensions
//     double Lx = 10.0;
//     double Ly = 10.0;
//     theGeometry->LxPlate = Lx;
//     theGeometry->LyPlate = Ly;
//     double w = theGeometry->LxPlate;
//     double h = theGeometry->LyPlate;

//     // HERE SHOULD PARTICULAR ELEMENTS SPECIFIC TO THE GEOMETRY LIKE HOLES OR NOTCHES OR POINTS ARUND WHICH THE MESH SHOULD BE FINER OR WHATEVER

//     // then the main geometry
//     int ierr;

//     double z = 0.0;
//     double point_mesh_size = 1.0;
//     double side_length = theGeometry->LxPlate;

//     // creating all the points
//     gmshModelOccAddPoint(-side_length/2, side_length, z, point_mesh_size, 1, &ierr);
//     gmshModelOccAddPoint(side_length/2, side_length, z, point_mesh_size, 2, &ierr);
//     gmshModelOccAddPoint(side_length/2, 0.0, z, point_mesh_size, 3, &ierr);
//     gmshModelOccAddPoint(-side_length/2, 0.0, z, point_mesh_size, 4, &ierr);

//     // creating the edges
//     int idLineTop = gmshModelOccAddLine(1, 2, 5, &ierr);
//     int idLineRight = gmshModelOccAddLine(2, 3, 6, &ierr);
//     int idLineBottom = gmshModelOccAddLine(3, 4, 7, &ierr);
//     int idLineLeft = gmshModelOccAddLine(4, 1, 8, &ierr);
//     int idHole = gmshModelOccAddCircle(0.0, 5.0, z, 1.0, 9, 0.0, 6.28318530717958647692, NULL, NULL, NULL, NULL, &ierr);


//     // creating the loops
//     int outer_loop_tags[] = {idLineTop, idLineRight, idLineBottom, idLineLeft};
//     int idLoopO = gmshModelOccAddCurveLoop(outer_loop_tags, 4, 10, &ierr);
//     int inner_loop_tags[] = {idHole};
//     int idLoopI = gmshModelOccAddCurveLoop(inner_loop_tags, 1, 11, &ierr);

//     // creating the surface
//     int surface_tags[] = {idLoopO, idLoopI};
//     int idSurface = gmshModelOccAddPlaneSurface(surface_tags, 2, 12, &ierr);
    
//     gmshModelOccSynchronize(&ierr);


//     if (theGeometry->elementType == FEM_QUAD) {
//         gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
//         gmshOptionSetNumber("Mesh.RecombineAll",1,&ierr);
//         gmshOptionSetNumber("Mesh.Algorithm",11,&ierr);  
//         gmshOptionSetNumber("Mesh.SmoothRatio", 21.5, &ierr);  
//         gmshOptionSetNumber("Mesh.RecombinationAlgorithm",1.0,&ierr); 
//         gmshModelGeoMeshSetRecombine(2,1,45,&ierr);  
//         gmshModelMeshGenerate(2,&ierr);  }
  
//     if (theGeometry->elementType == FEM_TRIANGLE) {
//         gmshOptionSetNumber("Mesh.SaveAll",1,&ierr);
//         gmshModelMeshGenerate(2,&ierr);}

//     return;
// }

void geoMeshImport(void) { // import the mesh into the geometry structure
    
    // HERE I COULD ADD SOME CODE TO CLEAN UP THE MESH BEFORE PUTTING IT INTO THE STRUCTURE
    // LIKE REMOVING UNUSED NODES AND EDGES 
    // THIS VERSION JUST IMPORTS THE RAW DATA DIRECTLY INTO THE STRUCTURE WITHOUT ANY EXTRA PROCESSING
    // THIS WILL DO FOR NOW TO KEEP IT SIMPLE
    
    int ierr;
    
    /* Importing nodes */
    
    size_t nNode,n,m,*node;
    double *xyz,*trash;
    gmshModelMeshGetNodes(&node,&nNode,&xyz,&n,
                         &trash,&m,-1,-1,0,0,&ierr);          ErrorGmsh(ierr);                         
    femNodes *theNodes = malloc(sizeof(femNodes));
    theNodes->nNodes = nNode;
    theNodes->X = malloc(sizeof(double)*(theNodes->nNodes));
    theNodes->Y = malloc(sizeof(double)*(theNodes->nNodes));
    for (int i = 0; i < theNodes->nNodes; i++){
        theNodes->X[i] = xyz[3*node[i]-3];
        theNodes->Y[i] = xyz[3*node[i]-2]; }
    theGeometry.theNodes = theNodes;
    gmshFree(node);
    gmshFree(xyz);
    gmshFree(trash);
    printf("Geo     : Importing %d nodes \n",theGeometry.theNodes->nNodes);
       
    /* Importing elements */
    /* Pas super joli : a ameliorer pour eviter la triple copie */
        
    size_t nElem, *elem;
    gmshModelMeshGetElementsByType(1,&elem,&nElem,
                               &node,&nNode,-1,0,1,&ierr);    ErrorGmsh(ierr);
    femMesh *theEdges = malloc(sizeof(femMesh));
    theEdges->nLocalNode = 2;
    theEdges->nodes = theNodes;
    theEdges->nElem = nElem;  
    theEdges->elem = malloc(sizeof(int)*2*theEdges->nElem);
    for (int i = 0; i < theEdges->nElem; i++)
        for (int j = 0; j < theEdges->nLocalNode; j++)
            theEdges->elem[2*i+j] = node[2*i+j]-1;  
    theGeometry.theEdges = theEdges;
    int shiftEdges = elem[0];
    gmshFree(node);
    gmshFree(elem);
    printf("Geo     : Importing %d edges \n",theEdges->nElem);
  
    gmshModelMeshGetElementsByType(2,&elem,&nElem,
                               &node,&nNode,-1,0,1,&ierr);    ErrorGmsh(ierr);
    if (nElem != 0) {
      femMesh *theElements = malloc(sizeof(femMesh));
      theElements->nLocalNode = 3;
      theElements->nodes = theNodes;
      theElements->nElem = nElem;  
      theElements->elem = malloc(sizeof(int)*3*theElements->nElem);
      for (int i = 0; i < theElements->nElem; i++)
          for (int j = 0; j < theElements->nLocalNode; j++)
              theElements->elem[3*i+j] = node[3*i+j]-1;  
      theGeometry.theElements = theElements;
      gmshFree(node);
      gmshFree(elem);
      printf("Geo     : Importing %d triangles \n",theElements->nElem); }
    
    int nElemTriangles = nElem;
    gmshModelMeshGetElementsByType(3,&elem,&nElem,
                               &node,&nNode,-1,0,1,&ierr);    ErrorGmsh(ierr);
    if (nElem != 0 && nElemTriangles != 0)  
      Error("Cannot consider hybrid geometry with triangles and quads :-(");                       
                               
    if (nElem != 0) {
      femMesh *theElements = malloc(sizeof(femMesh));
      theElements->nLocalNode = 4;
      theElements->nodes = theNodes;
      theElements->nElem = nElem;  
      theElements->elem = malloc(sizeof(int)*4*theElements->nElem);
      for (int i = 0; i < theElements->nElem; i++)
          for (int j = 0; j < theElements->nLocalNode; j++)
              theElements->elem[4*i+j] = node[4*i+j]-1;  
      theGeometry.theElements = theElements;
      gmshFree(node);
      gmshFree(elem);
      printf("Geo     : Importing %d quads \n",theElements->nElem); }

    
    /* Importing 1D entities */
  
    int *dimTags;
    gmshModelGetEntities(&dimTags,&n,1,&ierr);        ErrorGmsh(ierr);
    theGeometry.nDomains = n/2;
    theGeometry.theDomains = malloc(sizeof(femDomain*)*n/2);
    printf("Geo     : Importing %d entities \n",theGeometry.nDomains);
    printf("\nNumber of domains: %d\n", theGeometry.nDomains);

    for (int i=0; i < n/2; i++) {
        int dim = dimTags[2*i+0];
        int tag = dimTags[2*i+1];
        femDomain *theDomain = malloc(sizeof(femDomain)); 
        theGeometry.theDomains[i] = theDomain;
        theDomain->mesh = theEdges;
        sprintf(theDomain->name, "Entity %d ",tag-1);
         
        int *elementType;
        size_t nElementType, **elementTags, *nElementTags, nnElementTags, **nodesTags, *nNodesTags, nnNodesTags; 
        gmshModelMeshGetElements(&elementType, &nElementType, &elementTags, &nElementTags, &nnElementTags, &nodesTags, &nNodesTags, &nnNodesTags, dim, tag, &ierr);
        theDomain->nElem = nElementTags[0];
        theDomain->elem = malloc(sizeof(int)*2*theDomain->nElem); 
        for (int j = 0; j < theDomain->nElem; j++) {
            theDomain->elem[j] = elementTags[0][j] - shiftEdges; }
        printf("Geo     : Entity %d : %d elements \n",i,theDomain->nElem);
        gmshFree(nElementTags);
        gmshFree(nNodesTags);
        gmshFree(elementTags);
        gmshFree(nodesTags);
        gmshFree(elementType);
        printf(">> Done with domain n°%d\n",i);
    }
    gmshFree(dimTags);
 
    printf("\n>> geoMeshImport() finished");
    return;

}

// write the geometry data into the provided file in human readable format
void geoMeshWrite(const char *filename) {
    FILE* file = fopen(filename,"w");
    if (!file) {
        printf("Error! Unable to open file at %s\n", filename);
        exit(-1);
    }

    femNodes *theNodes = theGeometry.theNodes;
    fprintf(file, "Number of nodes %d \n", theNodes->nNodes);
    for (int i = 0; i < theNodes->nNodes; i++) {
        fprintf(file,"%6d : %14.7e %14.7e \n",i,theNodes->X[i],theNodes->Y[i]);
    }
    
    femMesh *theEdges = theGeometry.theEdges;
    fprintf(file,"Number of edges %d \n", theEdges->nElem);
    int *elem = theEdges->elem;
    for (int i = 0; i < theEdges->nElem; i++) {
        fprintf(file,"%6d : %6d %6d \n",i,elem[2*i],elem[2*i+1]);
    }
    
    femMesh *theElements = theGeometry.theElements;
    if (theElements->nLocalNode == 3) {
        fprintf(file,"Number of triangles %d \n", theElements->nElem);
        elem = theElements->elem;
        for (int i = 0; i < theElements->nElem; i++) {
            fprintf(file,"%6d : %6d %6d %6d\n",i,elem[3*i],elem[3*i+1],elem[3*i+2]);
        }
    }
    if (theElements->nLocalNode == 4) {
        fprintf(file,"Number of quads %d \n", theElements->nElem);
        elem = theElements->elem;
        for (int i = 0; i < theElements->nElem; i++) {
            fprintf(file,"%6d : %6d %6d %6d %6d\n",i,elem[4*i],elem[4*i+1],elem[4*i+2],elem[4*i+3]);
        }
    }
    
    int nDomains = theGeometry.nDomains;
    fprintf(file,"Number of domains %d\n", nDomains);
    for (int iDomain = 0; iDomain < nDomains; iDomain++) {
        femDomain *theDomain = theGeometry.theDomains[iDomain];
        fprintf(file,"  Domain : %6d \n", iDomain);
        fprintf(file,"  Name : %s\n", theDomain->name);
        fprintf(file,"  Number of elements : %6d\n", theDomain->nElem);
        for (int i=0; i < theDomain->nElem; i++){
            fprintf(file,"%6d",theDomain->elem[i]);
            if ((i+1) != theDomain->nElem  && (i+1) % 10 == 0) fprintf(file,"\n");
        }
        fprintf(file,"\n");
    }

    fclose(file);
}

// read a mesh file and save its contents into theGeometry structure
void geoMeshRead(const char *filename)
{
   FILE* file = fopen(filename,"r");
   
   int trash, *elem;
   
   femNodes *theNodes = malloc(sizeof(femNodes));
   theGeometry.theNodes = theNodes;
   ErrorScan(fscanf(file, "Number of nodes %d \n", &theNodes->nNodes));
   theNodes->X = malloc(sizeof(double)*(theNodes->nNodes));
   theNodes->Y = malloc(sizeof(double)*(theNodes->nNodes));
   for (int i = 0; i < theNodes->nNodes; i++) {
       ErrorScan(fscanf(file,"%d : %le %le \n",&trash,&theNodes->X[i],&theNodes->Y[i]));} 

   femMesh *theEdges = malloc(sizeof(femMesh));
   theGeometry.theEdges = theEdges;
   theEdges->nLocalNode = 2;
   theEdges->nodes = theNodes;
   ErrorScan(fscanf(file, "Number of edges %d \n", &theEdges->nElem));
   theEdges->elem = malloc(sizeof(int)*theEdges->nLocalNode*theEdges->nElem);
   for(int i=0; i < theEdges->nElem; ++i) {
        elem = theEdges->elem;
        ErrorScan(fscanf(file, "%6d : %6d %6d \n", &trash,&elem[2*i],&elem[2*i+1])); }
  
   femMesh *theElements = malloc(sizeof(femMesh));
   theGeometry.theElements = theElements;
   theElements->nLocalNode = 0;
   theElements->nodes = theNodes;
   char elementType[MAXNAME];  
   ErrorScan(fscanf(file, "Number of %s %d \n",elementType,&theElements->nElem));  
   if (strncasecmp(elementType,"triangles",MAXNAME) == 0) {
      theElements->nLocalNode = 3;
      theElements->elem = malloc(sizeof(int)*theElements->nLocalNode*theElements->nElem);
      for(int i=0; i < theElements->nElem; ++i) {
          elem = theElements->elem;
          ErrorScan(fscanf(file, "%6d : %6d %6d %6d \n", 
                    &trash,&elem[3*i],&elem[3*i+1],&elem[3*i+2])); }}
   if (strncasecmp(elementType,"quads",MAXNAME) == 0) {
      theElements->nLocalNode = 4;
      theElements->elem = malloc(sizeof(int)*theElements->nLocalNode*theElements->nElem);
      for(int i=0; i < theElements->nElem; ++i) {
          elem = theElements->elem;
          ErrorScan(fscanf(file, "%6d : %6d %6d %6d %6d \n", 
                    &trash,&elem[4*i],&elem[4*i+1],&elem[4*i+2],&elem[4*i+3])); }}
           
   ErrorScan(fscanf(file, "Number of domains %d\n", &theGeometry.nDomains));
   int nDomains = theGeometry.nDomains;
   theGeometry.theDomains = malloc(sizeof(femDomain*)*nDomains);
   for (int iDomain = 0; iDomain < nDomains; iDomain++) {
      femDomain *theDomain = malloc(sizeof(femDomain)); 
      theGeometry.theDomains[iDomain] = theDomain;
      theDomain->mesh = theEdges; 
      ErrorScan(fscanf(file,"  Domain : %6d \n", &trash));
      ErrorScan(fscanf(file,"  Name : %[^\n]s \n", (char*)&theDomain->name));
      ErrorScan(fscanf(file,"  Number of elements : %6d\n", &theDomain->nElem));
      theDomain->elem = malloc(sizeof(int)*2*theDomain->nElem); 
      for (int i=0; i < theDomain->nElem; i++){
          ErrorScan(fscanf(file,"%6d",&theDomain->elem[i]));
          if ((i+1) != theDomain->nElem  && (i+1) % 10 == 0) ErrorScan(fscanf(file,"\n")); }}
    
   fclose(file);
}

// set a domain name for given domain number
void geoSetDomainName(int iDomain, char *name) {
    if (iDomain >= theGeometry.nDomains){
        Error("Illegal domain number");
    }
    if (geoGetDomain(name) != -1) {
        Error("Cannot use the same name for two domains");
    }
    sprintf(theGeometry.theDomains[iDomain]->name,"%s",name);
} 

// retireve domain number from the name
int geoGetDomain(char *name) {
    int theIndex = -1;
    int nDomains = theGeometry.nDomains;
    for (int iDomain = 0; iDomain < nDomains; iDomain++) {
        femDomain *theDomain = theGeometry.theDomains[iDomain];
        if (strncasecmp(name,theDomain->name,MAXNAME) == 0) {
            theIndex = iDomain;
        }
    }
    return theIndex;        
}






/*
*
* PROBLEM FILE FUNCTIONS
*
*/
void femProblemWrite(femProblem *theProblem, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
      printf("Error at %s:%d\nUnable to open file %s\n", __FILE__, __LINE__, filename);
      exit(-1);
    }
  
    switch (theProblem->planarStrainStress) {
    case PLANAR_STRESS:
      fprintf(file, "Type of problem    :  Planar stresses  \n");
      break;
    case PLANAR_STRAIN:
      fprintf(file, "Type of problem    :  Planar strains \n");
      break;
    case AXISYM:
      fprintf(file, "Type of problem    :  Axi-symetric problem \n");
      break;
    default:
      fprintf(file, "Type of problem    :  Undefined  \n");
      break;
    }
    fprintf(file, "Young modulus      : %14.7e  \n", theProblem->E);
    fprintf(file, "Poisson ratio      : %14.7e  \n", theProblem->nu);
    fprintf(file, "Mass density       : %14.7e  \n", theProblem->rho);
    fprintf(file, "Gravity-Y          : %14.7e  \n", theProblem->g);
  
    for (int i = 0; i < theProblem->nBoundaryConditions; i++) {
      femBoundaryCondition *theCondition = theProblem->conditions[i];
      double value = theCondition->value;
      fprintf(file, "Boundary condition : ");
      switch (theCondition->type) {
      case DIRICHLET_X:
        fprintf(file, " Dirichlet-X        = %14.7e", value);
        break;
      case DIRICHLET_Y:
        fprintf(file, " Dirichlet-Y        = %14.7e", value);
        break;
      case NEUMANN_X:
        fprintf(file, " Neumann-X          = %14.7e", value);
        break;
      case NEUMANN_Y:
        fprintf(file, " Neumann-Y          = %14.7e", value);
        break;
      default:
        fprintf(file, " Undefined          = %14.7e", NAN);
        break;
      }

      fprintf(file, ": %s\n", theCondition->domain->name);
    }
    fclose(file);
}


/*
*
* ELASTICITY FUNCTIONS
*
*/

// initializing and filling the femProblem structure with everything needed for the FE analysis (geometry, properties, integration rules, constraints)
femProblem *femElasticityCreate(femGeo* theGeometry, double E, double nu, double rho, double g, femElasticCase iCase) {

    // NEEDS ADDITIONAL LINES IF WE WANT TO IMPLEMENT TANGENTIAL AND NORMAL CONSTRAINTS
    // ONLY WORKS FOR XY CONSTRAINTS FOR NOW
    
    femProblem *theProblem = malloc(sizeof(femProblem));
    theProblem->E   = E;
    theProblem->nu  = nu;
    theProblem->g   = g;
    theProblem->rho = rho;

    if (iCase == PLANAR_STRESS) {
        theProblem->A = E/(1-nu*nu);
        theProblem->B = E*nu/(1-nu*nu);
        theProblem->C = E/(2*(1+nu));
    }
    else if (iCase == PLANAR_STRAIN || iCase == AXISYM) {
        theProblem->A = E*(1-nu)/((1+nu)*(1-2*nu));
        theProblem->B = E*nu/((1+nu)*(1-2*nu));
        theProblem->C = E/(2*(1+nu));
    }

    theProblem->planarStrainStress = iCase;
    theProblem->nBoundaryConditions = 0;
    theProblem->conditions = NULL;

    // total number of DOF
    int size = 2*theGeometry->theNodes->nNodes;
    theProblem->constrainedNodes = malloc(size*sizeof(int));
    theProblem->soluce = malloc(size*sizeof(double));
    theProblem->residuals = malloc(size*sizeof(double));
    // initialize arrays containing constraint for each node, by default -1 meaning not constrained
    // as well as allocating and initializing the solution and residuals arrays to 0
    for (int i=0; i < size; i++) {
        theProblem->constrainedNodes[i] = -1;
        theProblem->soluce[i] = 0.0;
        theProblem->residuals[i] = 0.0;
    }

    // links mesh (now contained in theGeometry) to theProblem
    theProblem->geometry = theGeometry;  
    if (theGeometry->theElements->nLocalNode == 3) {
        theProblem->space    = femDiscreteCreate(3,FEM_TRIANGLE);
        theProblem->rule     = femIntegrationCreate(3,FEM_TRIANGLE);
    }
    if (theGeometry->theElements->nLocalNode == 4) {
        theProblem->space    = femDiscreteCreate(4,FEM_QUAD);
        theProblem->rule     = femIntegrationCreate(4,FEM_QUAD);
    }

    theProblem->spaceEdge    = femDiscreteCreate(2,FEM_EDGE);
    theProblem->ruleEdge     = femIntegrationCreate(2,FEM_EDGE); 
    theProblem->system       = femFullSystemCreate(size); 

    
    // femDiscretePrint(theProblem->space);   
    // femDiscretePrint(theProblem->spaceEdge);  

    // returns fully initialized femProblem structure (with material properties, geometry, fe spaces, condition markers and system data)
    return theProblem;
}

// freeing the problem structure
void femElasticityFree(femProblem *theProblem) {
    femFullSystemFree(theProblem->system);
    femIntegrationFree(theProblem->rule);
    femDiscreteFree(theProblem->space);
    femIntegrationFree(theProblem->ruleEdge);
    femDiscreteFree(theProblem->spaceEdge);
    free(theProblem->conditions);
    free(theProblem->constrainedNodes);
    free(theProblem->soluce);
    free(theProblem->residuals);
    free(theProblem);
}

void femElasticityPrint(femProblem *theProblem)  
{    
    printf("\n\n ======================================================================================= \n\n");
    printf(" Linear elasticity problem \n");
    printf("   Young modulus   E   = %14.7e [N/m2]\n",theProblem->E);
    printf("   Poisson's ratio nu  = %14.7e [-]\n",theProblem->nu);
    printf("   Density         rho = %14.7e [kg/m3]\n",theProblem->rho);
    printf("   Gravity         g   = %14.7e [m/s2]\n",theProblem->g);
    
    if (theProblem->planarStrainStress == PLANAR_STRAIN)  printf("   Planar strains formulation \n");
    if (theProblem->planarStrainStress == PLANAR_STRESS)  printf("   Planar stresses formulation \n");
    if (theProblem->planarStrainStress == AXISYM)         printf("   Axisymmetric formulation \n");

    printf("   Boundary conditions : \n");
    for(int i=0; i < theProblem->nBoundaryConditions; i++) {
          femBoundaryCondition *theCondition = theProblem->conditions[i];
          double value = theCondition->value;
          printf("  %20s :",theCondition->domain->name);
          if (theCondition->type==DIRICHLET_X)  printf(" imposing %9.2e as the horizontal displacement  \n",value);
          if (theCondition->type==DIRICHLET_Y)  printf(" imposing %9.2e as the vertical displacement  \n",value); 
          if (theCondition->type==NEUMANN_X)    printf(" imposing %9.2e as the horizontal force desnity \n",value); 
          if (theCondition->type==NEUMANN_Y)    printf(" imposing %9.2e as the vertical force density \n",value);}
    printf(" ======================================================================================= \n\n");
}

// define and apply the hard constraints (DIRICHLET X or Y)
void femElasticityAddBoundaryCondition(femProblem *theProblem, char *nameDomain, femBoundaryType type, double value) {
    
    // WOULD NEED TO UPDATE THIS FUNCTION IF WE WANT TO ALSO USE NORMAL OR TANGENTIAL DIRICHLET CONDITIONS
    // REMINDER: THIS FUNCTION DOES NOT DEAL WITH NEUMANN CONDITIONS YET, THEY COME LATER WHEN ASSEMBLING LOAD VECTOR

    int iDomain = geoGetDomain(nameDomain);
    if (iDomain == -1) {
        Error("Undefined domain :-(");
    }

    // create and store basic boundary information
    femBoundaryCondition* theBoundary = malloc(sizeof(femBoundaryCondition));
    theBoundary->domain = theProblem->geometry->theDomains[iDomain];
    theBoundary->value = value;
    theBoundary->type = type;

    // increase boundary condition count and add the new condition
    theProblem->nBoundaryConditions++;
    int size = theProblem->nBoundaryConditions;
    if (theProblem->conditions == NULL)
        theProblem->conditions = malloc(size*sizeof(femBoundaryCondition*));
    else 
        theProblem->conditions = realloc(theProblem->conditions, size*sizeof(femBoundaryCondition*));
    theProblem->conditions[size-1] = theBoundary;
    
    // for simple dirichlet determine which degree to constrain
    int shift=-1;
    if (type == DIRICHLET_X)
        shift = 0;      
    if (type == DIRICHLET_Y)
        shift = 1;  
    if (shift == -1) // if the condition is not one of these do nothing
        return;
    
    // update the constrainednodes array
    int *elem = theBoundary->domain->elem;
    int nElem = theBoundary->domain->nElem;
    for (int e = 0; e < nElem; e++) {
        // each edge is defined by two nodes
        for (int i = 0; i < 2; i++) {
            int node = theBoundary->domain->mesh->elem[2*elem[e]+i];
            theProblem->constrainedNodes[2*node+shift] = size-1;
        }
    }    
}







/*
*
* INTEGRATION FUNCTIONS
*
*/

// table of standard integration rule points and weights
static const double _gaussQuad4Xsi[4]    = {-0.577350269189626,-0.577350269189626, 0.577350269189626, 0.577350269189626};
static const double _gaussQuad4Eta[4]    = { 0.577350269189626,-0.577350269189626,-0.577350269189626, 0.577350269189626};
static const double _gaussQuad4Weight[4] = { 1.000000000000000, 1.000000000000000, 1.000000000000000, 1.000000000000000};
static const double _gaussTri3Xsi[3]     = { 0.166666666666667, 0.666666666666667, 0.166666666666667};
static const double _gaussTri3Eta[3]     = { 0.166666666666667, 0.166666666666667, 0.666666666666667};
static const double _gaussTri3Weight[3]  = { 0.166666666666667, 0.166666666666667, 0.166666666666667};
static const double _gaussEdge2Xsi[2]    = { 0.577350269189626,-0.577350269189626};
static const double _gaussEdge2Weight[2] = { 1.000000000000000, 1.000000000000000};

// sets up the integration method using gauss quadrature, depending on element type.
femIntegration *femIntegrationCreate(int n, femElementType type) {
    
    femIntegration *theRule = malloc(sizeof(femIntegration));

    if (type == FEM_QUAD && n == 4) {
        theRule->n      = 4;
        theRule->xsi    = _gaussQuad4Xsi;
        theRule->eta    = _gaussQuad4Eta;
        theRule->weight = _gaussQuad4Weight;
    }
    else if (type == FEM_TRIANGLE && n == 3) {
        theRule->n      = 3;
        theRule->xsi    = _gaussTri3Xsi;
        theRule->eta    = _gaussTri3Eta;
        theRule->weight = _gaussTri3Weight;
    }
    else if (type == FEM_EDGE && n == 2) {
        theRule->n      = 2;
        theRule->xsi    = _gaussEdge2Xsi;
        theRule->eta    = NULL;
        theRule->weight = _gaussEdge2Weight;
    }
    else Error("Cannot create such an integration rule !");

    return theRule; 
}

void femIntegrationFree(femIntegration *theRule) {
    free(theRule);
}







/*
*
* DISCRETISATION FUNCTIONS
*
*/

// discrete space (reference coordinates x, shape functions phi, derivatives of shape functions)
void _q1c0_x(double *xsi, double *eta) {
    xsi[0] =  1.0;  eta[0] =  1.0;
    xsi[1] = -1.0;  eta[1] =  1.0;
    xsi[2] = -1.0;  eta[2] = -1.0;
    xsi[3] =  1.0;  eta[3] = -1.0;
}
void _q1c0_phi(double xsi, double eta, double *phi) {
    phi[0] = (1.0 + xsi) * (1.0 + eta) / 4.0;  
    phi[1] = (1.0 - xsi) * (1.0 + eta) / 4.0;
    phi[2] = (1.0 - xsi) * (1.0 - eta) / 4.0;
    phi[3] = (1.0 + xsi) * (1.0 - eta) / 4.0;
}
void _q1c0_dphidx(double xsi, double eta, double *dphidxsi, double *dphideta) {
    dphidxsi[0] =   (1.0 + eta) / 4.0;  
    dphidxsi[1] = - (1.0 + eta) / 4.0;
    dphidxsi[2] = - (1.0 - eta) / 4.0;
    dphidxsi[3] =   (1.0 - eta) / 4.0;
    dphideta[0] =   (1.0 + xsi) / 4.0;  
    dphideta[1] =   (1.0 - xsi) / 4.0;
    dphideta[2] = - (1.0 - xsi) / 4.0;
    dphideta[3] = - (1.0 + xsi) / 4.0;

}
void _p1c0_x(double *xsi, double *eta) {
    xsi[0] =  0.0;  eta[0] =  0.0;
    xsi[1] =  1.0;  eta[1] =  0.0;
    xsi[2] =  0.0;  eta[2] =  1.0;
}
void _p1c0_phi(double xsi, double eta, double *phi) {
    phi[0] = 1 - xsi - eta;  
    phi[1] = xsi;
    phi[2] = eta;
}
void _p1c0_dphidx(double xsi, double eta, double *dphidxsi, double *dphideta) {
    dphidxsi[0] = -1.0;  
    dphidxsi[1] =  1.0;
    dphidxsi[2] =  0.0;
    dphideta[0] = -1.0;  
    dphideta[1] =  0.0;
    dphideta[2] =  1.0;
}
void _e1c0_x(double *xsi){
    xsi[0] = -1.0;  
    xsi[1] =  1.0;  
}
void _e1c0_phi(double xsi,  double *phi) {
    phi[0] = (1 - xsi) / 2.0;  
    phi[1] = (1 + xsi) / 2.0;
}
void _e1c0_dphidx(double xsi, double *dphidxsi) {
    dphidxsi[0] = -0.5;  
    dphidxsi[1] =  0.5;
}

// prepares structure representing a discrete reference element space
// so later we can perform simple integration with gauss-lagendre quadrature
// creates the space once, then it's reused to solve each element in the mesh
femDiscrete *femDiscreteCreate(int n, femElementType type) {
    
    femDiscrete *theSpace = malloc(sizeof(femDiscrete));
    // EN SOIT ON POURRAIT ENLEVER LES LIGNES QUI SUIVENT ET INITIALISER DIRECTEMENT QUAND ON LES UTILISE
    // MAIS PLUS SAFE COMME CA DU PDV DE MEMOIRE
    theSpace->type = type;
    theSpace->n = 0;
    theSpace->x = NULL;
    theSpace->phi = NULL;   
    theSpace->dphidx = NULL;    
    theSpace->x2 = NULL;    
    theSpace->phi2 = NULL;
    theSpace->dphi2dx = NULL;
 
    if (type == FEM_QUAD && n == 4) {
        theSpace->n       = 4;
        theSpace->x2      = _q1c0_x;
        theSpace->phi2    = _q1c0_phi;
        theSpace->dphi2dx = _q1c0_dphidx;
    }
    else if (type == FEM_TRIANGLE && n == 3) {
        theSpace->n       = 3;
        theSpace->x2      = _p1c0_x;
        theSpace->phi2    = _p1c0_phi;
        theSpace->dphi2dx = _p1c0_dphidx;
    }
    else if (type == FEM_EDGE && n == 2) {
        theSpace->n       = 2;
        theSpace->x       = _e1c0_x;
        theSpace->phi     = _e1c0_phi;
        theSpace->dphidx  = _e1c0_dphidx;
    }
    else Error("Cannot create such a discrete space !");

    return theSpace; 
}

void femDiscreteFree(femDiscrete *theSpace) {
    free(theSpace);
}

void femDiscretePrint(femDiscrete *mySpace) {
    int i,j;
    int n = mySpace->n;
    double xsi[4], eta[4], phi[4], dphidxsi[4], dphideta[4];

    if (mySpace->type == FEM_EDGE) {
        femDiscreteXsi(mySpace,xsi);
        for (i=0; i < n; i++) {           
            femDiscretePhi(mySpace,xsi[i],phi);
            femDiscreteDphi(mySpace,xsi[i],dphidxsi);
            for (j=0; j < n; j++)  {
                printf("(xsi=%+.1f) : ",xsi[i]);
                printf(" phi(%d)=%+.1f",j,phi[j]);  
                printf("   dphidxsi(%d)=%+.1f \n",j,dphidxsi[j]);
            }
            printf(" \n"); 
        }
    }
    if (mySpace->type == FEM_QUAD || mySpace->type == FEM_TRIANGLE) {
        femDiscreteXsi2(mySpace, xsi, eta);
        for (i = 0; i < n; i++)  {
            femDiscretePhi2(mySpace, xsi[i], eta[i], phi);
            femDiscreteDphi2(mySpace, xsi[i], eta[i], dphidxsi, dphideta);
            for (j = 0; j < n; j++) {  
                printf("(xsi=%+.1f,eta=%+.1f) : ", xsi[i], eta[i]);  
                printf(" phi(%d)=%+.1f", j, phi[j]);
                printf("   dphidxsi(%d)=%+.1f", j, dphidxsi[j]);
                printf("   dphideta(%d)=%+.1f \n", j, dphideta[j]);
            }
            printf(" \n");
        }
    }   
}

void femDiscreteXsi2(femDiscrete* mySpace, double *xsi, double *eta) {
    mySpace->x2(xsi,eta);
}
void femDiscretePhi2(femDiscrete* mySpace, double xsi, double eta, double *phi) {
    mySpace->phi2(xsi,eta,phi);
}
void femDiscreteDphi2(femDiscrete* mySpace, double xsi, double eta, double *dphidxsi, double *dphideta) {
    mySpace->dphi2dx(xsi,eta,dphidxsi,dphideta);
}
void femDiscreteXsi(femDiscrete* mySpace, double *xsi) {
    mySpace->x(xsi);
}
void femDiscretePhi(femDiscrete* mySpace, double xsi, double *phi) {
    mySpace->phi(xsi,phi);
}
void femDiscreteDphi(femDiscrete* mySpace, double xsi, double *dphidxsi) {
    mySpace->dphidx(xsi,dphidxsi);
}


/*
*
* FULL SYSTEM FUNCTIONS
*
*/

// allocates full algebraic system and initializes it
femFullSystem *femFullSystemCreate(int size) {
    
    femFullSystem *theSystem = malloc(sizeof(femFullSystem));
    
    femFullSystemAlloc(theSystem, size);
    femFullSystemInit(theSystem);

    return theSystem; 
}

// allocates the necessary memory for the full system
void femFullSystemAlloc(femFullSystem *mySystem, int size)
{
    int i;  
    double *elem = malloc(sizeof(double) * size * (size+1)); 
    mySystem->A = malloc(sizeof(double*) * size); 
    mySystem->B = elem;
    mySystem->A[0] = elem + size;  
    mySystem->size = size;
    for (i=1 ; i < size ; i++) {
        mySystem->A[i] = mySystem->A[i-1] + size;
    }
}

// initializes allocated system to zero
void femFullSystemInit(femFullSystem *mySystem) {
    int i,size = mySystem->size;
    for (i=0 ; i < size*(size+1) ; i++) {
        mySystem->B[i] = 0;
    }
}

// pretty self explainatory eh
void femFullSystemPrint(femFullSystem *mySystem) {
    double  **A, *B;
    int     i, j, size;
    
    A    = mySystem->A;
    B    = mySystem->B;
    size = mySystem->size;
    
    for (i=0; i < size; i++) {
        for (j=0; j < size; j++) {
            if (A[i][j] == 0) {
                printf("         ");
            }
            else{
                printf(" %+.1e",A[i][j]);
            }
        }
        printf(" :  %+.1e \n",B[i]);
    }
}

// this one too foo
void femFullSystemFree(femFullSystem *theSystem) {
    free(theSystem->A);
    free(theSystem->B);
    free(theSystem);
}




/*
*
* UTILS
*
*/

double femMin(double *x, int n) {
    double myMin = x[0];
    int i;
    for (i = 1; i < n; i++)
      myMin = fmin(myMin, x[i]);
    return myMin;
}
  
  double femMax(double *x, int n) {
    double myMax = x[0];
    int i;
    for (i = 1; i < n; i++)
      myMax = fmax(myMax, x[i]);
    return myMax;
  }
  
void femError(char *text, int line, char *file) {
    printf("\n-------------------------------------------------------------------------------- ");
    printf("\n  Error in %s:%d at line %d : \n  %s\n", file, line, line, text);
    printf("--------------------------------------------------------------------- Yek Yek !! \n\n");
    exit(69);
}

void femErrorGmsh(int ierr, int line, char *file) {
    if (ierr == 0)
        return;
    printf("\n-------------------------------------------------------------------------------- ");
    printf("\n  Error in %s:%d at line %d : \n  error code returned by gmsh %d\n", file, line, line, ierr);
    printf("--------------------------------------------------------------------- Yek Yek !! \n\n");
    gmshFinalize(NULL);
    exit(69);
}

void femErrorScan(int test, int line, char *file) {
    if (test >= 0)
        return;
    printf("\n-------------------------------------------------------------------------------- ");
    printf("\n  Error in fscanf or fgets in %s:%d at line %d : \n", file, line, line);
    printf("--------------------------------------------------------------------- Yek Yek !! \n\n");
    exit(69);
}

void femWarning(char *text, int line, char *file) {
    printf("\n-------------------------------------------------------------------------------- ");
    printf("\n  Warning in %s:%d at line %d : \n  %s\n", file, line, line, text);
    printf("--------------------------------------------------------------------- Yek Yek !! \n\n");
}
  

void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}