#include <unistd.h>
#include <stdio.h>


int main()
{
   int var 10;
   printf("Parent process: vard, PID %d\n", var, getpid());
   fork();
   printf("After first fork: vard, PID %d\n", var, getpid());
   if(fork())
   {
      var+=5;
      printf("Parent process: vard, PID %d\n", var, getpid());
   }
   else
   {
      var-=5;
      printf("Child process: vard, PID = %d\n", var, getpid());
   }
return 0;
}

// if karar yapısı sonucu, eğer parent'ten fork() edilen process eğer sonlandıysa doğru olarak kabul edilir.

// Parent ve Child arasındaki farka, var değerinden ulaşabiliriz. var, ilk değerinden 5 fazlaysa child önce sonlanmıştır
// 5 eksikse child devam etmektedir diyebiliriz.

// Process sırası farklı olduğu için sonuç her çıktıda değişkenlik gösterir. Çıktı sayısı ise her zaman 7'dir. 
// Çünkü ilk process ilk çıktıyı yazdırdıktan sonra fork() edilir ve fork sonrası 3'er çıktıdan toplamda 1+3+3 = 7 çıktı elde ederiz.
