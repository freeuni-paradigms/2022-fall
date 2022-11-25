#include <pthread.h>

//მოცემული გაქვთ ანგარიშები გარკვეული რაოდენობის საწყისი თანხით. უნდა დაწეროთ ორი მეთოდის იმპლემენტაცია AmountIn და AmountOut.

// AmountIn
// fromAccountდან უნდა გადავრიცხოთ amount რაოდენობის თანხა myAccountზე.
// თუ fromAccountზე საკმარისი რაოდენობის თანხა არ იქნა არაფერი არ უნდა ვქნათ.

// AmountOut
// myAccountდან უნდა გადავრიცხოთ amount რაოდენობის თანხა toAccountზე.
//  თუ საკმარისი თანხა არ არის ანგარიშზე მაშინ ოპერაცია უნდა დაპაუზდეს სანამ ვინმე არ ჩარიცხავს თანხას AmountIn-ით myAccountზე

typedef struct {
    int id;
    int amount;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
} Account;

void AmountIn(Account* fromAccount, Account* toAccount, int amount) {
    pthread_mutex_t* firstMutex;
    pthread_mutex_t* secondMutex;
    if (fromAccount->id < toAccount->id) {
        firstMutex = fromAccount->mutex;
        secondMutex = toAccount->mutex;
    }
    else {
        firstMutex = toAccount->mutex;
        secondMutex = fromAccount->mutex;
    }
    pthread_mutex_lock(firstMutex);
    pthread_mutex_lock(secondMutex);

    if (amount <= fromAccount->amount) {
        fromAccount->amount -= amount;
        toAccount->amount += amount;
        pthread_cond_broadcast(toAccount->cond);
    }

    pthread_mutex_unlock(firstMutex);
    pthread_mutex_unlock(secondMutex);
}

void AmountOut(Account* fromAccount, Account* toAccount, int amount) {
    pthread_mutex_lock(fromAccount->mutex);
    while (amount > fromAccount->amount) {
        pthread_cond_wait(fromAccount->cond, fromAccount->mutex);
    }

    fromAccount->amount -= amount;
    pthread_mutex_unlock(fromAccount->mutex);

    pthread_mutex_lock(toAccount->mutex);
    toAccount->amount += amount;
    pthread_cond_broadcast(toAccount->cond);
    pthread_mutex_unlock(toAccount->mutex);
}






