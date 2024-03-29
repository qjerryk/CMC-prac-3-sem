/*На стандартном потоке ввода задается целое число N (N > 0). Требуется создать N процессов по следующей схеме: процесс-родитель создает первый процесс (процесс-сын), процесс-сын создает второй процесс свой сыновий процесс (процесс-внук), процесс-внук создает третий процесс - своего сына (процесс-правнук) и так далее.

Процесс-родитель создает переменную pid, в которую записывает свой PID. Переменная pid создается в начале программы, до первого fork(). Дальше каждый процесс потомок выводит в стандартный поток вывода 2 числа. Первое число getpid()-getppid(), второе число getpid()-pid. После этого выводится символ перевода строки.

Для вывода можно использовать средства высокого уровня. Вывод всегда происходит до порождения очередного процесса. Не забываем про сброс буфера. (функция fflush(stdout))

Кроме того каждый из процессов-потомков выводит в стандартный поток ошибок свой PID и PPID в следующем формате: "PID = %d PPID = %d\n" и тоже не забываем про сброс буфера.

Процесс-родитель каждого из процессов должен завершаться после завершения работы своего потомка.

*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int N;
    int i, PID, pid = 0, is_PID_right = 0;
    scanf("%d", &N);
    PID = getpid();
    for (i = 0, pid = 0; i < N+1; i++){
        if (i){
            printf("%d %d\n", getpid()-getppid(), getpid()-PID);
            fflush(stdout);
            fprintf(stderr, "PID = %d PPID = %d\n", getpid(), getppid());
            fflush(stderr);
        }
        pid = fork();
        if (pid < 0){
            fprintf(stderr, "Error");
            return 1;
        }
        if (pid > 0){
            wait(NULL);
            break;
        }
    }
    return 0;
}
