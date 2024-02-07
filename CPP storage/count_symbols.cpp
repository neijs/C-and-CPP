int count_symbols(int arg) {
    int count = (arg == 0) ? 1 : 0;
    for (; arg; count++, arg /= 10);
    return count;
}
int count_symbols(int *arr, int n = 1) {
    int count = 0;
    for (int i = 0; i < n; i++)
        count += count_symbols(arr[i]);
    return count;
}
int count_symbols(char *str) {
    int count = 0;
    for (; str[count] != '\0'; count++);
    return count;
}
int count_symbols(double f, int n = 0) {
    long arg = long(f);
    int count = (arg == 0) ? 1 : 0;
    for (; arg; count++, arg /= 10);
    return count + n;
}