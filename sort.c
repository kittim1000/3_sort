#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 100

void medfilter(float *, int);

main() {
  int i, imax, ddd[NMAX], cscore[NMAX];
  int yy[NMAX], mm[NMAX], dd[NMAX], hh[NMAX], mn[NMAX], sc[NMAX];
  float fof2[NMAX], fof1[NMAX], foe[NMAX], foes[NMAX], hes[NMAX], hmf2[NMAX], hmf1[NMAX], hme[NMAX], b0[NMAX], b1[NMAX], d1[NMAX];
  float mf_fof2[NMAX], mf_hmf2[NMAX];
  char str[NMAX][200];

  FILE *fp;
  fp = fopen("data.tab", "r");

  i=0;
  while ( fgets (str[i], 200, fp) != NULL) {
    sscanf(str[i], "%d.%d.%d (%d) %d:%d:%d %d %f %f %f --- --- %f %f %f %f %f\n",
      &yy[i], &mm[i], &dd[i], &ddd[i], &hh[i], &mn[i], &sc[i], &cscore[i],
      &fof2[i], &fof1[i], &foe[i], &hmf2[i], &hmf1[i], &hme[i], &b0[i], &b1[i], &d1[i]);
    i++;
  }
  imax = i;

  qsort(str, imax, sizeof(str[0]), strcmp);

  for( i = 0 ; i < imax; i++ ) {
    printf(str[i]);
  }
  printf("\n");

// Median Filter

  medfilter(fof2, imax);
  printf("Median Filter, foF2: ");
  for (i=0; i<imax; i++) { printf ("%5.3f\n", fof2[i]); } printf ("\n");

  medfilter(hmf2, imax);
  printf("Median Filter, hmf2: ");
  for (i=0; i<imax; i++) { printf ("%5.3f\n", hmf2[i]); } printf ("\n");

  fclose (fp);
}

void medfilter(float v[], int n) {
  int i;
  float tmp[n], a, b, c;

  tmp[0] = (v[0]+v[1])/2;
  tmp[n-1] = (v[n-2]+v[n-1])/2;

  for (i=1; i<n-1; i++) {
    a = v[i-1]; b = v[i]; c = v[i+1];
    if ((b<=a) && (a<=c)) { tmp[i] = a; }
    if ((c<=a) && (a<=b)) { tmp[i] = a; }
    if ((a<=b) && (b<=c)) { tmp[i] = b; }
    if ((c<=b) && (b<=a)) { tmp[i] = b; }
    if ((a<=c) && (c<=b)) { tmp[i] = c; }
    if ((b<=c) && (c<=a)) { tmp[i] = c; }
  }
  for (i=0; i<n; i++) { v[i] = tmp[i]; }
}
