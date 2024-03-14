#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // bu program, parametre olarak spamcontroller dosyası koşarken gönderilen sırasıyla; dosya adını, dosyaya yazılacak işlemi belirten stringi ve spam olarak işaretlenecek yorumu tutuyor.
  
  FILE *spam_file = fopen(argv[0], argv[1]);
  
  if (spam_file == NULL) {
    perror("Error opening spam.txt");
    return EXIT_FAILURE;
  }
  
  fprintf(spam_file, "%s", argv[2]);
  fclose(spam_file);
  return EXIT_SUCCESS;
}
