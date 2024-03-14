#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>



void DumpHex(void* pointer, int byteLen){ 
  int i;
  printf("\nThe %d bytes starting at %p are: ",byteLen,pointer); 
  for(i=0;i<byteLen;i++)
  { 
    printf("%02x ",*((unsigned char *)pointer+i));
  }
}

int main(int argc, char **argv){

  char charVal = '0';
  int32_t intVal = 1;
  float floatVal = 1.0;
  double doubleVal = 1.0;

  typedef struct {
  char charVal;
  int32_t intVal;
  float floatVal;                                                 
  double doubleVal;       
  } Ex2Struct; Ex2Struct structVal = { '0', 1, 1.0, 1.0 };  
  
  DumpHex(&charVal, sizeof(char));            
  DumpHex(&intVal, sizeof(int32_t));          
  DumpHex(&floatVal, sizeof(float));       
  DumpHex(&doubleVal, sizeof(double));
  DumpHex(&structVal, sizeof(structVal));
  return 0;
}
