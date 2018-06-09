#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char *substring(char *, int, int);
char *str_replace(char *, char *, char *);

// ----------------------------------------------------------------------------
int main (void)
{
	DIR *dp;
	struct dirent *ep;
	char *filename; // the return string
	char *ext; // the return string
	char result[256]; // the return string
	strcpy(result, "");

	dp = opendir ("/Users/yannick/Dropbox/YF/Banque/200X/");
	if (dp != NULL)
	{
		while ((ep = readdir (dp)))
		{
			ext = substring(ep->d_name, strlen(ep->d_name)-3, 4);
			filename = str_replace(ep->d_name,"%20"," ");
			filename = str_replace(filename,"Relev_","Relevé");
			filename = str_replace(filename," _pargne"," épargne");
			filename = str_replace(filename,"n_","n°");
			if(strncmp ( filename, "Relevé", 6 ) == 0)
			{
				char *sub1;
				char *sub2;
				sub1 = substring(filename, 25, 4);
				sub2 = substring(filename, 22, 2);
				strcpy(result, sub1);
				strcat(result, "-");
				strcat(result, sub2);
				strcat(result, " CASA ");
				strcat(result, filename);
				strcat(result, ext);
				printf("mv \"%s\" \"%s\"\n", ep->d_name, result );
			}
			else if(strncmp ( filename, "E-Relevé", 6 ) == 0)
			{
				char *sub1;
				char *sub2;
				if(strncmp ( filename, "E-Relevés PEL", 13 ) == 0)
				{
					sub1 = substring(filename, 30, 4);
					sub2 = substring(filename, 27, 2);
				}
				else
				{
					sub1 = substring(filename, 34, 4);
					sub2 = substring(filename, 31, 2);
				}
				strcpy(result, sub1);
				strcat(result, "-");
				strcat(result, sub2);
				strcat(result, " CASA ");
				strcat(result, filename);
				strcat(result, ext);
				printf("mv \"%s\" \"%s\"\n", ep->d_name, result );
			}
			else if(strncmp ( filename, "E-Avis", 6 ) == 0)
			{
				char *sub1;
				char *sub2;
				sub1 = substring(filename, 28, 4);
				sub2 = substring(filename, 25, 2);
				strcpy(result, sub1);
				strcat(result, "-");
				strcat(result, sub2);
				strcat(result, " CASA ");
				strcat(result, filename);
				strcat(result, ext);
				printf("mv \"%s\" \"%s\"\n", ep->d_name, result );
			}
			else if(strncmp ( filename, "E-IFU", 5 ) == 0)
			{
				char *sub1;
				char *sub2;
				sub1 = substring(filename, 20, 4);
				sub2 = substring(filename, 17, 2);
				strcpy(result, sub1);
				strcat(result, "-");
				strcat(result, sub2);
				strcat(result, " CASA ");
				strcat(result, filename);
				strcat(result, ext);
				printf("mv \"%s\" \"%s\"\n", ep->d_name, result );
			}
			else if(strncmp ( filename, "Statement", 9 ) == 0)
			{
				char *sub1;
				char *sub2;
				sub1 = substring(filename, 15, 4);
				sub2 = substring(filename, 11, 3);
				strcpy(result, sub1);
				strcat(result, "-");
				if( strcmp( sub2, "Jan" ) == 0)
					strcat(result, "01");
				else if( strcmp( sub2, "Feb" ) == 0)
					strcat(result, "02");
				else if( strcmp( sub2, "Mar" ) == 0)
					strcat(result, "03");
				else if( strcmp( sub2, "Apr" ) == 0)
					strcat(result, "04");
				else if( strcmp( sub2, "May" ) == 0)
					strcat(result, "05");
				else if( strcmp( sub2, "Jun" ) == 0)
					strcat(result, "06");
				else if( strcmp( sub2, "Jul" ) == 0)
					strcat(result, "07");
				else if( strcmp( sub2, "Aug" ) == 0)
					strcat(result, "08");
				else if( strcmp( sub2, "Sep" ) == 0)
					strcat(result, "09");
				else if( strcmp( sub2, "Oct" ) == 0)
					strcat(result, "10");
				else if( strcmp( sub2, "Nov" ) == 0)
					strcat(result, "11");
				else if( strcmp( sub2, "Dec" ) == 0)
					strcat(result, "12");
				else
					strcat(result, sub2);
				strcat(result, " AMEX");
				strcat(result, ext);
				printf("mv \"%s\" \"%s\"\n", ep->d_name, result );
			}
			else
			{
				printf("TODO => %s\n", filename);
			}
		}
		(void) closedir (dp);
    }
	else
		perror ("Couldn't open the directory");

	return 0;
}

// ----------------------------------------------------------------------------
// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with)
{
	char *result; // the return string
	char *ins;    // the next insert point
	char *tmp;    // varies
	int len_rep;  // length of rep
	int len_with; // length of with
	int len_front; // distance between rep and end of last rep
	int count;    // number of replacements

	if (!orig)
		return NULL;
	if (!rep)
		rep = "";
	len_rep = strlen(rep);
	if (!with)
		with = "";
	len_with = strlen(with);

	ins = orig;
	for (count = 0; tmp = (char *)strstr(ins, rep); ++count) {
		ins = tmp + len_rep;
  }

  // first time through the loop, all the variable are set correctly
  // from here on,
  //    tmp points to the end of the result string
  //    ins points to the next occurrence of rep in orig
  //    orig points to the remainder of orig after "end of rep"
  tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

  if (!result)
    return NULL;

  while (count--) {
    ins = strstr(orig, rep);
    len_front = ins - orig;
    tmp = strncpy(tmp, orig, len_front) + len_front;
    tmp = strcpy(tmp, with) + len_with;
    orig += len_front + len_rep; // move to next "end of rep"
  }
  strcpy(tmp, orig);
  return result;
}


// ----------------------------------------------------------------------------
// C substring function: It returns a pointer to the substring
char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position-1);      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}
