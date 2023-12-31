/////////////////////////////////////////////////////////////////////GRUPO 11///////////////////////////////////////////////////////////////////////////////
//MIJAEL CALLE CANQUI
//RODRIGO ABRIL MANZANARES
//FRANCESKA ANTUANETTE CAFIERO GASCO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <time.h>
#define F 20 //Flilas.
#define C 30 //Columnas.
#define M 2 //Columnas.
///////////////////////////////////////////////////////////////////PROTOTIPOS MENÚ//////////////////////////////////////////////////////////////////////////
//1.-
void altaEmp(char nom[F][C], long id[F], int *n);
//2.-
void regHoraEnt(int hEntrada[F][M], int totalHM[F][C], long id[F]);
//3.-
void regHoraSal(char nom[F][C], int hSalida[F][M], int totalHM[F][C], long id[F]);
//4.-
void calcSalMen(char nom[F][C], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n);
//5.-
void darBajaEmp(char nom[F][C], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n);

//////////////////////////////////////////////////////////////PROTOTIPOS OTRAS FUNCIONES////////////////////////////////////////////////////////////////////

int menu();
void Get_hora(int *hora,int *min);
void rellVecMat(char nom[F][C], int hEntrada[F][M], int hSalida[F][M], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n);
int compRepId(long num, long id[F]);
int compEspId(long id[F]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCIÓN PRINCIPAL
int main() {
    int op; // Guarda el número de opción del menu.
    int *numEmp=0; // Guarda el numero de empleados total registrados.
    char emp[F][C]; // Guarda los empleados registrados(maximo 20 empleados)(con longitud máxima de 30 carácteres).
    long dni[F]; // Guarda La id de los empleados registrados, es long porque necesitamos 8 cifras para representar el DNI.
    int totalHoras[F]; // Guarda el número total de horas trabajadas por los empleados.
    float salario[F]; //Guarda el salario total de los empleados.
    int horaEnt[F][M], horaSal[F][M], totalHorasMes[F][C];
    // horaEnt: guarda la hora de entrada para cada empleado.
    // horaSal: guarda la hora de salida para cada empleado.
    // totalHorasMes: guarda las horas trabajadas de todos los dias del mes para cada empleado.

    rellVecMat(emp,horaEnt,horaSal,totalHorasMes,totalHoras,salario,dni,&numEmp);
    // Llena las variables anteriores a "0".

    do{
        op=menu(); //guarda el número seleccionado de la función menú.
        switch (op) {
            case 1:
                altaEmp(emp,dni,&numEmp);
                break;
            case 2:
                regHoraEnt(horaEnt,totalHorasMes,dni);
                break;
            case 3:
                regHoraSal(emp,horaSal,totalHorasMes,dni);
                break;
            case 4:
                calcSalMen(emp,totalHorasMes,totalHoras,salario,dni,&numEmp);
                break;
            case 5:
                darBajaEmp(emp,totalHorasMes,totalHoras,salario,dni,&numEmp);
                break;
            case 6:
                printf("\nSaliendo del programa...");
                break;
            default:
                printf("\nEscribe una opcion correcta.\n");
                break;
        }
    }while(op!=6); //No finaliza hasta que el usuario seleccione la opción salir.

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1.-
// La función altaEmp registra a los empleados (como máximo 20).
// - comprueba si la base de datos está llena, luego le pide al usuario la "ID"
// - comprueba si el id puesto por el usuario esta regitrado o no.
// - Pide al usuario el nombre y los apellidos.
void altaEmp(char nom[F][C], long id[F], int *n){
    char op;
    long cod=0;
    int compId=0, posId=0;
    //Pide por pantalla nombre del empleado y dni, y los guarda en la matriz nom y vector id, guarda también el numero de empleados en el puntero *n.
    do{
        compId=compEspId(id); //comprueba si el en vector DNI hay espacio o esta lleno.
        if(compId!=-1){ // -1 significa que no hay espacio, y si hay guarda el número de la posición en compID
            printf("\nDNI: ");
            scanf(" %ld",&cod);

            posId=compRepId(cod,id); //comprueba si el DNI introducido esta registrado, -1 el DNI no esta registrado.

            if(posId!=-1){ //comprueba si esta registrado
                printf("\nEl DNI ya esta registrado.");
            }else{ //Si no esta registrado, guarda la DNI y el nombre en la posición libre

                id[compId]=cod; //Guarda el DNI en la posición libre

                //Pide por pantala el nombre y lo guarda en la matriz con fgets
                printf("\nEmpleado:");
                fflush(stdin);
                fgets(nom[compId],sizeof(nom[compId]),stdin);

                //Reemplazo "\n" que pone fgets al final por "\0" en la matriz "nom"(donde se guarda el nombre y los apellidos de los usuarios).
                for (int i = 0; i < C; i++) {
                    if(nom[compId][i]=='\n'){
                        nom[compId][i]='\0';
                    }
                }

                *n=*n+1;   //Guarda el numero de empleados que se han introducido
            }

            fflush(stdin);
            printf("\nDesea introducir mas empleados S/N?: ");
            scanf("%c",&op);

        }else{
            printf("\nNo es posible anyadir mas empleados, la base de datos esta llena.");
            op='N';
        }


    }while(op!='N' && op!='n');

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2.-
// La función regHoraEnt registra la hora de entrada de un empleado poniendo el número de código y el numero de dia
void regHoraEnt(int hEntrada[F][M], int totalHM[F][C], long id[F]){
    long numCod=0; //Guarda el codigo introducido
    int op=0,pos=0,d=0,hor=0,min=0;

    do{
        printf("\nNumero de codigo: ");
        scanf("%ld",&numCod);
        pos=compRepId(numCod,id); //comprueba si el DNI introducido esta registrado y guarda su posición, guarda -1 el DNI no esta registrado.

        if(pos!=-1){ // Comprueba si esta registrado
            printf("\nNumero de dia: ");
            scanf("%i",&d);

            if(hEntrada[pos][d]!=0){
                printf("\nEl usuario ya ha registrado la hora de entrada.");
            }else{
                Get_hora(&hor,&min); //Se ejecuta la función Get_Hora y guarda las horas en "hor" y los minutos en "min"
                hEntrada[pos][0]=hor; //guarda las horas en la matriz segun la posición del usuario
                hEntrada[pos][1]=min; //guarda los minutos en la matriz segun la posición del usuario
                totalHM[pos][d-1]=totalHM[pos][d-1]+((hor*60)+min); //Convierte las horas a minutos y los suma con los minutos y lo guarda en la matriz
                printf("\nHora de entrada registrada.");
            }
            op=1; // asigna el valr 1 a op para que termine el bucle
        }else{ //Si no esta registrado muestra el siguiente mensaje
            printf("\nEl empleado con el codigo %ld no esta registrado.",numCod);
            op=1; // asigna el valr 1 a op para que termine el bucle
        }
    }while(op!=1);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3.-
// La función regHoraSal registra la hora de salida de un empleado poniendo el número de código y el numero de dia
void regHoraSal(char nom[F][C], int hSalida[F][M], int totalHM[F][C], long id[F]){
    long numCod=0; //Guarda el codigo introducido
    int op=0,pos=0,d=0,hor=0,min=0;
    int totalH=0; //guarda las horas totalesde un dia

    do{
        printf("\nNumero de codigo: ");
        scanf("%ld",&numCod);
        pos=compRepId(numCod,id); //comprueba si el DNI introducido esta registrado y guarda su posición, guarda -1 el DNI no esta registrado.

        if(pos!=-1){
            printf("\nNumero de dia: ");
            scanf("%i",&d);
            if(totalHM[pos][d-1]!=0){
                Get_hora(&hor,&min); //Se ejecuta la función Get_Hora y guarda las horas en "hor" y los minutos en "min"
                hSalida[pos][0]=hor; //guarda las horas en la matriz segun la posición del usuario
                hSalida[pos][1]=min; //guarda los minutos en la matriz segun la posición del usuario
                totalHM[pos][d-1]=((hor*60)+min)-totalHM[pos][d-1]; //Convierte las horas a minutos y los suma, luego resta la hora de entrada

                for (int i = 0; i < C; ++i) {
                    totalH=totalH+totalHM[pos][i]; //guarda el total de horas de todos los dias en totalH
                }
                printf("\n---------------------------------------------------------------------------------------");
                printf("\n| NOMBRE/APELLIDOS\t         | DNI\t    | HORAS/DIA %i | HORAS TOTAL/MES |",d);
                printf("\n---------------------------------------------------------------------------------------");
                printf("\n| %-30s | %-8ld | %-4i \t  | %-4i \t    |", nom[pos], id[pos],(totalHM[pos][d-1])/60,totalH/60);
                printf("\n---------------------------------------------------------------------------------------");
            }else{
                printf("\nEl usuario %ld no ha Registrado la hora de entrada.",numCod);
            }
            op=1; //Para finalizar el do while
        }else{
            printf("\nEl empleado con el codigo %ld no esta registrado.",numCod);
            op=1;  //Para finalizar el do while
        }
    }while(op!=1);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4.-
void calcSalMen(char nom[F][C], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n){

    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {
            totalH[i]=totalH[i]+totalHM[i][j];  //guarda el total de horas de todos los dias en totalH de todos los empleados
        }
    }
    // calcúla las horas traajadas segun el Precio/hora
    for (int i = 0; i < F; i++) {
        totalH[i]=totalH[i]/60;
        if(totalH[i]>0 && totalH[0]<120){
            salarioT[i]=totalH[i]*8.00; // <120 a 8.00€ la hora
        }else if(totalH[i]>=120 && totalH[0]<135){
            salarioT[i]=totalH[i]*12.45; // 120 - 135 a 12.45€ la hora
        }else if(totalH[i]>135 && totalH[0]<145){
            salarioT[i]=totalH[i]*14.00; // 135 - 145 a 14.00€ la hora
        }else if(totalH[i]>=145){
            salarioT[i]=totalH[i]*15.00; // >145 a 15.00€ la hora
        }
    }

    //Impresión de tabla de los trabajadores nombre, dni, horas trabajadas y salario
    printf("\n-----------------------------------------------------------------------------------------");
    printf("\n| NUM | NOMBRE/APELLIDOS\t      | DNI\t | HORAS TRABAJADAS\t | SALARIO      |");
    printf("\n-----------------------------------------------------------------------------------------");
    for (int i = 0; i < F; i++) {
        printf("\n| %-2i | %-30s | %-8ld | %-4i\t\t\t | %-8.2f EUR |", i + 1, nom[i], id[i],totalH[i],salarioT[i]);
    }
    printf("\n---------------------- Numero total de empleados registrados: %i -------------------------",*n);

    //Reseteo del registro del horario mensual y el numero total de horas trabajadas.
    for (int i=0; i<F; i++) {
        totalH[i]=0;
        for (int j=0; j<C; j++) {
            totalHM[i][j]=0;
        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//5.-
// La función darBajaEmp dd de baja a un empleado que decida marcharse de la empresa pagandore 8€ la hora y un plus del 3% del salario mensual
void darBajaEmp(char nom[F][C], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n){
    int op=0,pos=0;
    long numCod=0;
    float finiquito=0;
    do{
        printf("\nNumero de codigo: ");
        scanf("%ld",&numCod);
        pos=compRepId(numCod,id); //Si el usuario no esta registrado pos=-1, si lo está pos="numero de la posición".

        if(pos!=-1){
            for (int i = 0; i < C; ++i) {
                totalH[pos]=totalH[pos]+totalHM[pos][i];
            }
            totalH[pos]=totalH[pos]/60; //convierte los minutos que estan guardados en totalH en horas
            salarioT[pos]=totalH[pos]*8.00; //multiplica las horas por 8 para calcular el salario
            finiquito=salarioT[pos]*0.03; //calcúla el 3% del salario mensual

            printf("\n---------------------------------------------------------------------------------------");
            printf("\n| NOMBRE/APELLIDOS\t         | DNI\t    | TOTAL HORAS | SALARIO      | PLUS\t    |");
            printf("\n---------------------------------------------------------------------------------------");
            printf("\n| %-30s | %-8ld | %-4i\t  | %-8.2f EUR | %-4.2f EUR |", nom[pos], id[pos], totalH[pos], salarioT[pos], finiquito);
            printf("\n---------------------------------------------------------------------------------------");

            //Elimina los datos del empleado del empleado
            id[pos]=0; // DNI del empleado
            totalH[pos]=0; // total de horas trabajadas del empleado
            salarioT[pos]=0.00; // salario total del empleado
            for (int i=0; i<C; i++) {
                nom[pos][i]='\0'; //Nombre del empleado
                totalHM[pos][i]=0; //total de horas trabajadas de todos los dias durante un mes
            }
            *n=*n-1; // Resta 1 al numero total de empleados porque se ha eliminado un usuario.

            op=1; //Para finalizar el do while
        }else{
            printf("\nEl empleado con el codigo %ld no esta registrado.",numCod);
            op=1; //Para finalizar el do while
        }
    }while(op!=1);

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////FUNCIONES ADICIONALES////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//función Menu: guarda la impresión por pantalla el menú en una funcion entera, luego retorna la opción seleccionada en la variable "op".
int menu(){
    int op=0;
    printf("\n_____________________________CONTROL HORARIO DE EMPLEADOS______________________________");
    printf("\n1) Dar de alta a un nuevo empleado.");
    printf("\n2) Registrar hora de entrada.");
    printf("\n3) Registrar hora de salida.");
    printf("\n4) Calcular salario mensual.");
    printf("\n5) Dar baja a un empleado.");
    printf("\n6) Salir del programa.");
    printf("\n______________________________________GAVICU_PAGA______________________________________");
    printf("\nElige una opcion: ");
    scanf(" %i",&op);
    return op;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//comprueba si si esta lleno el vector de DNI.
int compEspId(long id[F]){
    int rt=0,r=0,i=0;
    do{
        if(id[i]==0){
            rt=i;
            r=1;
        }else{
            rt=-1;
            if(i>=F){
                r=1;
            }
        }
        i++;
    }while(r!=1);
    return rt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comprueba si la Id esta repetida
int compRepId(long num, long id[F]){
    int rt=-1;
    for (int i = 0; i < F; i++) {
        if(id[i]==num){
            rt=i; // i si es la posición DNI ya esta registrado.
        }
    }
    return rt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Guarda la hora y los minutos actuales del sistema en dos punteros.
void Get_hora(int *hora,int *min){
    struct tm *h;
    time_t hor;
    hor=time(NULL);
    h= localtime(&hor);
    *hora=h->tm_hour;
    *min=h->tm_min;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Rellena el vector DNI a 0, la matriz horaEnt/horaSal a 0, y el numEmp a 0.
void rellVecMat(char nom[F][C], int hEntrada[F][M], int hSalida[F][M], int totalHM[F][C], int totalH[F], float salarioT[F], long id[F], int *n){

    for (int i=0; i<F; i++) {
        id[i]=0;
        totalH[i]=0;
        for (int j=0; j<C; j++) {
            nom[i][j]='\0';
            totalHM[i][j]=0;

        }
    }
    for (int i = 0; i < F; i++) {
        salarioT[i]=0.00;
        for (int j = 0; j < M; j++) {
            hEntrada[i][j]=0;
            hSalida[i][j]=0;
        }
    }
    *n=0;
}