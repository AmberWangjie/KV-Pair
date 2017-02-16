#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * array = createCounts();//(void);
  if(array == NULL){
    //    free(array);
    return NULL;
  }
  //step1: open file
  FILE * f = NULL;
  f = fopen(filename,"r");
  if(f == NULL){
    return NULL;
  }

  //step2: read one line(key) and find value
  
  //getline ==> char* (key)
  char * line = NULL; 
  size_t sz;
  while(getline(&line,&sz,f) >= 0){
    char* newLine = strchr(line, '\n');
    *newLine = '\0';
    char * key = line;
    char * value = lookupValue(kvPairs, key);
    //printf("\x1B[32mkey=%s\x1B[0m, value=%s\n", key,value);
    addCount(array,value);
    line = NULL;
    free(key);
  }
  
  free(line);
  if(fclose(f) != 0){
    return NULL;
  }
  //step3: return counts_t
  return array;
}


//./count_test kvs1.txt list1a.txt list1b.txt
int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc < 3){
    fprintf(stderr, "wrong file name\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  if(kv == NULL){
    perror("could not open the file\n");
    return EXIT_FAILURE;
  }
  int i;
  for (i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outName, "w");
    printCounts(c, f);
    if(fclose(f) != 0){
      perror("failed to close the file\n");
      return EXIT_FAILURE;
    }
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
 //read the key/value pairs from the file named by argv[1] (call the result kv)

 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c



 //free the memory for kv
  return EXIT_SUCCESS;
}
