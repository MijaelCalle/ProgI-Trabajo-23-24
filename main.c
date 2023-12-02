//GRUPO 11
//MIJAEL CALLE CANQUI
//RODRIGO ABRIL MANZANARES
//FRANCESKA ANTUANETTE CAFIERO GASCO

#include <stdio.h>
#include <time.h>
#define F 20
#define C 30
#define M 2
//1.-
void altaEmp(char nom[F][C], long id[F], int *n);
//2.-
void regHoraEnt(int hEntrada[F][M], int totalHM[F][C], long id[F], int dia[F], int *n);
//3.-
void regHoraSal(int hSalida[F][M], int totalHM[F][C], long id[F], int dia[F], int *n);
//4.-
void calcSalMen(char nom[F][C], int totalHM[F][C], int totalH[F], long id[F], int *n);
//5.-
void darBajaEmp(char nom[F][C], int totalHM[F][C], int totalH[F], long id[F], int *n);

//Otras funciones.
void Get_hora(int *hora,int *min);
void rellVecMat(char nom[F][C], int hEntrada[F][M], int hSalida[F][M], int totalHM[F][C], int totalH[F], long id[F], int *n);
int compRepId(long num, long id[F]);
int compEspId(long id[F]);


//FUNCIÓN PRINCIPAL
int main() {
    int op;
    int *numEmp=0;
    int hora, minuto;
    char emp[F][C];
    long dni[F], fecha[F];
    int totalHoras[F];
    int horaEnt[F][M], horaSal[F][M], totalHorasMes[F][C];
    rellVecMat(emp,horaEnt,horaSal,totalHorasMes,totalHoras,dni,&numEmp);

    //Menú
    do{
        printf("\n_____________________________CONTROL HORARIO DE EMPLEADOS______________________________");
        printf("\n1) Dar de alta a un nuevo empleado.");
        printf("\n2) Registrar hora de entrada.");
        printf("\n3) Registrar hora de salida.");
        printf("\n4) Calcular salario mensual.");
        printf("\n5) Dar baja a un empleado.");
        printf("\n6) Salir del programa.");
        printf("\n_______________________________________________________________________________________");
        printf("\nElige una opcion: ");
        scanf("%i",&op);
        switch (op) {
            case 1:
                altaEmp(emp,dni,&numEmp);
                break;
            case 2:
                regHoraEnt(horaEnt,totalHorasMes,dni,fecha,&numEmp);
                break;
            case 3:
                regHoraSal(horaSal,totalHorasMes,dni,fecha,&numEmp);
                break;
            case 4:
                calcSalMen(emp,totalHorasMes,totalHoras,dni,&numEmp);
                break;
            case 5:
                darBajaEmp(emp,totalHorasMes,totalHoras,dni,&numEmp);
                break;
            case 6:
                printf("\nSaliendo del programa...");
                break;
            default:
                printf("\nEscribe una opcion correcta.\n");
                break;
        }
    }while(op!=6);

    return 0;
}

//1.-
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

                //Reemplazo \n que pone fgets al final por \0
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

//2.-
void regHoraEnt(int hEntrada[F][M], int totalHM[F][C], long id[F], int dia[F], int *n){
    long numCod=0;
    int op=0,pos=0,d=0,hor=8,min=15;

    do{
        printf("\nNumero de codigo: ");
        scanf("%ld",&numCod);
        pos=compRepId(numCod,id);

        if(pos!=-1){

            printf("\nNumero de dia: ");
            scanf("%i",&d);

            //Get_hora(&hor,&min);
            hEntrada[pos][0]=hor;
            hEntrada[pos][1]=min;
            totalHM[pos][d-1]=totalHM[pos][d-1]+((hor*60)+min);

            op=1; //Para finalizar el do while
        }else{
            printf("\nEl empleado con el codigo %ld no esta registrado.",numCod);
            op=1;
        }
    }while(op!=1);
}

//3.-
void regHoraSal(int hSalida[F][M], int totalHM[F][C], long id[F], int dia[F], int *n){
    long numCod=0;
    int op=0,pos=0,d=0,hor=14,min=35;

    do{
        printf("\nNumero de codigo: ");
        scanf("%ld",&numCod);
        pos=compRepId(numCod,id);

        if(pos!=-1){

            printf("\nNumero de dia: ");
            scanf("%i",&d);

            //Get_hora(&hor,&min);
            hSalida[pos][0]=hor;
            hSalida[pos][1]=min;
            totalHM[pos][d-1]=((hor*60)+min)-totalHM[pos][d-1];

            op=1; //Para finalizar el do while
        }else{
            printf("\nEl empleado con el codigo %ld no esta registrado.",numCod);
            op=1;
        }
    }while(op!=1);
    /*
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            printf("%i ",totalHM[i][j]);
        }
        printf("\n");
    }
    */

}

//4.-
void calcSalMen(char nom[F][C], int totalHM[F][C], int totalH[F], long id[F], int *n){

    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {
            totalH[i]=totalH[i]+totalHM[i][j];
        }
    }

    printf("\n---------------------------------------------------------------------------------------");
    printf("\n| NUM | NOMBRE/APELLIDOS\t      | DNI\t | HORAS TRABAJADAS\t | SALARIO    |");
    printf("\n---------------------------------------------------------------------------------------");
    for (int i = 0; i < F; i++) {
        // Ajusta el formato según la longitud máxima de los datos
        printf("\n| %-2i | %-30s | %-8ld | %-4i\t\t\t | %-4i euros |", i + 1, nom[i], id[i],(totalH[i]/60),(totalH[i]/60)*8);
    }
    printf("\n---------------------- Numero total de empleados registrados: %i -----------------------",*n);


}

//5.-
void darBajaEmp(char nom[F][C], int totalHM[F][C], int totalH[F], long id[F], int *n){
    int i=0;
    printf("\n---------------------------------------------------------------------------------------");
    printf("\n| NUM | NOMBRE/APELLIDOS\t      | DNI\t | HORAS TRABAJADAS\t | SALARIO    |");
    printf("\n---------------------------------------------------------------------------------------");
    printf("\n| %-2i | %-30s | %-8ld | %-4i\t\t\t | %-4i euros |", i + 1, nom[i], id[i],(totalH[i]/60),(totalH[i]/60)*8);
    printf("\n---------------------- Numero total de empleados registrados: %i -----------------------",*n);
}

////////////////////////////////////////////////FUNCIONES ADICIONALES////////////////////////////////////////////////

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

//Hora
void Get_hora(int *hora,int *min){
    struct tm *h;
    time_t hor;
    hor=time(NULL);
    h= localtime(&hor);
    *hora=h->tm_hour;
    *min=h->tm_min;
}

//Rellena el vector DNI a 0, la matriz horaEnt/horaSal a 0, y el numEmp a 0.
void rellVecMat(char nom[F][C], int hEntrada[F][M], int hSalida[F][M], int totalHM[F][C], int totalH[F], long id[F], int *n){

    for (int i=0; i<F; i++) {
        id[i]=0;

        for (int j=0; j<C; j++) {
            nom[i][j]='\0';
            totalHM[i][j]=0;
        }
    }
    for (int i = 0; i < F; i++) {
        totalH[i]=0;
        for (int j = 0; j < M; j++) {
            hEntrada[i][j]=0;
            hSalida[i][j]=0;
        }
    }
    *n=0;
}