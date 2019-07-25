/*
 * Author   : Julian C.
 * Version  : V 3.11.61
 * Function : Compile .cpp files and execute.
 *
 * Name of version: Va.b.c
 *   a -> Major changes.
 *   b -> Minor changes. + a            // in new versionation: if a++ then b = 0.
 *   c -> Nº times compile. + b + a    // in new versionation: if a++ or b++ then c++.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <fstream> // http://www.chuidiang.org/clinux/ficheros/fichero-texto-cpp.php
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

//This is a usefull program to compile and execute files .cpp...
#define ARGS 0
#define SOURCES 1
#ifdef __linux__
    #define OS "linux"
#else 
    #define OS "others"
#endif /* ifdef OS */

using namespace std;

void create_history ( ); //Create a history of files compiled and check History.txt
string seek_history ( char file[20], int, char ** );
void read_history ( );
void compile ( string cmd, char file[20], string str_file, string *others_to_compile, int ); //Compile a file.cpp
void execute ( string cmd, string file, string* args ); //Execute a file.exe
void get ( int, char **, int, string * );
int how_much ( int, char **, int what );

int main ( int argc, char *argv[] ) // **argv
{
    /*cout << "HM ARGS: " << how_much(argc, argv, ARGS) << endl;
    cout << "HM SOURCES: " << how_much(argc, argv, SOURCES) << endl;*/
    string command = "";
    string *others; // No inicializar
    char file[20];
    string str_file;
    create_history( );
    str_file = seek_history( file, argc, argv );

    others = new string[how_much( argc, argv, SOURCES )];
    get( argc, argv, SOURCES, others );
    compile( command, file, str_file, others, how_much( argc, argv, SOURCES ) );
    delete[] others;
    
    others = new string;
    *others = "";
    get( argc, argv, ARGS, others );
    execute( command, str_file, others );
    delete others;

    read_history( );
    return EXIT_SUCCESS;
}

void create_history ( )
{
    ifstream history_in; //Input file stream
    history_in.open( "History.txt", ios::in ); //Check the file
    if ( history_in.fail( ) ) //If the file isn't create, then create the file
    {
        cout << "I can't find a History.txt, then I create a History.txt" << endl;
        ofstream history_out;
        history_out.open( "History.txt", ios::out );
        history_out.close( );
    }
    else
    {
        history_in.close( );
    }
}

string seek_history ( char file[20], int argc, char *argv[] )
{
    bool w = true, new_program;
    char name[20], name_ver[50], ver[20], Vabc;     // old: Version en forma a.b.c (a= nuevas funciones,
    unsigned int i, /*j,*/ v, point1=0, point2=0;  // old: b= bugs arreglados, c= Nº de veces compilado)
    unsigned int v_a=0, v_b=0, v_c=0;
    string info;
    if ( 1 < argc )//argc == 2 )
    {
        cout << "\n\nName of file: " << argv[1] << ".cpp" << endl;
        // Mejorarlo añadiendo un analizador de los argumentos suministrados.
    }
    else
    {
        cout << "\n\nMore o few arguments.\n";
        cout << "Name of file(.cpp): "; cin >> file;
    }
//ifstream==========================================================================================
    ifstream history_in;
    history_in.open( "History.txt", ios::in );
    if ( history_in.fail( ) )
    {
        cout << "I cannot seek in the file" << endl;
        exit( 1 );
    }
//==================================================================================================
    while( !history_in.eof( ) ) //Da 'name', 'ver' y 'name_ver'
    {
        memset( name, '\0', 20 ); //Vaciar con memset(buffer, '\0', longitud)
        memset( ver, '\0', 20 ); //Vaciar con memset(buffer, '\0', longitud)
        getline( history_in, info );
        strcpy( name_ver, info.c_str( ) );
        for ( i=0; i < info.length( ); i++ ) //Recorrer lo que mide la linea del archivo para ubicar V
        {
            if ( name_ver[i] == 'V' )
            {
                v=i;
            }
        }
        for ( i = 0; i < info.length( ); i++ ) //Recorrer el nombre del programa e introducirlo en 'name' y 'ver'
        {
            if ( i < v )
            {
                name[i] = name_ver[i];
            }
            else
            {
                ver[i - v] = name_ver[i];
            }
        }
//Check the program=================================================================================
        if ( strcmp( file, name ) == 0 )
        {
            new_program = false; //old_program :)
        }
        else
        {
            new_program = true;
        }
//==================================================================================================
        if ( !new_program )
        {
            char ver_a[16], ver_b[16], ver_c[16];
            for ( i = 0; i < ( info.length( ) - v ); i++ ) //Recorrer 'ver' para situar los dos puntos
            {
                if ( ver[i] == '.' )
                { 
                    if ( point1 == 0 )
                    {
                        point1 = i;
                    }
                    else
                    {
                        point2 = i;
                    }
                }
            }
            memset( ver_a, '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            memset( ver_b, '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            memset( ver_c, '\0', 16 ); //Vaciar con memset(buffer, '\0', longitud)
            for ( i = 1; i < ( info.length( ) - v ); i++ ) //Introduce el numero de la version
            {
                if ( i < point1 )
                {
                    ver_a[i - 1] = ver[i];
                }
                else if ( i > point1 && i < point2 )
                {
                    ver_b[i - ( point1 + 1 )] = ver[i];
                }
                else if ( i > point2 )
                {
                    ver_c[ i - ( point2 + 1 )] = ver[i];
                }
            }
            v_a = atoi( ver_a ); //Cambia el string a int para usarlo
            v_b = atoi( ver_b );
            v_c = atoi( ver_c );
        }
    } //while(!history_in.eof())
    memset( name_ver, '\0', 50 ); //Vaciar con memset(buffer, '\0', longitud)
    strcpy( name_ver, name );
    if ( new_program ) //Se necesita fuera del while
    {
        cout << "Introducing " << file << " in History.txt" << endl;
    }
    while ( w )
    {
        cout << "Type of change?(Va.b.c)" << endl;
        cin >> Vabc;
        switch( Vabc )
        {
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
                cout << "'" << Vabc << "' isn't 'a','b' or 'c'.\nPlease try again." << endl;
                break;
        }
    }
    info = argv[1];//+ "V" + to_string(v_a) + ".";
    info += 'V';
    info += to_string( v_a );
    info += '.';
    info += to_string( v_b );
    info += '.';
    info += to_string( v_c );
//ofstream==========================================================================================
    ofstream history_out;
    history_out.open( "History.txt", ios::app );
    if ( history_out.fail( ) )
    {
        cout << "I cannot open the file" << endl;
        exit( 1 );
    }
    history_out << info << endl; // << '\n'
//==================================================================================================
    cin.get( );
    history_in.close( );
    history_out.close( );
    return info;
}

void read_history ( )
{
    char c;
    string info;
    cout << "Do you want to read a History.txt?(y/N) : " << endl;
    cin.get(c);
    if ( c == 'y' || c == 'Y' )
    {
        ifstream history_in;
        history_in.open( "History.txt", ios::in ); // Open for reading
        if ( history_in.fail( ) )
        {
            cout << "I can't read a History.txt" << endl;
            exit( 1 );
        }
        while( !history_in.eof( ) ) // While isn't end of file of 'file'
        {
            //history_in.get(c);
            //cout<<c;
            getline( history_in, info );
            cout << info << endl;
        }
        history_in.close( );
        cin.get( );
    }
    else if ( c != '\n' )
    {
        cin.get( );
    }
    cout << "Goodbye";
    cin.get( );
}

void compile ( string cmd, char file[20], string str_file, string *others_to_compile, int size )
{
    string others = "";
    string others_comp = "";
    cmd += "g++ -c -std=c++14 " + (string)file + ".cpp ";
    for( int i = 0; i < size; i++ )
    {
        cmd += *(others_to_compile + i) + ".cpp ";
        others += *(others_to_compile + i) + ".cpp ";
        others_comp += *(others_to_compile + i) + ".o ";
    }
    system( cmd.c_str( ) );
    //cout << cmd << endl;
    cout << "Compiled " << file << ".cpp " << others << endl;

    cmd = "g++ -std=c++14 " + (string)file + ".o " + others_comp + "-o " + str_file;
    system( cmd.c_str( ) );
    cout << "Compiled " << file << ".o " << others_comp << endl;
    //cout << cmd << endl;
    cout << "Press enter..." << endl;
    cin.get( );
}

void execute ( string cmd, string file, string *args )
{
    time_t start, end;
    double executing_time;
    if ( OS == "linux" )
    {
        cmd = "./" + file + " " + *args;
    }
    else // for Windows
    {
        cmd = file + " " + *args;
    }
    cout << "Executing " << cmd << endl;
    start = time(&start);
    system( cmd.c_str( ) );
    end = time(&end);
    executing_time = difftime( end, start );
    cout << endl << "End of program." << endl << "Press enter..." << endl;
    cout << "Executing time: " << executing_time << " seconds." << endl;
    cin.get( );
}

int how_much ( int argc, char *argv[], int what )
{
    bool found = false, found_arg = false;
    int result = 0;
    int i;
    for( i = 2; i < argc && !found; i++ )
    {
        if ( what == SOURCES && ( (string)argv[i] == "-args" || (string)argv[i] == "-a" ) )
        {
            found = true;
        }
        else if ( what == SOURCES )
        {
            result++;
        }
        else if ( (string)argv[i] == "-args" || (string)argv[i] == "-a" )
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

void get ( int argc, char *argv[], int what, string *strs )
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
            *strs += (string)argv[i] + " ";
        }
    }
}
