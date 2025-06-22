void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int a=3, b=4;
    printf("After:错误");
    swap(&a, &b);
    system("pause");
    return 0;
}
