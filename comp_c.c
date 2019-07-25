/*
 * Author   : Julian C.
 * Version  : V 3.12.62
 * Function : Compile .c files and execute.
 *
 * Name of version: Va.b.c
 *   a -> Major changes.
 *   b -> Minor changes. + a            // in new versionation: if a++ then b = 0.
 *   c -> Nº times compile. + b + a    // in new versionation: if a++ or b++ then c++.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//This is a usefull program to compile and execute files .c...
#define ARGS 0
#define SOURCES 1
#ifdef __linux__
    #define OS "linux"
#else 
    #define OS "others"
#endif /* ifdef OS */

void create_history ( ); //Create a history of files compiled and check History.txt
char* seek_history ( int, char** );
void read_history ( );
void compile ( char* file, char* str_file, char** others_to_compile, int ); //Compile a file.c
void execute ( char* file, char* args ); //Execute a file
void get ( int, char** , int, char** );
int how_much ( int, char** , int what );
void init_matrix ( char*** , int, int );
void delete_matrix ( char** , int );


int main ( int argc, char* argv[] ) // **argv
{
    char** others = NULL;
    char* str_file;
    int how_sources = how_much( argc, argv, SOURCES );
    create_history( );
    str_file = seek_history( argc, argv );

    init_matrix( &others, how_sources, 30 );
    get( argc, argv, SOURCES, others );
    compile( argv[1], str_file, others, how_sources );
    //delete_matrix( others, how_sources ); // Se supone que habria que eliminarlo así.
    free(others);
    others = NULL;

    others = calloc( 1, sizeof(char* ) );
    *others = calloc( 100, sizeof(char) );
    get( argc, argv, ARGS, others );
    execute( argv[1], *others );
    free(others);
    others = NULL;
    
    read_history( );
    return 0;
}

void create_history ( )
{
    FILE* history_in;
    history_in = fopen( "History.txt", "r" ); // Intentar leer el archivo
    if ( history_in == NULL )
    {
        printf("I can't find a History.txt, then I create a History.txt");
        FILE* history_out = fopen( "History.txt", "w" );
        if (fclose(history_out)) // No seria necesario, solo con escribir fclose(history_out);, mas que suficiente
        {
            printf("I couldn't close History.txt\n");
            exit(-1);
        }
    }
    else
    {
        fclose(history_in);
    }
}

char* seek_history ( int argc, char* argv[] )
{
    bool w = true, new_program = true, found = false, same_program;
    char* name, *name_ver, *ver, Vabc;     // old: Version en forma a.b.c (a= nuevas funciones,
    unsigned int i, v;                             // old: b= bugs arreglados, c= Nº de veces compilado)
    unsigned int v_a = 0, v_b = 0, v_c = 0;
    //char info[30];
    char* info = calloc( 50, sizeof(char) );
    name = calloc( 20, sizeof(char) );
    name_ver = calloc( 50, sizeof(char) );
    ver = calloc( 20, sizeof(char) );
    if ( 1 < argc )
    {
        // Cambiar todo esto, el nombre del archivo siempre estará ubicado en argv[1]
        printf( "\n\nName of file: %s.cpp\n", argv[1] );
        // Mejorarlo añadiendo un analizador de los argumentos suministrados.
    }
    else
    {
        printf("How to use:\n");
        //TODO
        exit(0);
    }
//history_in========================================================================================
    FILE* history_in = fopen( "History.txt", "r" );
    if ( history_in == NULL )
    {
        printf("I cannot seek in the file\n");
        exit(-2);
    }
//==================================================================================================
    while(!feof(history_in)) //Da 'name', 'ver' y 'name_ver'
    {
        fgets( info, 50, history_in );
        strcpy( name_ver, info );
        for ( i = 0; i < strlen(name_ver); i++ )
        {
            if ( name_ver[i] != 'V' )
            {
                if (!found)
                {
                    name[i] = name_ver[i];
                }
                else
                {
                    ver[i - v] = name_ver[i];
                }
            }
            else
            {
                found = true;
                v = i + 1;
            }
        }
        found = false;
//Check the program=================================================================================
        if (!strcmp( argv[1], name ))
        {
            new_program = false; //old_program :)
            same_program = true;
        }
        else
        {
            same_program = false;
        }
//==================================================================================================
        if (same_program)
        {
            char ver_abc[3][16];
            int points_count = 0, point_pos = 0;
            memset( ver_abc[0], '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            memset( ver_abc[1], '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            memset( ver_abc[2], '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            for ( i = 0; i < strlen(ver); i++ ) //Recorrer 'ver' para situar los dos puntos
            {
                if ( ver[i] == '.' )
                {
                    points_count++;
                    point_pos = i + 1;
                }
                else
                {
                    ver_abc[points_count][i - point_pos] = ver[i];
                }
            }
            v_a = atoi( ver_abc[0] ); //Cambia el char array a int para usarlo
            v_b = atoi( ver_abc[1] );
            v_c = atoi( ver_abc[2] );
        }
        memset( name, '\0', 20 ); //Vaciar con memset(buffer, '\0', longitud)
        memset( ver, '\0', 20 ); //Vaciar con memset(buffer, '\0', longitud)
    } //while(!feof(history_in))
    memset( name_ver, '\0', 50 ); //Vaciar con memset(buffer, '\0', longitud)
    strcpy( name_ver, name );
    if ( new_program ) //Se necesita fuera del while
    {
        printf( "Introducing %s in History.txt\n", argv[1] );
    }
    //while(w) // Arreglar bug
    do {
        printf("Type of change?(Va.b.c)\n");
        scanf( "%s", &Vabc );
        //Vabc = getchar( );
        switch (Vabc) {
            case 'a':
                v_a++;
                v_b = 0;
                v_c++;
                w = false;
                break;
            case 'b':
                v_b++;
            case 'c':
                v_c++;
                w = false;
                break;
            default:
                printf( "'%c' isn't 'a','b' or 'c'.\nPlease try again.\n", Vabc );
                w = true; // Esto está porque si no se sale del bucle.
                break;
        }
    } while(w);
    sprintf( info, "%sV%d.%d.%d", argv[1], v_a, v_b, v_c );
//history_out=======================================================================================
    FILE* history_out = fopen( "History.txt", "a" );
    if ( history_out == NULL )
    {
        printf("I cannot open the file\n");
        exit(-2);
    }
    fputs( info, history_out );
    fputs( "\n", history_out );
//==================================================================================================
    getchar( );
    fclose(history_in);
    fclose(history_out);
    free(name_ver);
    free(name);
    free(ver);
    name_ver = NULL;
    name = NULL;
    ver = NULL;
    return info;
}

void read_history ( )
{
    char c;
    int lines = 0, paragraphs = 15;
    char* info = calloc( 50, sizeof(char) );
    printf( "Do you want to read a History.txt?(y/N) : " );
    c = getchar( );
    if ( c == 'y' || c == 'Y' )
    {
        FILE* history_in = fopen( "History.txt", "r" ); // Open for reading
        if ( history_in == NULL )
        {
            printf( "I can't read a History.txt" );
            exit(-1);
        }
        getchar( );
        while(!feof(history_in)) // While isn't end of file of 'file'
        {
            fgets( info, 50, history_in );
            printf( "%s", info );
            if ( (lines + 1) % (paragraphs + 1) == 0 )
            {
                getchar( );
            }
            lines++;
        }
        fclose(history_in);
        getchar( );
    }
    else if ( c != '\n' )
    {
        getchar( );
    }
    printf("Goodbye");
    getchar( );
}

void compile ( char* file, char* str_file, char** others_to_compile, int size )
{
    char* cmd = calloc( 300, sizeof(char) );
    char* others = calloc( 300, sizeof(char) );
    char* others_comp = calloc( 300, sizeof(char) );
    sprintf( cmd, "gcc -c -std=c11 -Wall -Wextra %s.c ", file );
    for( int i = 0; i < size; i++ )
    {
        strcat( cmd, *( others_to_compile + i) );
        strcat( cmd, ".c " );
        strcat( others, *( others_to_compile + i) );
        strcat( others, ".c " );
        strcat( others_comp, *( others_to_compile + i) );
        strcat( others_comp, ".o " );
    }
    system( cmd );
    printf( "Compiled %s.c %s\n", file, others );
    sprintf( cmd, "gcc -std=c11 -Wall -Wextra %s.o %s-o %s", file, others_comp, str_file );
    system( cmd );
    printf( "Compiled %s.o %s\n", file, others_comp );
    printf( "Press enter...\n" );
    getchar( );
    free(cmd);
    free(others);
    free(others_comp);
    cmd = NULL;
    others = NULL;
    others_comp = NULL;
}

void execute ( char* file, char* args )
{
    char* cmd = calloc( 300, sizeof(char) );
    time_t start, end;
    double executing_time;
    if ( !strcmp( OS, "linux") )
    {
        sprintf( cmd, "./%s %s", file, args );
    }
    else // for Windows
    {
        sprintf( cmd, "%s %s", file, args );
    }
    printf( "Executing %s\n", cmd );
    start = time(&start);
    system( cmd );
    end = time(&end);
    executing_time = difftime( end, start );
    printf("\nEnd of program.\nPress enter...\n");
    printf( "Executing time: %.f seconds,", executing_time );
    getchar( );
    free(cmd);
    cmd = NULL;
}

int how_much ( int argc, char* argv[], int what )
{
    bool found = false, found_arg = false;
    int result = 0;
    int i;
    for( i = 2; i < argc && !found; i++ )
    {
        if ( what == SOURCES && ( !strcmp( argv[i], "-args") || !strcmp( argv[i], "-a" ) ) )
        {
            found = true;
        }
        else if ( what == SOURCES )
        {
            result++;
        }
        else if ( !strcmp( argv[i], "-args" ) || !strcmp( argv[i], "-a" ) )
        {
            found_arg = true;
        }
        else if ( found_arg )
        {
            result++;
        }
    }
    //return what * (argc - i - 1) -(what - 1) * (i - 2);
    return what * result -(what - 1) * result;
    //        ^ARGS^            ^SOURCES^
}

void get ( int argc, char* argv[], int what, char** strs )
{
    int args_others = how_much( argc, argv, SOURCES );
    int pos_init = 2;
    if ( what == SOURCES && 0 < args_others )
    {
        for( int j = 0; j < args_others; j++ )
        {
            strs[j] = argv[pos_init + j];
        }
    }
    else if ( what == ARGS )
    {
        args_others = how_much( argc, argv, ARGS );
        pos_init = 2 + how_much( argc, argv, SOURCES ) + 1;
        for( int i = pos_init; i < pos_init + args_others; i++ )
        {
            strcat( *strs, argv[i] );
            strcat( *strs, " " );
        }
    }
}
// Utilizo un char*** porque necesito ir a la direccion del char**
void init_matrix ( char*** buffer, int rows, int colunms )
{
    *buffer = calloc( rows, sizeof(char* ) );
    for ( int i = 0; i < rows; i++ )
    {
        *buffer[i] = calloc( colunms, sizeof(char) );
    }
}

void delete_matrix ( char** buffer, int rows )
{
    for( int i = 0; i < rows; i++ )
    {
        free(buffer[i]);
        printf("\n[%d]\n", i);
    }
    free(buffer);
}
