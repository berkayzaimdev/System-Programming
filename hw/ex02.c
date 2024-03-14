#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_file() {
    FILE *file = fopen("example.txt", "w"); // FILE türünde bir struct yapı örnekler. Bu yapı pointer olarak çalışır ve WRITE modunda aktiftir.
    if (file == NULL) //dosya oluşturma işlemi başarısız olursa hata yazdırır.
    {
        perror("Dosya oluşturulurken hata oluştu");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Çocuk işlem PID'si: %d\n", getpid());
  // getpid() fonksiyonu ile çocuk işlemin PID'sini fprintf fonksiyonu ile dosya içerisine yazdırırız.
    fclose(file);
  // dosyayı kapatır
    printf("Dosya oluşturuldu ve içeriği yazıldı.\n");
}

void create_server() {
    printf("Çocuk işlem PID'si: %d\n", getpid());
    // Burada ağ üzerinde bir sunucu oluşturulabilir.
    // Örnek olarak sadece mesaj yazdırılıyor.
    printf("Ağ üzerinde sunucu oluşturuldu.\n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
    // pid, geçersiz ID olan <0 bir değer fırlatırsa, hata mesajı yazdır ve programdan çık
        perror("Fork hatası");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
    // Çocuk işlem ise, 0 döneceği için bu koşulu sağlar
        create_server();
        exit(EXIT_SUCCESS);
    } else {
    // Ebeveyn işlem ise, 0'dan farklı bir değer döneceği için bu koşulu sağlar
        int status;
        waitpid(pid, &status, 0); // Çocuk işlemin tamamlanmasını bekler

        if (WIFEXITED(status)) {
            printf("Çocuk işlem tamamlandı.\n");
        } else {
            printf("Çocuk işlem beklenmeyen bir şekilde sonlandı.\n");
        }

        create_file();
    }

    return 0;
}
