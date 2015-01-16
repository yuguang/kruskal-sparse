/****************************************************************************/
/*                                                                          */
/*              CO759: Model for HW1, Kruskal MST Algorithm                 */
/*              Date:  January 14, 2015                                     */
/*                                                                          */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

static void usage (char *f);
static int getprob (char *fname, int *p_ncount, int *p_ecount, int **p_elist,
    int **p_elen);
// elist - array 2*ecount
// elist[2*i] is end0 of ith edge
// elist[2*i+1] is end1 of ith edge
// elen - array ecount
// elen[i] is length of ith edge
static int kruskal_spanningtree (int ncount, int ecount, int *elist,
    int *elen, int *tlist);

int main (int ac, char **av)
{
    int rval  = 0, i, ncount, ecount;
    int *elist = (int *) NULL, *elen = (int *) NULL, *tlist = (int *) NULL;
    double szeit, wt;

    if (ac < 2) {
        usage (*av);
        rval = 1;  goto CLEANUP;
    }

    rval = getprob (av[1], &ncount, &ecount, &elist, &elen);
    if (rval) {
        fprintf (stderr, "getprob failed\n");
        goto CLEANUP;
    }

    tlist = (int *) malloc ((ncount-1)*sizeof (int));
    if (!tlist) {
        fprintf (stderr, "out of memory for tlist\n");
        rval = 1;  goto CLEANUP; 
    }

    szeit = CO759_zeit ();
    rval = kruskal_spanningtree (ncount, ecount, elist, elen, tlist);
    // changes tlist array
    if (rval) {
        fprintf (stderr, "kruskal_spanningtree failed\n");
        goto CLEANUP;
    }
    printf ("Running Time: %.2f seconds\n", CO759_zeit() - szeit);
    fflush (stdout);

    wt = 0.0;
    for (i = 0; i < ncount - 1; i++) wt += elen[tlist[i]];

    printf ("Tree Length: %.0f\n", wt); fflush (stdout);

CLEANUP:

    if (tlist) free (tlist);
    if (elist) free (elist);
    if (elen) free (elen);
    return rval;
}

static int kruskal_spanningtree (int ncount, int ecount, int *elist,
        int *elen, int *tlist)
{
    int i;

    /* Place the indices of the spanning tree edges into the array    */
    /* tlist.  The array should receive ncount-1 numbers, each number */
    /* being between 0 and ecount-1.                                  */

    /* The function should return the value 0 and a non-zero value if */
    /* it fails.                                                      */

    /* I'll put dummy values into the array.                          */

    for (i = 0; i < ncount-1; i++) tlist[i] = i;

    return 0;
}

static void usage (char *f)
{
    fprintf (stderr, "Usage: %s edge_file\n", f);
}

static int getprob (char *fname, int *p_ncount, int *p_ecount, int **p_elist,
    int **p_elen)
{
    FILE *f = (FILE *) NULL;
    int i, end1, end2, w, rval = 0, ncount, ecount;
    int *elist = (int *) NULL, *elen = (int *) NULL;

    if ((f = fopen (fname, "r")) == NULL) {
	fprintf (stderr, "Unable to open %s for input\n",fname);
        rval = 1;  goto CLEANUP;
    }

    if (fscanf (f, "%d %d", &ncount, &ecount) != 2) {
	fprintf (stderr, "Input file %s has invalid format\n",fname);
        rval = 1;  goto CLEANUP;
    }

    printf ("Nodes: %d  Edges: %d\n", ncount, ecount);
    fflush (stdout);

    elist = (int *) malloc (2 * ecount * sizeof (int));
    if (!elist) {
        fprintf (stderr, "out of memory for elist\n");
        rval = 1;  goto CLEANUP;
    }

    elen = (int *) malloc (ecount * sizeof (int));
    if (!elen) {
        fprintf (stderr, "out of memory for elen\n");
        rval = 1;  goto CLEANUP;
    }

    for (i = 0; i < ecount; i++) {
	if (fscanf(f,"%d %d %d",&end1, &end2, &w) != 3) {
	    fprintf (stderr, "%s has invalid input format\n",fname);
            rval = 1;  goto CLEANUP;
	}
	elist[2*i] = end1;
	elist[2*i+1] = end2;
	elen[i] = w;
    }

    *p_ncount = ncount;
    *p_ecount = ecount;
    *p_elist = elist;
    *p_elen = elen;

CLEANUP:
    if (f) fclose (f);
    return rval;
}

