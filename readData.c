//
//  code to read the collections.txt and form an adjacency matrix of the url's

//  Modified by Satya Behara on 20/1/18.
//

#include "readData.h"
#include  <string.h>
#include <stdlib.h>
#include <assert.h>


List getUrlList(){
    //create a linked list with all the url_Id's in the collection.txt
    
    List url_list = NULL;
    
    FILE *fp = fopen("collection.txt", "r");
    char line[1000];
    int url_id;
    
    
    while (fscanf(fp, "%s", &line[0])!=EOF) {
        //printf("%s \n",line);
        char *token = strtok(line, "url");
        
        if(token != NULL){
            url_id = atoi(token);
            url_list = insertLL(url_list, url_id);
        }
    }
    
    fclose(fp);
    showLL(url_list);
    
    return url_list;
}


const char* generateUrl(int url){
    //build the url filename from the url ID
    
    char url_filename[1000] = "url";
    char tmp[1000];
    static char final_urlname[1000];
    sprintf(tmp, "%d", url);
    strcat(url_filename, tmp);
    strcat(url_filename, ".txt");
    snprintf(final_urlname, sizeof(final_urlname), "%s", url_filename);
    return final_urlname;
}

int getCount(List url_list) {
    //get the number of elements in a linked list
    
    List tmp = url_list;
    int n = 0;
    
    while(tmp != NULL) {
        n++;
        tmp = deleteLL(tmp, getValue(tmp));
    }
    
    return n;
}


List getOutboundUrlList(int url_in){
    //create a list of all the outgoing url's in a given url
    
    List url_list = NULL;
    printf("url%d.txt: \n", url_in);
    
    FILE *fp = fopen(generateUrl(url_in), "r");
    printf("Inside %s\n", generateUrl(url_in));
    char line[1000];
    int url_id;
    int flag = 0;
    int start = 0;
    
    
    while (fscanf(fp, "%s", &line[0])!=EOF) {
        //printf("%s \n",line);
        if(strcmp(line, "#start") == 0 && start == 0)
            start = 1;
        else if(strcmp(line, "Section-1") == 0 && start == 1)
            start =2;
        else if (start == 2) {
            if(strcmp(line, "#end") == 0 && flag == 0)
                flag = 1;
            else if(strcmp(line, "Section-1") == 0 && flag == 1)
                break;
            else {
                flag = 0;
        
                char *token = strtok(line, "url");
                if(token != NULL){
                    url_id = atoi(token);
                    printf("Inserting %s(%d)\n", token, url_id);
                    url_list = insertLL(url_list, url_id);
                }
                
            }
        }
        else
            start = 0;
    }
    
    fclose(fp);
    printf("Nodes: ");
    showLL(url_list);
    
    return url_list;
}




Graph getGraph() {
    //create a graph which holds the adjacency matrix of the url links to each other
    
    Vertex inVertex, outVertex;
    List url_list = getUrlList();
    List url_list_orig = url_list;
    List out_url_list;
    
    assert(url_list != NULL);
    int nV = getCount(url_list);
    
    printf("Creating graph\n");
    Graph g_new = newGraph(nV);
    Edge e;
    
    while(url_list != NULL) {
        inVertex = getValue(url_list);
        
        out_url_list = getOutboundUrlList(inVertex);
        while(out_url_list != NULL) {
            outVertex = getValue(out_url_list);
            e.v = indexOf(url_list_orig, inVertex);
            e.w = indexOf(url_list_orig, outVertex);
            insertEdge(g_new, e);
            out_url_list = deleteLL(out_url_list, outVertex);
        }
        url_list = deleteLL(url_list, inVertex);
        
    }
    return g_new;
    
}



























