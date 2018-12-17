#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, i, j, k, *h, *d, n, *s, *f;
    scanf("%d", &n);
    d = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf("%d", &d[i]);
    scanf("%d", &m);
    h = malloc(sizeof(int) * m);
    s = malloc(sizeof(int) * m);
    f = malloc(sizeof(int) * m);
    for (i = 0; i < m; i++) s[i] = 0;
    for (i = 0; i < m; i++) h[i] = -1;
    for (i = 0; i < n; i++)
    {
        if (h[d[i] % m] == -1)
        {
            h[d[i] % m] = d[i];
        }
        else
        {
            k = 1;
            while (h[(d[i] + k) % m] != -1) k += 1;
            h[(d[i] + k) % m] = d[i];
        }
    }
    for (i = 0; i < n; i++)
    {
        if (h[d[i] % m] == d[i])
        {
            s[d[i] % m] = 1;
        }
        else
        {
            k = 1;
            while (h[(d[i] + k) % m] != d[i]) k += 1;
            s[(d[i] + k) % m] = k + 1;
        }
    }
    for (i = 0; i < m; i++)
    {
        k = i; j = 1;
        while (h[k] != -1)
        {
            k += 1;
            j += 1;
            k = k % m;
        }
        f[i] = j;
    }
    printf("Address:\t"); 
    for (i = 0; i < m; i ++) printf("%d\t", i); printf("\n");
    printf("Key:\t\t");
    for (i = 0; i < m; i++) printf("%d\t", h[i]);printf("\n");
    printf("Fail:\t\t");
    for (i = 0; i < m; i++) printf("%d\t", f[i]);printf("\n");
    printf("Success:\t");
    for (i = 0; i < m; i++) printf("%d\t", s[i]); printf("\n");

    // for (i = 0; i < n; i ++) printf("%d\t", d[i] % m); 

    double succ_sum, fail_sum;
    succ_sum = 0;
    fail_sum = 0;
    for(i = 0; i < m; ++ i) {
        succ_sum += s[i];
        fail_sum += f[i];
    }

    printf("\nAverage Success: %.2lf, Average False: %.2lf", succ_sum / n, fail_sum / m);
    return 0;
}
