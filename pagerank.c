//
//  Page Rank algo to rank a sample set of urls
//  
//
//  Modified by Satya Behara on 20/1/18.
//

#include "pagerank.h"
#include <stdio.h>
#include "readData.h"
#include <stdlib.h>
#include <math.h>


typedef struct Url{
    float PR;
    int outDeg;
    int url_id;
} Url;

int fCompare(const void *a, const void *b){
    struct Url *x = (struct Url*)a;
    struct Url *y = (struct Url*)b;
    return x->PR >= y->PR ? -1 : 1;
}



int main(int argc, char *argsv[]) {
    if(argc < 4) {
        printf("Invalid arguments\n");
        return 0;
    }
    else {
        float df = atof(argsv[1]);
        float diffPR = atof(argsv[2]);
        int maxIter = atoi(argsv[3]);
        
    
    
        Graph g_out = getGraph();
        showGraph(g_out);
        
        List url_list = getUrlList();
        int n = getCount(url_list);
        Url url_set[n];
        float pR[n];
        float pR_new[n];
        int outDeg[n];
        float var;
        float diff = 0.0f;
        for(int i = 0; i < n; i++){
            pR[i] = 1.0f/(float)n;
            outDeg[i] = outDegree(g_out, i);
        }
        
        printf("Page Ranks:\n");
        for(int i = 0; i < n; i++){
            printf("%f\n", pR[i]);
            printf("%d\n", outDeg[i]);
        }
        
        printf("Iterating for %d times\n", maxIter);
        for(int iter = 0; iter < maxIter; iter++) {
            
            for(int i = 0; i < n; i++) {
                var = 0.0;
                for(int j = 0; j < n; j++) {
                    if (adjacent(g_out, j, i)){
                        var += pR[j]/(float)outDeg[j];
                    }
                pR_new[i] = (1 - df)/(float)n + df*(var);
                }
            }
            
            diff = 0.0f;
            for(int i = 0; i < n; i++){
                diff += fabs(pR_new[i]-pR[i]);
                pR[i] = pR_new[i];
            }
            if (diff <= diffPR)
                break;
        }
        
        
        printf("Page Ranks:\n");
        for(int i = 0; i < n; i++){
            url_set[i].PR = pR[i];
            url_set[i].outDeg = outDeg[i];
            url_set[i].url_id = getValue(url_list);
            url_list = deleteLL(url_list, getValue(url_list));
        }
        
        
        qsort(url_set, sizeof(url_set)/sizeof(*url_set), sizeof(*url_set), fCompare);
        
        for(int i = 0; i < n; i++){
            printf("url%d, %d, %.7f\n", url_set[i].url_id, url_set[i].outDeg, url_set[i].PR);
        }
        
        return 0;
    }
    
    
    
}
