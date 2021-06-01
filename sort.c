#include <stdio.h>
#include <string.h>

#define LMAX 100 // Maximum number of rows
#define NMAX 200 // Maximum number of characters per row

void medfilter(double *, int); // Median Filter
void swap (double*, double*);
int compare_raws(const void *, const void *);

struct raws {
  int yy, mm, dd, ddd, hh, mn, ss, cscore;
  double fof2, fof1, foe;
  char foes[3], hmes[3];
  double hmf2, hmf1, hme, b0, b1;
};

void main() {

  struct raws line[LMAX], tmp;

  int i, ii, imax, j, c1, c2;
  char str[NMAX], header[NMAX];
  double f_fof2[LMAX], f_hmf2[LMAX];

  i=0;
  ii=1;
  while ( fgets (str, NMAX, stdin) != NULL) {

    if (str[0] == '#') strcpy(header, str); // Detects the header that starts with '#'
    else {
      c1 = sscanf(str, "%d.%d.%d (%d) %d:%d:%d %d %lf %lf %lf %s %s %lf %lf %lf %lf %lf",
        &tmp.yy, &tmp.mm, &tmp.dd, &tmp.ddd, &tmp.hh, &tmp.mn, &tmp.ss, &tmp.cscore,
        &tmp.fof2, &tmp.fof1, &tmp.foe, tmp.foes, tmp.hmes, &tmp.hmf2, &tmp.hmf1, &tmp.hme, &tmp.b0, &tmp.b1);

      c2 = 1;
      for (j=0; j<i; j++) {
        if (compare_raws(&line[j], &tmp) == 0) {
          c2 = 0;
          break;
        }
      }

      if (c1 < 18) printf("[Missing column] line %d: %s", ii, str);
      else if (c2 == 0) printf("[Duplicate line] line %d: %s", ii, str);
      else {
        line[i] = tmp;
        i++;
      }
    }
    ii++;
  }
  imax = i;

  qsort(line, imax, sizeof(struct raws), compare_raws); // sorts the rows, old to new

  printf("\n%s", header);
  for(i=0; i<imax; i++) {
    tmp = line[i];

    printf("%d.%02d.%02d (%03d) %02d:%02d:%02d %03d %.3f %.3f %.3f %s %s %.3f %.3f %.3f %.3f %.3f\n",
      tmp.yy, tmp.mm, tmp.dd, tmp.ddd, tmp.hh, tmp.mn, tmp.ss, tmp.cscore,
      tmp.fof2, tmp.fof1, tmp.foe, tmp.foes, tmp.hmes, tmp.hmf2, tmp.hmf1, tmp.hme, tmp.b0, tmp.b1);
  }
  printf("\n");

// Median Filter

  for (i=0; i<imax; i++) {
    f_fof2[i] = line[i].fof2;
    f_hmf2[i] = line[i].hmf2;
  }

  medfilter(f_fof2, imax);
  medfilter(f_hmf2, imax);

  printf("Median Filter, foF2 & hmf2: \n");

  for (i=0; i<imax; i++) {
    tmp = line[i];

    printf("%d.%02d.%02d (%03d) %02d:%02d:%02d %.3f %.3f\n",
      tmp.yy, tmp.mm, tmp.dd, tmp.ddd, tmp.hh, tmp.mn, tmp.ss, f_fof2[i], f_hmf2[i]); // prints the date, time, foF2, hmF2
  }
}

int compare_raws(const void *s0, const void *t0) {
  int i;
  struct raws *s, *t;

  s = (struct raws*) s0;
  t = (struct raws*) t0;

  if ((i = (s->yy)-(t->yy)) != 0) { return i; }
  else {
    i = 86400*((s->ddd)-(t->ddd)) + 3600*((s->hh)-(t->hh)) + 60*((s->mn)-(t->mn)) + (s->ss)-(t->ss);
        // if year is the same, compare the number of seconds since Jan 1 00:00
    return i;
  }
}

void medfilter(double v[], int n) { // Median Filter with window size 3
  int i;
  double temp[n], a, b, c;

  temp[0] = (v[0]+v[1])/2;
  temp[n-1] = (v[n-2]+v[n-1])/2;

  for (i=1; i<n-1; i++) {
    a = v[i-1]; b = v[i]; c = v[i+1];
    if (a<b) { swap(&a,&b); }
    if (a<c) { swap(&a,&c); }
    if (b<c) { swap(&b,&c); }
    temp[i] = b;
  }

  for (i=0; i<n; i++) { v[i] = temp[i]; }
}

void swap(double* a, double* b) {
  double t;
  t=*a;
  *a=*b;
  *b=t;
}
