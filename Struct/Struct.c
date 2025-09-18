#include <stdio.h>
int i;
struct Student{
    char NID [10];
    char Name [10];
    int Chinese, English, Math, Art, PE;
    float Avg;
};

int main(){
    struct Student classA [10];
    for(i=0;i<10;i++){
        printf("%s", classA[i]. NID);
        printf("%s", classA[i].Name);
        printf("%d", classA[i].Chinese);
        printf("%d",classA[i].English);
        printf("%d",classA[i].Math);
        printf("%d", classA[i]. Art);
        printf("%d",classA[i].PE);
        printf("%f", classA[i]. Avg);
    }
    return 0;
}
