#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signum) {
    int status;
    pid_t pid;

    // Çocuk süreçleri zombi süreç haline gelmeden temizle
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Süreç başarılı bir şekilde sonlandıysa
        if (WIFEXITED(status)) {
            printf("ID'si:%d olan child process başarıyla sonlandı.\n", pid);
        }
    }
}

int main() {
    // SIGCHLD sinyalini yakalayacak işleyiciyi ayarla
    struct sigaction sa;
    sa.sa_handler = &sigchld_handler;
    // struct'ın sa_handler parametresine adres olarak yazdığımız fonksiyonu atıyoruz. Bu fonksiyon bize sinyal yakalandığında process'ı sonlandırmamızı sağlayacak.
  
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    // sa_flags, flag mantığıyla çalışan parametredir. 1 ya da 0 olabilir. bu bağlamda atamamızı yaparız.
  
    // SA_RESTART flag'ı ayarlandığında, sinyal yürütmesi tamamlandıktan sonra koda normal işleyişi ile devam edip etmeyeceğimizi belirtir. Eğer 0 olarak ayarlasaydık, sinyal yürütmesi tamamlandıktan sonra hata alırdık.

    // SA_NOCLDSTOP flag'ı ise ayarlandığında, sistem sonlandırılmış bir alt işlem için sinyal iletir ancak durdurulmuş olana iletmez. SIGCHLD sinyali için özel bir flagdır
    if (sigaction(SIGCHLD, &sa, NULL) == -1) 
    {
        perror("Bir hata oluştu!");
        exit(EXIT_FAILURE);
    }

    // Birden çok child process oluştur.
    for (int i = 0; i < 5; i++) {
        pid_t pid = fork(); 
        if (pid == -1) {
            perror("Bir hata oluştu!");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process'te bulunduğumuz için bu koşulu sağlarız
            printf("%d ID'li chil process başlatılıyor\n", getpid());
            // Dosya işlemlerinin bulunduğu kısım
            sleep(1); // Örnek için bekletme
            exit(0);  // Chil process'ı sonlandır
        }
    }

    // Ana süreç diğer işlemlerini yaparken child process'ları beklet
    while(1) {
        sleep(1); // Örnek için sürekli çalıştır
    }

    return 0;
}
