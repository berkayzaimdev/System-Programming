#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork(); // fork metodu ile main process'ı child process ve main process olmak üzere iki dala ayırırız.

    if (pid < 0)  // pid'nın 0'dan daha küçük olması, process'te bir hata aldığımızı ifade eder. Bu koşulda process'ten çıkmamız gerekir.
    {
         // bir hata yakalandığı takdirde Exec failed yazdırır ve process'ten çıkış yaparız.
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 

    else if (pid == 0) { // pid'nın 0'a eşit olması, bu process'ın çocuk process olduğunu ifade eder. 
        printf("Child process running...\n");
        execl("/bin/ls", "ls", "-1", NULL); 
        // execl metodunu parametrelere göre açıklarsak;
        // ilk parametre olan /bin/ls, yürütülecek program dizininin yolunu belirtir.
        // ikinci parametre olan ls, koşmakta olan process'in adını belirtir.
        // üçüncü parametre olan -1, process'lerin isimlerinin tek bir sütunda listelenmesini sağlar.
        // dördüncü parametre olan NULL, argümanların sonuna ulaştığımızın işaretidir.

        //exec metodunun l'li kullanımı, argümanları dizi değil de liste olarak almamızı sağlar.  

        perror("Exec failed");
        // bir hata oluştuğu takdirde Exec failed yazdırır ve process'ten çıkış yaparız.
        exit(EXIT_FAILURE);
    } 

    else { // pid'nın 0'dan büyük olması, bu process'ın parent process olduğunu ifade eder.
        printf("Parent process waiting for child...\n");
        wait(&status);
        // wait metodu sayesinde bu metoda status'un adresini göndererek child process'ın tamamlanmasını beklememizi sağlarız.
        printf("Child process completed.\n");
    }

    return 0;
}
