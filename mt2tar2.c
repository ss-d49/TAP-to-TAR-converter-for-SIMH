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
char bufz[1024] = {0};
char *tarname = NULL;

if (strcmp("--blocksize", argv[1]) == 0)
{
    blocksize = (size_t)atoi (argv[2]);
}
else if (!argc)
{
    fprintf (stderr, "Usage: %s {--blocksize blocksize} tarfile\n", tapname);
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
		bytes_in = fread (buf, 1, 512, INFILE);
		
        if (bytes_in == 0)
		{
            break;
		}
		
		fwrite (buf, 1, 512, OUTFILE);
		fseek(INFILE, 8, SEEK_CUR);
		bytes_in = fread (buf, 1, blocksize-520, INFILE);
		
		if (bytes_in < blocksize-520)
		{
			fwrite (buf, 1, bytes_in-1560-12, OUTFILE);			
            break;
		}
		
        fwrite (buf, 1, bytes_in-1560, OUTFILE);
		fseek(INFILE, 4, SEEK_CUR);
    }
	fwrite (bufz, 1, 1024, OUTFILE);
	fclose (INFILE);
	fclose (OUTFILE);
    }

free (tarname);
free (buf);
exit(0);
}
