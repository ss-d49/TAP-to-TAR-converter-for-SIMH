#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

main (int argc, char **argv)
{
FILE *INFILE = NULL, *OUTFILE = NULL;
size_t blocksize = 8192, bytes_in;
char *tapname = argv[0];
char *buf = NULL;
char *tarname = NULL;

if ((argc >= 3) && ((strcmp("--blocksize", argv[1]) == 0)))
{
    blocksize = (size_t)atoi (argv[2]);
}
else if (argc < 1)
{
    fprintf (stderr, "Usage: %s {--blocksize blocksize} tarfile {tarfile2 ...}\n", tapname);
    fprintf (stderr, "This utility converts a unix simh .tap file to a tar file\n");
    exit (0);
}

while (--argc > 0) {
    ++argv;
    tarname = realloc (tarname, 5 + strlen (argv[0]));
    if (NULL == (INFILE = fopen (argv[0], "rb"))) {
        fprintf (stderr, "Error Opening tar file '%s': %s\n", argv[0], strerror (errno));
        break;
    }
    strcpy (tarname, argv[0]);
    strcat (tarname, ".tar");
    if (NULL == (OUTFILE = fopen (tarname, "wb"))) {
        fprintf (stderr, "Error Opening tap file '%s': %s\n", tarname, strerror (errno));
        break;
    }
    buf = realloc (buf, blocksize);
    while (1) {
		fseek(INFILE, 4, SEEK_CUR);
		bytes_in = fread (buf, 1, blocksize, INFILE);
		
        if (bytes_in == 0)
		{
            break;
		}
		
		if (bytes_in < blocksize-520)
		{
			fwrite (buf, 1, bytes_in-12, OUTFILE);			
            break;
		}
		
        fwrite (buf, 1, bytes_in, OUTFILE);
		fseek(INFILE, 4, SEEK_CUR);
    }
	fclose (INFILE);
	fclose (OUTFILE);
    }

free (tarname);
free (buf);
exit(0);
}
