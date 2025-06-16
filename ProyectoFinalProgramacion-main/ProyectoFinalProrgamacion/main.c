#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include "matricula.h"

// MENU PRINCIPAL
int mostrarMenu() {
	int menu;
	system("cls");  // Limpia la pantalla
	
	printf("+---------------MENU---------------+");
	printf("\n| 1. Registro de un vehiculo       |");
	printf("\n| 2. Buscar vehiculo por placa     |");
	printf("\n| 3. Listar vehiculos matriculados |");
	printf("\n| 4. Salir                         |");
	printf("\n+----------------------------------+");
	printf("\nIngrese su opcion: ");
	scanf("%d", &menu);
	
	return menu;
}

int numLista = 0;  // Contador global de vehículos registrados
float valorMatricula;
//Funcion para transformar la placa a mayusculas
void convertirAMayusculas(char *cadena) {
	while (*cadena) {
		*cadena = toupper((unsigned char)*cadena);
		cadena++;
	}
}

// Estructura que almacena los datos de un vehículo
struct Vehiculo {
	char placa[9], tipo[50];    // Placa (máx 8 + '\0') y tipo del vehículo
	int cedula, anio, revisiones;
	int edadPropietario;
	float avaluo;
};

// Arreglo para almacenar hasta 100 vehículos
struct Vehiculo listaVehiculos[100];


// Crea y almacena un vehículo
struct Vehiculo crearVehiculo(char placa[8], int cedula, int anio, char tipo[50], float avaluo, int revisiones, int edad) {
	struct Vehiculo v;
	
	strcpy(v.placa, placa);
	v.cedula = cedula;
	v.edadPropietario = edad;
	v.anio = anio;
	strcpy(v.tipo, tipo);
	v.avaluo = avaluo;
	v.revisiones = revisiones;
	
	listaVehiculos[numLista] = v;
	
	return v;
}

// registro de vehiculos
void registrarVehiculo() {
	char placa[9], tipo[50], verificarCedula[10], verificarAnio[5],verificarEdad[3], verificarAvaluo[15], verificarRevisiones[2];
	int cedula, anio, revisiones, edad, placaNueva;
	float avaluo;
	
	// Validar placa
	do {
		placaNueva=1;
		printf("Ingrese la placa del vehiculo: ");
		scanf("%s", placa);
		convertirAMayusculas(placa);
		if (strlen(placa) > 8 || strlen(placa) < 7) {
			printf("Error: Ingrese la placa en el formato correcto\n");
		}
		if (strchr(placa, '-') == NULL) {
			printf("Error: Ingrese la placa con el guion (-).\n");
		}
		
			for (int i = 0; i<=numLista; i++){
				if ( strcmp(listaVehiculos[i].placa, placa)==0){
					placaNueva=0;
					printf("ERROR: El vehiculo de placa %s ya está matriculado. \n", placa);
				}
			}
			
		
	} while (strlen(placa) > 8 || strlen(placa) < 7 || strchr(placa, '-') == NULL || placaNueva==0);
	
	
	
	// Validar cédula
	do {
		printf("Ingrese el numero de cedula del propietario: ");
		scanf("%s", verificarCedula);
		
		if (strspn(verificarCedula, "0123456789") != strlen(verificarCedula)) {
			printf("Error: solo se permiten numeros.\n");
		}
		if (strlen(verificarCedula) != 10) {
			printf("Error: ingrese un numero de cedula valido.\n");
		}
		
	} while (strspn(verificarCedula, "0123456789") != strlen(verificarCedula) || strlen(verificarCedula) != 10);
	
	cedula = atoi(verificarCedula);
	
	// Validar edad
	do {
		printf("Ingrese la edad del propietario: ");
		scanf("%s", verificarEdad);
		
		if (strspn(verificarEdad, "0123456789") != strlen(verificarEdad)) {
			printf("Error: solo se permiten numeros.\n");
		}
		if (atoi(verificarEdad) < 18 || atoi(verificarEdad) > 100) {
			printf("Error: ingrese una edad válida.\n");
		}
		
	} while (strspn(verificarEdad, "0123456789") != strlen(verificarEdad) || atoi(verificarEdad) < 18 || atoi(verificarEdad) > 100);
	
	edad = atoi(verificarEdad);
	
	// Validar año
	do {
		printf("Ingrese el anio del vehiculo: ");
		scanf("%s", verificarAnio);
		
		if (strspn(verificarAnio, "0123456789") != strlen(verificarAnio) || strlen(verificarAnio) > 4) {
			printf("Error: Ingrese el anio en el formato correcto.\n");
		}
		
	} while (strspn(verificarAnio, "0123456789") != strlen(verificarAnio) || strlen(verificarAnio) > 4 );
	
	anio = atof(verificarAnio); 
	
	while (anio < 1950 || anio > 2025) {
		printf("Error: Ingrese el año entre 1950 y 2025.\n");
		printf("Ingrese el anio del vehiculo: ");
		scanf("%s", verificarAnio);
		
		if (strspn(verificarAnio, "0123456789") != strlen(verificarAnio) || strlen(verificarAnio) > 4) {
			printf("Error: Ingrese el anio en el formato correcto.\n");
		}
		anio = atof(verificarAnio); 
	}
	
	// Ingresar tipo
	printf("Por favor ingrese el tipo de vehiculo: ");
	scanf(" %[^\n]s", tipo);  // Lee con espacios
	
	// Validar avalúo
	do {
		printf("Ingrese el avaluo del vehiculo: ");
		scanf("%s", verificarAvaluo);
		
		if (strspn(verificarAvaluo, "0123456789.") != strlen(verificarAvaluo)) {
			printf("Error: Solo se aceptan numeros.\n");
		}
		
	} while (strspn(verificarAvaluo, "0123456789.") != strlen(verificarAvaluo));
	
	avaluo = atof(verificarAvaluo);
	
	// Validar revisiones
	do {
		printf("Ingrese el numero de revisiones que ha tenido en el anio: ");
		scanf("%s", verificarRevisiones);
		
		if (strspn(verificarRevisiones, "0123456789") != strlen(verificarRevisiones)) {
			printf("Error: solo se permiten numeros.\n");
		}
		
	} while (strspn(verificarRevisiones, "0123456789") != strlen(verificarRevisiones));
	
	revisiones = atoi(verificarRevisiones);
	
	// Crear vehículo
	crearVehiculo(placa, cedula, anio, tipo, avaluo, revisiones, edad);
	
	// Crear vehículo y agregarlo a la lista
	// Crear vehículo y agregarlo a la lista
	struct Vehiculo nuevo = crearVehiculo(placa, cedula, anio, tipo, avaluo, revisiones, edad);

	valorMatricula = calcularMatricula(placa, avaluo, anio, edad, revisiones);
	
	if (valorMatricula==0){
		return;
	}else{
		
	
	char confirmarPago[4];
	printf("Valor a pagar por matricula: %.2f\n", valorMatricula);
	printf("¿Desea confirmar el pago? (si/no): ");
	scanf("%s", confirmarPago);
	
	// Convertir a minúsculas
	for (int i = 0; confirmarPago[i]; i++) {
		confirmarPago[i] = tolower(confirmarPago[i]);
	}
	
	if (strcmp(confirmarPago, "si") != 0) {
		printf("Registro cancelado. No se genero comprobante.\n");
		return;
	}
	

	

	// Si confirma, guardar en archivo
	FILE *archivo = fopen("comprobante.txt", "a");
	if (archivo != NULL) {
		fprintf(archivo, "---------- COMPROBANTE DE REGISTRO ----------\n");
		fprintf(archivo, "Placa: %s\n", nuevo.placa);
		fprintf(archivo, "Cedula: %d\n", nuevo.cedula);
		fprintf(archivo, "Edad del propietario: %d\n", nuevo.edadPropietario);
		fprintf(archivo, "Anio: %d\n", nuevo.anio);
		fprintf(archivo, "Tipo: %s\n", nuevo.tipo);
		fprintf(archivo, "Avaluo: %.2f\n", nuevo.avaluo);
		fprintf(archivo, "Revisiones: %d\n", nuevo.revisiones);
		fprintf(archivo, "Valor a pagar matricula: %.2f\n", valorMatricula);
		fprintf(archivo, "---------------------------------------------\n\n");
		fclose(archivo);
		printf("Pago confirmado. Comprobante generado exitosamente.\n");
	} else {
		printf("Error al generar el comprobante.\n");
	}
	}
}

// Ingreso multiple de vehiculos
void procesarIngreso() {
	char continuar[4];
	do {
		system("cls");
		registrarVehiculo();
		numLista++;
		printf("\n¿Desea ingresar otro vehiculo adicional? (si/no): ");
		scanf("%s", continuar);
	} while (strcmp(continuar, "si") == 0);
}

// Funcion para listar vehiculos
void listarVehiculos() {
	system("cls");
	
	FILE *archivo = fopen("comprobante.txt", "r");
	if (archivo == NULL) {
		printf("No hay vehiculos registrados en el archivo.\n");
		return;
	}
	
	printf("\n-------- LISTADO DE VEHICULOS --------\n\n");
	
	char linea[200];
	while (fgets(linea, sizeof(linea), archivo)) {
		printf("%s", linea);
	}
	
	fclose(archivo);
}



// Funcion principal
int main() {
	int menu;
	char regresarMenu[4];
	
	do {
		menu = mostrarMenu();
		
		// Selección de opciones
		switch (menu) {
		case 1:
			procesarIngreso();
			break;
		case 2:
			break;
		case 3:
			listarVehiculos();
			break;
		case 4:
			printf("\nSaliendo...\n");
			break;
		default:
			printf("\nFunción invalida.\n");
		}
		
		// Pregunta si desea regresar al menu, excepto si elige salir
		if (menu != 4) {
			printf("\n¿Desea regresar al menu? (si/no): ");
			scanf("%s", regresarMenu);
			
			// Convertimos la respuesta a minúsculas
			for (int i = 0; regresarMenu[i]; i++) {
				regresarMenu[i] = tolower(regresarMenu[i]);
			}
		}
		
		// Y la condición queda igual:
	} while (menu != 4 && strcmp(regresarMenu, "si") == 0);
	
	return 0;
}
