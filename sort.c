#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LMAX 100
#define NMAX 200

void medfilter(double *, int);
void swap (double*, double*);

main() {

  struct raws {
    char date[NMAX]; char ddd[NMAX]; char time[NMAX]; char cscore[NMAX];
    char fof2[NMAX][NMAX]; char fof1[NMAX]; char foe[NMAX]; char foes[NMAX];
    char hes[NMAX]; char hmf2[NMAX]; char hmf1[NMAX]; char hme[NMAX];
    char b0[NMAX]; char b1[NMAX]; char d1[NMAX];
  } line[LMAX], tmp;

  int i, imax;
  char str[NMAX], header[NMAX];
  double f_fof2[LMAX], f_hmf2[LMAX];

/*  char date[LMAX][NMAX], ddd[LMAX][NMAX], time[LMAX][NMAX], cscore[LMAX][NMAX];
  char fof1[LMAX][NMAX], foe[LMAX][NMAX], foes[LMAX][NMAX], hes[LMAX][NMAX], hmf1[LMAX][NMAX], hme[LMAX][NMAX], b0[LMAX][NMAX], b1[LMAX][NMAX], d1[LMAX][NMAX];
  float fof2[LMAX], hmf2[LMAX];
  char str[LMAX][NMAX], header[NMAX];
*/

  FILE *fp;
  fp = fopen("data.tab", "r");

  i=0;
  while ( fgets (str, NMAX, fp) != NULL) {
    if (str[0] == '#') { strcpy(header, str); }
    else {
      sscanf(str, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s",
        tmp.date, tmp.ddd, tmp.time, tmp.cscore,
        tmp.fof2, tmp.fof1, tmp.foe, tmp.foes, tmp.hes, tmp.hmf2, tmp.hmf1, tmp.hme, tmp.b0, tmp.b1, tmp.d1);
//        date[i], ddd[i], time[i], cscore[i],
//        &fof2[i], fof1[i], foe[i], foes[i], hes[i], &hmf2[i], hmf1[i], hme[i], b0[i], b1[i], d1[i]);

      line[i] = tmp;
      i++;
    }
  }
  imax = i;

  qsort(line, imax, sizeof(line[0]), strcmp);

  printf(header);
  printf("\n");

  for(i=0; i<imax; i++) {
    tmp = line[i];
    printf("%s %s %s %s %s %s %s %s %s %s %s %s %s %s\n",
      tmp.date, tmp.ddd, tmp.time, tmp.cscore,
      tmp.fof2, tmp.fof1, tmp.foe, tmp.foes, tmp.hes, tmp.hmf2,
      tmp.hmf1, tmp.hme, tmp.b0, tmp.b1, tmp.d1);
  }
  printf("\n");

// Median Filter

  for (i=0; i<imax; i++) {
    f_fof2[i] = atof(line[i].fof2);
    f_hmf2[i] = atof(line[i].hmf2);
  }

  medfilter(f_fof2, imax);
  printf("Median Filter, foF2: \n");
  for (i=0; i<imax; i++) { printf ("%5.3f\n", f_fof2[i]); } printf ("\n");

  medfilter(f_hmf2, imax);
  printf("Median Filter, hmf2: \n");
  for (i=0; i<imax; i++) { printf ("%5.3f\n", f_hmf2[i]); } printf ("\n");

  fclose (fp);
}

void medfilter(double v[], int n) {
  int i;
  double tmp[n], a, b, c;

  tmp[0] = (v[0]+v[1])/2;
  tmp[n-1] = (v[n-2]+v[n-1])/2;

  for (i=1; i<n-1; i++) {
    a = v[i-1]; b = v[i]; c = v[i+1];
    if (a<b) { swap(&a,&b); }
    if (a<c) { swap(&a,&c); }
    if (b<c) { swap(&b,&c); }
    tmp[i] = b;
  }

  for (i=0; i<n; i++) { v[i] = tmp[i]; }
}

void swap(double* a, double* b) {
  double t;
  t=*a;
  *a=*b;
  *b=t;
}
