// Version: 1.3.12
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main ( int argc, char *argv[] )
{
    if ( 1 < argc )
    {
        string file, command;
        file = argv[1];
        cout << "Name of file.java is '" << file << "'." << endl;
        cout << "Compiling " << file << ".java" << endl;
        command = "javac " + file + ".java";
        system( command.c_str( ) );
        cout << "Executing " << file << ".class" << endl << endl;
        command = "java " + file;
        if ( 2 < argc ) //argumentos para el programa
        {
            for ( int i = 0; i + 2 < argc; i++ )
            {
                command = command + " " + argv[i + 2];
            }
        }
        //cout << "CMD: " << command;
        system( command.c_str( ) );
    }
    else
    {
        char yn;
        string args;
        cout << "Error too many arguments or few arguments." << endl;
        string file, command;
        cout << "Type de name of file.java" << endl;
        cin >> file;
        cout << "Name of file.java is '" << file << "'." << endl;
        cout << "Compiling " << file << ".java" << endl;
        command = "javac " + file + ".java";
        system( command.c_str( ) );
        cout << "Executing " << file << ".class" << endl << endl;
        command = "java " + file;
        cout << "Do you want to add args for the java program?" << endl;
        cin >> yn;
        while( yn == 'y' || yn == 'Y' ) //argumentos para el programa 
        {
            cin >> args;
            command = command + " " + args;
            cout << "Do you want to add more args for the java program?" << endl;
            cin >> yn;
        }
        //cout << "CMD: " << command;
        system( command.c_str( ) );
    }
    return ( 0 );
}
