#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status;

  pid = fork(); // Çocuk süreci oluştur

  if (pid < 0) {
    // Fork hatası
    fprintf(stderr, "Fork başarısız oldu\n");
    return 1;
  } else if (pid == 0) {
    // Çocuk süreci
    printf("Çocuk süreç çalışıyor...\n");
    sleep(5); // 5 saniye uyku
    printf("Çocuk süreç sonlandı.\n");
    exit(0);
  } else {
    // Ebeveyn süreci
    printf("Ebeveyn süreç bekliyor...\n");
    wait(&status); // Çocuk sürecin durumunu bekler
    printf("Ebeveyn süreç, çocuk sürecin durumunu aldı.\n");
  }
  return 0;
}

/*

1. Programda ilk fork çağrısında, main process bölünerek bir child process oluşturur. Child ve main process, running durumdadır.

2. Child process else if bloğuna, main(parent) process ise else bloğuna girer.

3. Child process ve parent process, wait komutundan ötürü sıralı bir şekilde ilk önce Parent, sonra Child processlar print çıktılarını yazdırır.

4. Child process içinde sleep(5) komutu 5 saniye uyku durumu oluşturur ve waiting durumuna geçer.

5. 5 saniye sonra Child process'te ikinci print çıktısı yazdırılır. akabinde exit(0) komutu çağrılır ve Child process, terminate olur.

6. exit komutu çağrılıp Child process bittiği için else bloğundaki wait kodu aktif olur ve parent Process ikinci çıktısını yazdırır. Bloktan çıkış ile de parent process terminate olur.

*/
