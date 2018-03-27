#include "C2Decomp.hpp"

void C2Decomp::transposeY2X(double *src, double *dst){

    int s1, s2, s3, d1, d2, d3;

    s1 = decompMain.ysz[0];
    s2 = decompMain.ysz[1];
    s3 = decompMain.ysz[2];

    d1 = decompMain.xsz[0];
    d2 = decompMain.xsz[1];
    d3 = decompMain.xsz[2];

    memSplitYX(src, s1, s2, s3, work1_r, dims[0], decompMain.y1dist);

    MPI_Alltoallv(work1_r, decompMain.y1cnts, decompMain.y1disp, realType, 
		  work2_r, decompMain.x1cnts, decompMain.x1disp, realType, 		   
		  DECOMP_2D_COMM_COL);

    memMergeYX(work2_r, d1, d2, d3, dst, dims[0], decompMain.x1dist);

}

