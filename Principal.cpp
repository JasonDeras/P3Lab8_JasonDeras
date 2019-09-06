#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

using namespace std;

void MenuListar();
void Empleados();
void Departamentos();

//Variables de control
sqlite3 *conn;
sqlite3_stmt *res;
int error=0;
int rec_count =0;
const char *tail;
	
int main(int argc, char** argv) {
	
//YYYY-MM-DD	
	
	while(true){
		
		int op;
		
		cout<<"Menu\n\n\n\n";
		cout<<"1. Listar\n\n";
		cout<<"2. Agregar\n\n";
		cout<<"3. Eliminar\n\n";
		cout<<"4. Listado de empleados y jefe\n\n";
		cout<<"5. Actualizar salario\n\n";
		cout<<"6. Listado por de partamento\n\n\n";
		cout<<"7. Salir\n\n";
		cout<<"Ingrese una opcion: ";
		cin>>op;
		
		cout<<"\n\n\n\n";
		
		switch(op){
			
			case 1:
				MenuListar();
			break;
			
			case 7:
				exit(0);
				conn=NULL;
				res=NULL;
				tail=NULL;	
			break;
			
			default:
				cout<<"Opcion no valida\n\n\n\n";
			break;
				
		}//Fin de las opciones del menu	
		
	}//Fin del while que hace repetitivo el sistema
	
	system("pause");
	return 0;
	
}//Fin del main

void MenuListar(){
	
	int op;
	
	cout<<"1. Listar empleados\n\n";
	cout<<"2. Listar departamentos\n\n";
	cout<<"Ingrese una opcion: ";
	cin>>op;
	cout<<"\n\n\n\n";
	
	switch(op){
		
		case 1:
			Empleados();
		break;
		
		case 2:
			Departamentos();
		break;
		
		default:
			cout<<"Opcion no valida\n\n\n\n";
		break;	
	}//Fin del switch de listado
	
	
}//Fin del menu para listar

void Empleados(){
	
	error=sqlite3_open("oracle-sample.db",&conn);
	error=sqlite3_prepare_v2(conn,"select * from emp",1000,&res,&tail);
	
	while(sqlite3_step(res) == SQLITE_ROW){
		
			cout<<"Numero del empleado: "<<sqlite3_column_text(res,0)<<endl;
			cout<<"Nombre del empleado: "<<sqlite3_column_text(res,1)<<endl;
			cout<<"Trabajo de empleado: "<<sqlite3_column_text(res,3)<<endl;
			cout<<"Manager del empleado: "<<sqlite3_column_text(res,4)<<endl;
			cout<<"Fecha de contratacion: "<<sqlite3_column_text(res,5)<<endl;
			cout<<"Comimision del empleado: "<<sqlite3_column_text(res,6)<<endl;
			cout<<"Departamento del empleado: "<<sqlite3_column_text(res,7);
			cout<<"\n\n\n\n";
	}//Fin del while de impresion
	
	cout<<"\n\n\n\n";	
	sqlite3_close(conn);
	
}//Fin del metodo para listar empleados

void Departamentos(){
	
	error=sqlite3_open("oracle-sample.db",&conn);
	error=sqlite3_prepare_v2(conn,"select * from emp",1000,&res,&tail);
	
	while(sqlite3_step(res) == SQLITE_ROW){
		
			cout<<"Numero del empleado: "<<sqlite3_column_text(res,0)<<endl;
			cout<<"Nombre del empleado: "<<sqlite3_column_text(res,1)<<endl;
			cout<<"Trabajo de empleado: "<<sqlite3_column_text(res,3)<<endl;
			cout<<"Manager del empleado: "<<sqlite3_column_text(res,4)<<endl;
			cout<<"Fecha de contratacion: "<<sqlite3_column_text(res,5)<<endl;
			cout<<"Comimision del empleado: "<<sqlite3_column_text(res,6)<<endl;
			cout<<"Departamento del empleado: "<<sqlite3_column_text(res,7);
			cout<<"\n\n\n\n";
	}//Fin del while de impresion
	
	cout<<"\n\n\n\n";	
	sqlite3_close(conn);
	
}//Fin del metodo para listar de departamentos
