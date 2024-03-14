#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main() {
   int var = 10;
   printf("Parent process: var = %d, PID = %d\n", var, getpid());
   fork();
   printf("After first fork: var = %d, PID = %d\n", var, getpid());
   fork();
   printf("After second fork: var = %d, PID = %d\n", var, getpid());
   fork();
   printf("After third fork: var = %d, PID = %d\n", var, getpid());
   return 0;
}

// Adım adım gidecek olursak; ilk fork işleminden önce Parent process çıktısı yazılır.
// İlk fork işlemi, proccess'imizde yeni bir dal oluşturur ve process 9.satırdan devam eder.
// Bu dallar, first fork sonucunu iki kere yazdırır. Parent ve Child sırası farklı olabilir.
// İkinci fork işlemi, devam etmekte olan iki process'i ayrı ayrı ikiye ayırır.
// Bu ayrılan yeni dallar, 12. satırdan devam eder. Yani 4 ayrı process, 4 kez second fork sonucunu yazdırır.
// 13. satırda üçüncü fork işlemi uygulanır ve 4'e ayrılmış olan process'lerin her biri tekrar 2'ye ayrılır.
// Sonuç olarak third fork 4*2 = 8 kez yazdırılır.
// Çıktı sıraları, processlerin sonuçlanma durumuna göre farklılık gösterebilir.
