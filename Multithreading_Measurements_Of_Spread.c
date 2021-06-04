#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//Static variables
static int size_of_array;
static int i;

//Determine the size of the input array
static void determineSizeOfInputArray(){
  printf("How many numbers will you enter? Enter your response as a positive integer: ");
  scanf("%d", &size_of_array);

  if(size_of_array > 0){  
    printf("You entered: %d\n", size_of_array);
  } else {
    do{
      printf("Your input of %d is invalid. Please enter a positive integer:", size_of_array);
      scanf("%d", &size_of_array);
    } while(size_of_array <= 0);
  }
}
  
//Collect the inputs for the integer array 
static void collectArrayInputs(int arr[]){
  printf("\nBegin entering your values.\n");
  for(i=0; i<size_of_array; i++){
    printf("Value %d: ",(i+1) );
    scanf("%d", &arr[i]);
  }
}

//Display the content of the array 
static void displayArrayContent(int arr[]){
  printf("\n");
  for(i=0; i<size_of_array; i++){
    printf("%d, ", arr[i]);
  }
}

//Insertion Sort
static void insertionSort(int arr[], int n){
  int i, element, j;
  for(i=1; i<n; i++){
    element = arr[i];
    j=i-1;
    while(j>= 0 && arr[j] > element){
      arr[j+1] = arr[j];
      j=j-1;
    }
    arr[j+1] = element;
  }
}

//Display the minimum value
void *getMin(void *arg){
  int *values = (int*)arg;
  printf("\nMinimum: %d\n", values[0]);
  return NULL;
}

//Display the maximum value
void *getMax(void *arg){
  int *values = (int*)arg;
  printf("Maximum: %d\n", values[(size_of_array-1)]);
  return NULL;
}

//Display the average value
void *getAvg(void *arg){
  int *values = (int*)arg;
  int sum = 0;
  float average = 0.0;
  for(i=0; i<size_of_array; i++){
    sum = sum + values[i];
  }
  average = (sum/size_of_array);
  printf("Average: %.2f\n", average);
  return NULL;
}

//main function
int main(){
  
  determineSizeOfInputArray(); //O(1)
  int inputArray[size_of_array]; //Allocates necessary memory for input array

  collectArrayInputs(inputArray); //O(n)
  
  printf("\nUnsorted Array:");
  displayArrayContent(inputArray); //O(n)
  
  insertionSort(inputArray, size_of_array); //O(n^2)

  printf("\n\nSorted Array:");
  displayArrayContent(inputArray); //O(n)
  printf("\n");

  //Thread identifiers
  pthread_t minPath;
  pthread_t maxPath;
  pthread_t avgPath;

  //Creating a thread for each task
  pthread_create(&minPath,NULL,getMin,inputArray);
  pthread_create(&maxPath,NULL,getMax,inputArray);
  pthread_create(&avgPath,NULL,getAvg,inputArray);

  //Threads join when they complete their designated task
  pthread_join(minPath,NULL);
  pthread_join(maxPath,NULL);
  pthread_join(avgPath,NULL);

  return 0;
}
