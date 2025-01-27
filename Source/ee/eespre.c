﻿//This file is part of EESLISM.
//
//Foobar is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Foobar is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Foobar.If not, see < https://www.gnu.org/licenses/>.

/*   ee_spre.c  */
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "common.h"
#include "esize.h"
#include "fesy.h"
#include "fnfio.h"
#include "winerror.h"
#include "fnlib.h"

/**
 * @file
 * @brief 事前処理
 */


/* ---------------------------------------------------------- */

/*        注釈文の除去             */

void eesprera (char *File, char *Ipath)
{
	FILE *fi, *fb ;
	char  s[SCHAR], c, RET[SCHAR];
	//int len ;
	char *STRCUT(char *DATA, char a);

	//len = strlen(File);
	//printf("s3=%s %d\n",File,len);

	if ((fi = fopen(File, "r")) == 0)
	{
		Eprint ( "<eesprera>", File ) ;
		preexit ( ) ;
		exit(EXIT_INPUT);
	}
	strcpy(RET, STRCUT(File, '.'));
	fb = fopen(strcat(strcpy(s, RET), "bdata0.ewk"), "w");
	
	while (fscanf(fi," %s ", s) >= 0)
	{
		if (strcmp(s, "!") == 0)
		{
			while (fscanf(fi, "%c", &c),  c != '\n')
				;
		}
		else
		{
			if (strcmp(s, "　") == 0)
				fprintf(fb, "  ") ;
			else
				fprintf(fb, " %s ", s);
			
			if (strcmp(s, ";") == 0 || s[strlen(s)-1] == ';')
				fprintf(fb,"\n");
			else if (strcmp(s, "#") == 0 || s[strlen(s)-1] == '#')
				fprintf(fb,"\n");
			else if (strcmp(s, "*") == 0 || s[strlen(s)-1] == '*')
				fprintf(fb,"\n");
			else if (strcmp(s, "*debug") == 0)
				EnterDebugMode();

		}
	}
	fclose(fi);
	fprintf(fb," \n"), fclose(fb);
}

/* ---------------------------------------------------------- */	       

/*              スケジュ－ルデ－タファイルの作成    */

void eespre(char *File, char *Ipath, int *key)
{
	FILE *fi, *fb, *fs, *fsn, *fw ;
	char  s[2048], *st, *stt, t[2048] ; //  schnm[DSCHMX][SCHAR], scwnm[DSCHMX][SCHAR];
//	int i ; // Nsch=0, Nscw=0;
	int		syspth, syscmp ;
	long	ad ;

	syspth = syscmp = 0 ;
	
	if ((fi = fopen(strcat(strcpy(s,Ipath), File), "r")) == 0)
	{
		Eprint ( "<eespre>", File ) ;

		preexit ( ) ;
		exit(EXIT_INPUT);
	}

	Syscheck ( fi, &syspth, &syscmp ) ;
	
	fb = fopen(strcat(strcpy(s, Ipath), "bdata.ewk"), "w");
	fs = fopen(strcat(strcpy(s, Ipath), "schtba.ewk"), "w");
	fsn= fopen(strcat(strcpy(s, Ipath), "schnma.ewk"), "w");
	fw = fopen(strcat(strcpy(s, Ipath), "week.ewk"), "w");
	
	while (fscanf(fi," %s ", s) >= 0)
	{
		//		printf ( "<eespre> %s\n", s ) ;
		
		if (strcmp(s, "TITLE") == 0)
		{
			fscanf(fi, " %[^;];", s);
			fprintf(fb, "TITLE  %s ;\n", s);
		}
		/**********************************
		else if (strcmp(s, "!") == 0)
		{
		while (fscanf(fi, "%c", &c),  c != '\n')
		;
		}
		**********************************/
		
		else if (strncmp(s, "wbmlist=", 8) == 0)
		{
			if ((st = strchr(s, ';' )) != NULL )
				*(st+1) = '\0' ;
			else
				fscanf ( fi, "%*s" ) ;

			set_fbm_list_filename(s + 8);
		}

		else if (strcmp(s, "WEEK") == 0 )
		{
			*key = 1 ;
			fscanf(fi, " %[^;];", s ) ;
			fprintf(fw, "%s ;\n", s ) ;
		}
		else if (strcmp(s, "%s") == 0)
		{
			fscanf(fi, " %[^;];", s); 
			fprintf(fs, "%s ;\n", s);
		}
		else if (strcmp(s, "%sn") == 0)
		{
			fscanf(fi, " %[^;];", s);
			fprintf(fsn, "%s ;\n", s);
		}
		else if ((st=strchr(s, '"')) != 0)
		{	 
			fprintf(fb, " %s ", s);
			while (st != 0)
			{
				stt=strchr(st+1, '"');
				*stt='\0';
				if (isalpha(*(st+1)) != 0 || 
					strcmp(st+1, "-")== 0 || strcmp(st+1, "+")== 0)
				{
				/*****************************
					for (i=0; i<Nscw; i++)
					{
						if (strcmp(scwnm[i], st) == 0)
							break;
					}
					if (i == Nscw)
					{
						strcpy(scwnm[Nscw], st);
						Nscw++ ;
					*********************************/
						fprintf(fs, "-s %s%c  000-(%c)-2400 ;\n", st, '"', *(st+1));
						/*****************************
					}
					****************************/
				}
				else
				{
					/************************
					for (i=0; i<Nsch; i++)
					{
						if (strcmp(schnm[i], st) == 0)
							break;
					}
					if (i == Nsch)
					{
						strcpy(schnm[Nsch], st);
						Nsch++ ;
						*****************************/
						fprintf(fs, "-v %s%c  000-(%s)-2400 ;\n", st, '"', st+1);
						/****************************
					}
					*****************************/
				}
				
				st=strchr(stt+1, '"');
			}
		}
		else
		{
			if ( s[strlen(s)-1] == ';' )
			{
				strcpy ( t, s ) ;
				t[strlen(t)-1] = '\0' ;
				fprintf ( fb, " %s ; ", t ) ;
			}
			else
				fprintf(fb, " %s ", s);
			
			if (strcmp(s, ";") == 0 || s[strlen(s)-1] == ';')
				fprintf(fb,"\n");
			else if (strcmp(s, "#") == 0 || s[strlen(s)-1] == '#')
				fprintf(fb,"\n");
			else if (strcmp(s, "*") == 0 || s[strlen(s)-1] == '*')
				fprintf(fb,"\n");
		}
	}
	fclose ( fi ) ;

	fprintf ( fb, "\n" ) ;

	ad = ftell ( fb ) ;
#ifdef WIN32
	//6文字分戻る(改行コード2文字含む)
	fseek ( fb, ad - 6, SEEK_SET ) ;
#else
	fseek ( fb, ad - 4, SEEK_SET ) ;
#endif

	//if ( syscmp == 0 )
	//	fprintf ( fb, " SYSCMP\n *\n" ) ;
	//if ( syspth == 0 )
	//	fprintf ( fb, " SYSPTH\n *\n" ) ;

	fprintf ( fb, " *\n" ) ;
	fprintf(fw, "\n");
	fclose(fw);
	fclose ( fb ) ;
	fprintf(fs, "*\n");
	fclose(fs);
	fprintf(fsn, "*\n");
	fclose(fsn);
}

/******************************************************************/

void	Syscheck ( FILE *fi, int *syspth, int *syscmp )
{
	char	s[2048] ;

	while ( fscanf ( fi, "%s", s ) != EOF )
	{
		if ( strcmp ( s, "SYSPTH" ) == 0 )
			*syspth = 1 ;
		else if ( strcmp ( s, "SYSCMP" ) == 0 )
			*syscmp = 1 ;
	}

	rewind ( fi ) ;
}
