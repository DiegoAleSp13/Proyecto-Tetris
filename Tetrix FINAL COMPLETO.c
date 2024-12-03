#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
void mostrarranking();
void puntaje();
void setColor(int color);
void tetris();
int elegirpieza();
void posicionpieza(int Posicion, char pieza[4][4]);
void printMatrix(char matriz[21][12]);
void RotacionPiezas(int *fila,int *columna,int *rotar,int Posicion, char Pieza[4][4],char matriz[21][12]);

void setColor(int color)
{
    // Obtiene el manejador de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Cambia el color del texto
    SetConsoleTextAttribute(hConsole, color);
    //0 - Negro/1 - Azul/2 - Verde/3 - Aqua/4 - Rojo/5 - Púrpura/6 - Amarillo/7 - Blanco/8 - Gris/9 - Azul brillante/10 - Verde brillante/11 - Aqua brillante/12 - Rojo brillante/13 - Magenta brillante/14 - Amarillo brillante/15 - Blanco brillante
}
struct Jugador
{
    int puntos;
    char NOMBRE[3];
};

int  main()
{
    char opc;
    struct Jugador Usuario;
    do
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf(" ________________________________________________________\n");
        printf("|     [][][][] [][][][] [][][][] [][][][] []  []  []     |\n");
        printf("|        []    []          []    []    []      [][]      |\n");
        printf("|        []    [][][]      []    [][][]   []    []       |\n");
        printf("|        []    []          []    []    [] []   [][]      |\n");
        printf("|        []    [][][][]    []    []    [] []  []  []     |\n");
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238);
        printf("%c%c%c%c",238,238,238,238);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238);
        setColor(13);
        printf("    .................................................    \n");
        printf("   :+=------------+*+=------------=*+=------------=*-    \n");
        printf("   :+*::::::::---=#*++-::::::::---##++=::::::::---*#-    \n");
        printf("   :+*----===++++*#*++-----==+++**##++=----==++++**#-    \n");
        printf("   .++==++********#*++==++********##+++=++********##-    \n");
        printf("   .++************#*++************##+++***********##-    \n");
        printf("   .++************#*++************##+++***********##-    \n");
        printf("   .++************#*++************##+++***********##-    \n");
        printf("   :++#***##*****##+++******####**##++******##****##-    \n");
        printf("   .**############*==*#############*+*#############*-    \n");
        printf("                    ==------------=+.                    \n");
        printf("                    ++-:::::------##.                    \n");
        printf("                    ++-:-----====+##.                    \n");
        printf("                    ++===++*******##.                    \n");
        printf("                    +++***********##.                    \n");
        printf("                    ++************##.                    \n");
        printf("                    ++************##.                    \n");
        printf("                    ++************##.                    \n");
        printf("                    +*##############.                    \n");
        printf("                    ::::::::::::::::                     \n");
        setColor(7);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("Ingrese la primera letra para acceder a la interfaz\n");
        printf("[I]Iniciar Partida\n[R]RANKING (Mayores puntajes)\n[S]Salir\n"); //ESTO DE RANKING VA A ESTAR CON ARCHIVOS
        scanf(" %c",&opc);
        switch(opc)
        {
        case 'I':
        case 'i':
            setColor(2);
            srand(time(NULL));
            tetris();
            break;
        case 'R':
        case 'r':
            system("cls");
            printf("RANKING DE LOS MEJORES JUGADORES DE LOS CONOCIDOS DEL CREADOR [PODRAS SUPERARLOS?]\n");
            printf("ADVERTENCIA:\nEl uso de hacks o errores al lado del creador sera etado y tendra que pagar USD 1 al creador.\n");

            mostrarranking();

            system("pause");
            break;
        case 'S':
        case 's':
            printf("FIN DEL JUEGO. ESPERO QUE TE HAYA GUSTADO... Y sino... Quejarse al siguiente numero +54 9 11 6716-5563\n");
            sleep (2);
            break;
        default:
            printf("\nERROR 1603. Para mas informacion buscar ARREGLAR.MIKE.COM\n");
            printf("Escriba algo normal por favor...\n");
            sleep(3);
            break;
        }

        system("cls");
    }
    while(opc!='S' && opc!='s');
    return 0;
}
void tetris()
{
    struct Jugador Usuario;
    Usuario.puntos=0;
    int partida=0;
    int Piezaseleccionada=0;
    char piezaEXT[4][4] = {0};
    int CantPiezas[100]= {0};
    char matriz[21][12] = {0}; //0 y 11 son paredes, 20 tambien el piso. Quedaria de 1 a 10 y 0 a 19 20x10
    for (int j=0; j<12; j++)
    {
        matriz[20][j]=254;
    }
    for (int i=0; i<20; i++)
    {
        matriz[i][11]=254;
        matriz[i][0]=254;
    }
    do
    {
        int Pieza = elegirpieza(CantPiezas, &Piezaseleccionada);
        Piezaseleccionada++;
        posicionpieza(Pieza, piezaEXT); //SE GUARDA EN LA PIEZA EXTERNA EL VALOR PARA SER INTEGRADO EN LA MATRIZ PRINCIPAL
        int Colision=0; //SI OCURRE COLISION... KABOOM!
        int fila = 0; //FILA POR DONDE EMPIEZA A CAER LAS PIEZAS
        char PiezaOriginal[4][4]= {0}; //MATRIZ PARA QUE SE GUARDE LA PIEZA ORIGINAL
        int columna = 4; //COLUMNA POR DONDE EMPIEZAN A CAER LAS PIEZAS
        int rotar=0; //PUNTERO QUE ROTA DEPENDIENDO DEL VALOR
        while (Colision!=1)
        {
            int Verfcolision=0;
            int aux=0;
            system("cls");
            if(rotar==0)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        PiezaOriginal[i][j]=piezaEXT[i][j];
                    }
                }
            }

            if ((GetAsyncKeyState(VK_UP) || (GetAsyncKeyState(0x52)))) //ARRIBA O R PARA ROTAR
            {
                rotar++;
                RotacionPiezas(&fila,&columna,&rotar,Pieza, piezaEXT,matriz);
                if(rotar==0)
                {

                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(matriz[fila+i][columna+j+1]==0 && PiezaOriginal[i][j]!=0 && matriz[fila+i][columna+j-1]==0)
                            {
                                Verfcolision++;
                            }
                        }
                    }
                    if(Verfcolision==4)
                    {
                        for(int i=0; i<4; i++)
                        {
                            for(int j=0; j<4; j++)
                            {
                                piezaEXT[i][j]=PiezaOriginal[i][j];
                            }
                        }
                    }
                    Verfcolision=0;
                }
            }
            if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41))) //IZQUIERDA CON A
            {

                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        if(matriz[fila+i][columna+j-1]==0 && piezaEXT[i][j]!=0)
                        {
                            Verfcolision++;
                        }
                    }
                }
                if(Verfcolision==4)
                {
                    columna--;
                }
                Verfcolision=0;
            }

            if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44))) //DERECHA CON D
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        if(matriz[fila+i][columna+j+1]==0 && piezaEXT[i][j]!=0)
                        {
                            Verfcolision++;
                        }
                    }
                }
                if(Verfcolision==4)
                {
                    columna++;
                }
                Verfcolision=0;
            }

            if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53))) //ABAJO CON S
            {
                do
                {
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(matriz[fila+i+1][columna+j]!=0 && piezaEXT[i][j]!=0)
                            {
                                Verfcolision=1;
                            }
                        }
                    }
                    if(Verfcolision==1)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                {
                                    if (piezaEXT[i][j]!=0)
                                    {
                                        matriz[fila+i][columna+j] = piezaEXT[i][j];
                                    }
                                }
                            }
                        }
                        Colision=1;
                        sleep(0.5);
                    }
                    else
                        fila++;
                }
                while(Colision!=1);
            }

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[fila+i+1][columna+j]!=0 && piezaEXT[i][j]!=0)
                    {
                        Verfcolision=1;
                    }
                }
            }
            if(Verfcolision!=1)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (piezaEXT[i][j]!=0 && matriz[fila+i][columna+j]==0)
                        {
                            matriz[fila+i][columna+j] = piezaEXT[i][j];
                        }
                    }
                }
                puntaje(&Usuario.puntos);
                elegirpieza(CantPiezas, &Piezaseleccionada);
                printMatrix(matriz);
                do
                {
                    aux++;
                }
                while(aux<=100005000);

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (piezaEXT[i][j]!=0 && matriz[fila+i][columna+j]!=0)
                        {
                            matriz[fila+i][columna+j]=0;
                        }
                    }
                }
                fila++;
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (piezaEXT[i][j]!=0)
                        {
                            matriz[fila+i][columna+j] = piezaEXT[i][j];
                        }
                    }
                }
                Usuario.puntos+=rand() % 30+10;
                Colision=1;
            }
//BAJAR FILA
        }
        int verificarcolumna=0;
        int Bajarfila=0;
        for(fila=0; fila<20; fila++)
        {
            for(columna=1; columna<11; columna++)
            {
                if (matriz[fila][columna]!=0)
                {
                    verificarcolumna++;
                }
                if (verificarcolumna==10)
                {
                    for(columna=1; columna<11; columna++)
                    {
                        matriz[fila][columna]=0;
                    }

                    elegirpieza(CantPiezas, &Piezaseleccionada);
                    printMatrix(matriz);
                    sleep(1);
                    system("cls");
                    for (Bajarfila = fila ; Bajarfila > 0; Bajarfila--)
                    {
                        for (columna = 1; columna < 11; columna++)
                        {
                            matriz[Bajarfila][columna] = matriz[Bajarfila-1][columna];
                        }
                    }
                    Usuario.puntos+=100;
                }
            }
            verificarcolumna=0;
        }
        for(int j=1; j<11; j++)
        {
            if(matriz[0][j]!=0)
            {
                partida=1;
                system("cls");
            }
        }

    }
    while(partida!=1);
    printf("GAME OVER\n");
    printf("INGRESE UN NOMBRE DE TRES DIGITOS:\n");
    for (int i = 0; i < 3; i++)
    {
        scanf(" %c", &Usuario.NOMBRE[i]);
    }
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%c", Usuario.NOMBRE[i]);
    }
    printf(" Su puntaje fue de %d\n",Usuario.puntos);
    printf("Creador: Diego A. Spinelli Gracias por participar! Espero que le haya gustado. :)");

    FILE *archivo = fopen("ranking.txt", "a"); // Abre el archivo en modo de añadir
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para guardar el puntaje.\n");
        return;
    }

    fprintf(archivo, "Nombre: %3s Puntaje: %d\n", Usuario.NOMBRE, Usuario.puntos);  // Guardar puntaje y nombre
    fclose(archivo);
    sleep(3);
}

int elegirpieza( int CantPiezas[100], int *Piezaseleccionada)
{
    int PiezaR;
    if(CantPiezas[99]==0)
    {
        for(int X=0; X<100; X++)
        {
            CantPiezas[X]= PiezaR= rand() % 7+1;//DEVOLVER RANDOM
        }
    }
    if(*Piezaseleccionada==99)
    {
        *Piezaseleccionada=0;
    }

    printf("Proxima PIEZA es...\n");
    switch(CantPiezas[*Piezaseleccionada])
    {
    case 1:
        printf("\n[]\n[]\n[][]\n");
        break;
    case 2:
        printf("\n[][]\n[][]\n");
        break;
    case 3:
        printf("\n[]\n[]\n[]\n[]\n");
        break;
    case 4:
        printf("\n  [][]\n[][]\n");
        break;
    case 5:
        printf("\n[][]\n  [][]\n");
        break;
    case 6:
        printf("\n[][][]\n  []");
        break;
    case 7:
        printf("\n    []\n    []\n  [][]");
        break;
    }
    printf("\n\n\n");
    return CantPiezas[*Piezaseleccionada];
}

void posicionpieza(int Posicion, char pieza[4][4]) //LA A EN ALGUNOS NOMBRES DE LAS MATRICES CHAR SON DE ALTERNATIVA.
{
    char L[4][4]= {0,254,0,0,
                   0,254,0,0,        //[]
                   0,254,254,0,      //[]
                   0,0,0,0,          //[][]
                  };
    char C[4][4]= {0,254,254,0,
                   0,254,254,0,
                   0,0,0,0,        //[][]
                   0,0,0,0,        //[][]
                  };
    char I[4][4]= {0,254,0,0,           //[]
                   0,254,0,0,           //[]
                   0,254,0,0,           //[]
                   0,254,0,0,           //[]
                  };

    char N[4][4]= {0,0,254,254,
                   0,254,254,0,
                   0,0,0,0,         //[][]
                   0,0,0,0        //[][]
                  };
    char NA[4][4]= {254,254,0,0,
                    0,254,254,0,
                    0,0,0,0,       //[][]
                    0,0,0,0,         //[][]
                   };
    char T[4][4]= {254,254,254,0,
                   0,254,0,0,
                   0,0,0,0,     //[][][]
                   0,0,0,0,       //[]
                  };
    char LA[4][4]= {0,0,254,0,
                    0,0,254,0,           //[]
                    0,254,254,0,        // []
                    0,0,0,0,           //[][]
                   };
    switch(Posicion)
    {
    case 1:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = L[i][j];
            }
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = C[i][j];
            }
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = I[i][j];
            }
        }
        break;
    case 4:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = N[i][j];
            }
        }
        break;
    case 5:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = NA[i][j];
            }
        }
        break;
    case 6:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = T[i][j];
            }
        }
        break;
    case 7:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pieza[i][j] = LA[i][j];
            }
        }
        break;
    }
}

void printMatrix(char matriz[21][12])
{
    for (int i = 0; i < 20; i++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t<! ");
        for (int j = 1; j < 11; j++)
        {
            if (matriz[i][j] == 0)
                printf(" . ");
            else
                printf(" %c ", matriz[i][j]);
        }
        printf(">!\n");
    }
    printf("\t\t\t\t\t\t\t\t\t\t\t\t<!===============================>!\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t///////////////////////////////////\n");
}

void RotacionPiezas(int *fila,int *columna,int *rotar,int Posicion, char Pieza[4][4], char matriz[21][12])
{
    int Verfcolision=0;
    switch(Posicion)
    {
    case 1:

        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {0,0,254,0,        //    []
                                          254,254,254,0,    //[][][]
                                          0,0,0,0,
                                          0,0,0,0,
                                         };
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
        {
            char  matrizRotacion1[4][4]= {0,254,254,0,        //  [][]
                                          0,0,254,0,          //    []
                                          0,0,254,0,          //    []
                                          0,0,0,0,
                                         };
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==3)
        {
            char  matrizRotacion1[4][4]= {254,254,254,0,        //[][][]
                                          254,0,0,0,            //[]
                                          0,0,0,0,
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==4)
            (*rotar)=0;
        break;

    case 3:
        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {0,0,0,0,
                                          254,254,254,254,        //[][][][]
                                          0,0,0,0,
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
            (*rotar)=0;
        break;
    case 4:
        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {0,254,0,0,        //[]
                                          0,254,254,0,      //[][]
                                          0,0,254,0,        //  []
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
            (*rotar)=0;
        break;
    case 5:
        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {0,0,254,0,        //  []
                                          0,254,254,0,      //[][]
                                          0,254,0,0,        //[]
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]= matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
            (*rotar)=0;
        break;
    case 6:
        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {0,254,0,0,       // []
                                          254,254,0,0,    //[][]
                                          0,254,0,0,      //  []
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
        {
            char  matrizRotacion1[4][4]= {0,254,0,0,        //   []
                                          254,254,254,0,     //[][][]
                                          0,0,0,0,
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==3)
        {
            char  matrizRotacion1[4][4]= {0,254,0,0,        //[]
                                          0,254,254,0,      //[][]
                                          0,254,0,0,        //[]
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==4)
            (*rotar)=0;
        break;
    case 7:
        if(*rotar==1)
        {
            char  matrizRotacion1[4][4]= {254,254,254,0,        //[][][]
                                          0,0,254,0,            //    []
                                          0,0,0,0,
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==2)
        {
            char  matrizRotacion1[4][4]= {0,254,254,0,        //  [][]
                                          0,254,0,0,            //[]
                                          0,254,0,0,          //  []
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==3)
        {
            char  matrizRotacion1[4][4]= {254,0,0,0,        //[]
                                          254,254,254,0,    //[][][]
                                          0,0,0,0,
                                          0,0,0,0,
                                         };

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(matriz[*fila+i][*columna+j+1]==0 && matrizRotacion1[i][j]!=0 && matriz[*fila+i][*columna+j-1]==0)
                    {
                        Verfcolision++;
                    }
                }
            }
            if(Verfcolision==4)
            {
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        Pieza[i][j]=matrizRotacion1[i][j];
                    }
                }
            }
            Verfcolision=0;
        }
        if(*rotar==4)
            (*rotar)=0;
        break;
    }


}
void puntaje(int *puntosJugador)
{
    printf("*PROCESO COMPLETADO*\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tCONTROLES:\n");
    printf("NIVEL: INFINITO\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tMOVER EN HORIZONTAL: IZQ Y DER|A Y D\n");
    printf("PUNTAJE: %d \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tROTAR PIEZA: ARRIBA|R\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTIRAR ABAJO AUTO: ABAJO|S\n", *puntosJugador);
}

void mostrarranking()
{
    FILE *archivo = fopen("ranking.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo 'ranking.txt'.\n");
        return;
    }

    struct Jugador jugadores[100];
    int numJugadores = 0;
    char linea[100];

    while (fgets(linea, sizeof(linea), archivo) && numJugadores < 100) //Lectura de la linea completa dentro del archivo.
    {
        if (sscanf(linea, "Nombre: %3c Puntaje: %d", jugadores[numJugadores].NOMBRE, &jugadores[numJugadores].puntos) == 2)
        {
            numJugadores++;
        }
    }

    fclose(archivo);
    for (int i = 0; i < numJugadores - 1; i++)  // Ordenado Bubble Sort descendente
    {
        for (int j = 0; j < numJugadores - i - 1; j++)
        {
            if (jugadores[j].puntos < jugadores[j + 1].puntos)
            {
                struct Jugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }


    printf("POSICIONAMIENTO DEL TETRIX\n");
    for (int i = 0; i < numJugadores; i++)
    {
        printf("%d: Nombre: %.3s, Puntaje: %d\n", i + 1, jugadores[i].NOMBRE, jugadores[i].puntos);
    }
}
