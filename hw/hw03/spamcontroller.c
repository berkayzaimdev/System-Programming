#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMENT_LENGTH 100
#define SPAM_KRITERI_SAYISI 3

char *spam_kriteri[] = {"kazandınız", "ücretsiz kazan", "çekiliş"};

int eslesme_sayisi(char *comment, char *word) {
  int c = 0;
  char *found = strstr(comment, word);
  // strstr(x,y) metodu ile y'nin x'in içinde bulunup bulunmadığını kontrol
  // ederiz. www veya http alan isimleri, 5'ten fazla kez geçiyorsa bu mesajı
  // spam olarak işaretleriz.
  while (found != NULL) {
    c++;
    found = strstr(found + 1, word);
    // eşleşme yakalandığı müddetçe döngü devam eder
  }
  return c;
}

void spam_kontrolu(char *comment) {
  int link_sayisi = 0;
  for (int i = 0; i < SPAM_KRITERI_SAYISI; i++) {
    if (strstr(comment, spam_kriteri[i]) != NULL) {
      // eşleşme durumunda yorumun spam olarak işaretlenmesi için if yazdık. tek bir eşleşme yeterli oluyor
      execl("./filewriter", "spam.txt", "a", comment, NULL);
      // eşleşme yakalanınca filewriter dosyasını koşturmak adına gerekli parametreleri gönderdik.
      break;
    }
  }

  link_sayisi += eslesme_sayisi(comment, "http");
  link_sayisi += eslesme_sayisi(comment, "www");

  if (link_sayisi > 3) {
    // yorumda geçen link sayısı 3'ten büyükse spam olarak işaretle ve dosyaya yazdır
    execl("./filewriter", "spam.txt", "a", comment, NULL);
  }

}

int main() {
  pid_t pid;
  char comment[MAX_COMMENT_LENGTH];

  while (1) {
    printf("Bir yorum ekleyiniz. (programı sonlandırmak icin 'exit' "
           "yazabilirsiniz): ");
    fgets(comment, MAX_COMMENT_LENGTH, stdin);

    if (strcmp(comment, "exit\n") == 0) {
      break;
    }

    pid = fork();
    // fork() kullanarak bir child process oluşturduk

    if (pid < 0) { // fork() sonucu PID<0 ise bir hata oluşmuştur deriz ve hata mesajını yazdırıp programdan çıkış yaparız
      perror("Fork failed");
      exit(EXIT_FAILURE);
    }

    else if (pid == 0) { // fork() sonucu PID=0 ise child process koşuyor
                         // demektir. Spam kontrol işlemini child processta
                         // yapacağımız için bizi ilgilendiren ana kısım burası
      spam_kontrolu(comment);
      exit(EXIT_SUCCESS);
      // exit metodu ile spam kontrolü başarı ile bittikten sonra child process'ı sonlandırırız
    }

    else {        // fork() sonucu PID=0 ise parent process koşuyor demektir.
      wait(NULL); // wait metodunu kullanarak child process'in bitmesini bekliyoruz
    }
  }

  return 0;
}

// Sorular:

// Bu senaryoda, fork, exec, ve wait sistem çağrılarını nasıl kullanırsınız?
/*
-> döngünün her adımında fork kullanımı ile bir child process oluşturulur. Bu child process, yorumu kontrol etmek için spam_kontrolu metodunu çağıracaktır. Koşmakta olan process'ın child process olup olmadığını pid ile kontrol ederiz.

-> exec metodunu, execl olarak kullanmayı tercih ettim. Parametre olarak dosya adını, dosyaya uygulanacak işlemi belirten stringi ve spam olarak işaretlenecek yorumu liste formatında gönderdim ve filewriter dosyasının koşturulmasını sağladım. filewriter dosyası, spam olarak işaretlenen yorumun spam.txt'e yazdırılmasını sağlıyor.
*/

// Hangi kriterleri kullanarak bir yorumun spam olarak işaretleneceğini belirlerdiniz?
/*
-> genelgeçer spam kriterlerini kullanabiliriz. Bu kriterlerden bazıları;
mesajda bulunan link sayısı 3'ten fazlaysa,

mesajda 'kazandınız', 'çekiliş', 'ücretsiz kazan' gibi ifadeler geçiyorsa, bu mesajı bir spam olarak işaretleyebiliriz.
*/

// spam.txt dosyasına kaydedilecek spam yorumlarını nasıl temsil edersiniz ve bu dosyaya yazmayı nasıl gerçekleştirirsiniz?
/*
-> spam yorumları, dosyaya her satırda bir spam mesajı bulunacak şekilde yazdırılır.

-> bu yorumları fprintf ile dosyaya satır satır yazdırırız. String olarak
ekleyeceğimiz için otomatik olarak satırlar arası boşluk olacaktır bu yüzden \n eklemedik
*/
