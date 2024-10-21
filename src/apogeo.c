#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <elf.h>


#define ELF_MAGIC_SIZE 4

const uint8_t elfMagicPattern[ELF_MAGIC_SIZE] = {0x7f,'E','L','F'};

void prepareFile(const char *elfName);

void printHeader();

Elf64_Ehdr* elf64;

int main(int argc, char *argv[]){

  

 printf("\n ***[apogeo - ELF Protector Tool]*** \n\n");

   if(argc != 2){
    printf("Only 1 argument is supported\n ");
    exit(EXIT_FAILURE);
   }

    for(int i=0;i<argc;i++){
      printf("argument %d: %s\n",i,argv[i]);
    }

    elf64 = malloc(sizeof(Elf64_Ehdr));
    prepareFile(argv[1]);
    printHeader();
    return 0;
}

void prepareFile(const char *elfName){
  FILE *file = fopen(elfName,"rb");
  if(!file){
    printf("Error: %s\n",strerror(errno));
    exit(EXIT_FAILURE); 
  }

  void *elfMagic = malloc(ELF_MAGIC_SIZE);

  if(elfMagic == NULL){
    printf("Error allocating memory on prepareFile\n");
    exit(EXIT_FAILURE);
  }

  int bytesRead = fread(elfMagic,1,ELF_MAGIC_SIZE,file);

  if(bytesRead != ELF_MAGIC_SIZE){
    printf("Error reading ELF_MAGIC_SIZE\n");
    exit(EXIT_FAILURE);
  }

  printf("%s\n",(char*)elfMagic);

  for(int i=0; i<ELF_MAGIC_SIZE; i++){
    if(*(uint8_t*)(elfMagic+i) != elfMagicPattern[i]){
      printf("File is not an ELF_64 file\n");
      exit(EXIT_FAILURE);
    }
  }
  
  if(fseek(file,0,SEEK_SET)!=0){
    printf("Error setting the pointer to the start of the file\n");
    exit(EXIT_FAILURE);
  }

  ssize_t result = fread(elf64,sizeof(Elf64_Ehdr),1,file);
  printf("%d\n ",result);
  if(result != 1){
    printf("Error reading the header \n");
    exit(EXIT_FAILURE);
  }
 

} 

void printHeader(){
  printf("*Actual start of the section header is: %d\n",elf64->e_shoff);
}







