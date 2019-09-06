#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

using namespace std;

//Listar
void MenuListar();
void Empleados();
void Departamentos();

//Agregar
void MenuAgregar();
void AgregarEmpleado();
void AgregarDepartamento();

//Eliminar
void Eliminar();

//Litado de emplegos con su jefe{
void Jefes();

//Void actualizacion del salario
void salario();

//Listar los empleados del departamento
void emp_dept();

//Variables de control
sqlite3 *conn;
sqlite3_stmt *res;
int error=0;
int rec_count =0;
const char *tail;
	
int main(int argc, char** argv) {	
	
	while(true){
		
		int op;
		
		cout<<"Menu\n\n\n\n";
		cout<<"1. Listar\n\n";
		cout<<"2. Agregar\n\n";
		cout<<"3. Eliminar\n\n";
		cout<<"4. Listado de empleados y jefe\n\n";
		cout<<"5. Actualizar salario\n\n";
		cout<<"6. Listado por de partamento\n\n";
		cout<<"7. Salir\n\n";
		cout<<"Ingrese una opcion: ";
		cin>>op;
		
		cout<<"\n\n\n\n";
		
		switch(op){
			
			case 1:
				MenuListar();
			break;
			
			case 2:
				MenuAgregar();
			break;
			
			case 3:
				Eliminar();
			break;
			
			case 4:
				Jefes();
			break;
			
			case 5:
				salario();
			break;
			
			case 6:
			 	emp_dept();
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
		cout<<"Mgr del empleado: "<<sqlite3_column_text(res,4)<<endl;
		cout<<"Fecha de contratacion: "<<sqlite3_column_text(res,5)<<endl;
		cout<<"Comimision del empleado: "<<sqlite3_column_text(res,6)<<endl;
		cout<<"Departamento del empleado: "<<sqlite3_column_text(res,7);
		cout<<"\n\n\n\n";
			
	}//Fin del while de impresion
	
	cout<<"\n\n\n\n";
		
	sqlite3_close(conn);
	
	system("pause");
	
}//Fin del metodo para listar empleados

void Departamentos(){
	
	error=sqlite3_open("oracle-sample.db",&conn);
	error=sqlite3_prepare_v2(conn,"select * from dept",1000,&res,&tail);
	
	while(sqlite3_step(res) == SQLITE_ROW){
		
			cout<<"Numero de Departamento: "<<sqlite3_column_text(res,0)<<endl;
			cout<<"Nombre del Departamento: "<<sqlite3_column_text(res,1)<<endl;
			cout<<"Localizacion: "<<sqlite3_column_text(res,2);
			cout<<"\n\n\n\n";
	}//Fin del while de impresion
	
	cout<<"\n\n\n\n";
		
	sqlite3_close(conn);
	
	system("pause");
	
}//Fin del metodo para listar de departamentos

void MenuAgregar(){
	
	int op;
	
	cout<<"1. Agregar empleado\n\n";
	cout<<"2. Agregar departamento\n\n";
	cout<<"Ingrese una opcion: ";
	cin>>op;
	cout<<"\n\n\n\n";
	
	switch(op){
		
		case 1:
			AgregarEmpleado();
		break;
		
		case 2:
			AgregarDepartamento();
		break;
		
		default:
			cout<<"Opcion no valida\n\n\n\n";
		break;	
	}//Fin del switch de listado
	
	
}//Fin del menu para agregar

void AgregarEmpleado(){
	
	//Connection con la base
	error=sqlite3_open("oracle-sample.db",&conn);
	
	//Variables para agregar empleados
	string num_emp;
	string nom_emp;
	string trabajo;
	string manager;
	string contratacion;
	string saldo;
	string commision;
	string num_dept;
	
	//Inserta en la tabla
	string insert;
	
	cout<<"Ingrese numero de empleado: ";
	cin>>num_emp;
	
	cout<<"Ingrese nombre del empleado: ";
	cin>>nom_emp;
	
	cout<<"Ingrese trabajo: ";
	cin>>trabajo;
	
	cout<<"Ingrese mgr: ";
	cin>>manager;
	
	cout<<"Fecha de contratacion: ";
	cin>>contratacion;
	
	cout<<"Ingrese saldo: ";
	cin>>saldo;
	
	cout<<"Ingrese comision: ";
	cin>>commision;
	
	cout<<"Ingrese numero de departamento: ";
	cin>>num_dept;
	
	
	insert = "select * from dept where deptno = '"+num_dept+"'";
	sqlite3_prepare_v2(conn, insert.c_str(), insert.length()+1, &res,	&tail);
						
	if(error!=SQLITE_OK){
		cout<<"Error con el query";
		cout<<"\n\n\n\n";
		return ;
	}//If que valida si funciono el query
						
	if(sqlite3_step(res) == SQLITE_ROW){
		insert = "insert into emp values('"+num_emp+"','"+nom_emp+"','"+trabajo+"','"+manager+"','"+contratacion+"','"+saldo+"','"+commision+"','"+num_dept+"')";
		error=sqlite3_exec(conn,insert.c_str(),0,0,0);
	}//Aregarlo a la tabla
	
	sqlite3_close(conn);
	cout<<"\n\n\n\n";
	
}//Fin del metodo para listar empleados

void AgregarDepartamento(){
	
	//Connection con la base
	error=sqlite3_open("oracle-sample.db",&conn);
	
	//Variables para agregar empleados
	string num_dept;
	string nom_dept;
	string localizacion;
	
	//Inserta en la tabla
	string insert;
	
	cout<<"Ingrese numero del departamento: ";
	cin>>num_dept;
	
	cout<<"Ingrese nombre del departamento: ";
	cin>>nom_dept;
	
	cout<<"Ingrese localizacion: ";
	cin>>localizacion;
	
	insert="insert into dept values('"+num_dept+"','"+nom_dept+"','"+localizacion+"')";
	
	if(error!=SQLITE_OK){
		cout<<"Error con el query";
		cout<<"\n\n\n\n";
		return ;
	}//If que valida si funciono el query
	
	error=sqlite3_exec(conn,insert.c_str(),0,0,0);
	
	sqlite3_close(conn);
	cout<<"\n\n\n\n";
	
}//Fin del metodo para agregar de departamentos

void Eliminar(){
	
	//Connection con la base
	error=sqlite3_open("oracle-sample.db",&conn);
	
	//Variable de eliminar
	string num_emp;
	
	//Variable del query
	string deleted;
	
	cout<<"Ingrese el numero de empleado a eliminar: ";
	cin>>num_emp;
	
	deleted="delete from emp where empno= '"+num_emp+"'";
	
	if(error!=SQLITE_OK){
		cout<<"Error con el query";
		cout<<"\n\n\n\n";
		return ;
	}//If que valida si funciono el query
	
	error=sqlite3_exec(conn,deleted.c_str(),0,0,0);
	
	sqlite3_close(conn);
	
	cout<<"\n\n\n\n";
	
}//Fin del metodo para eliminar

void Jefes(){
	
	//Connection con la base
	error=sqlite3_open("oracle-sample.db",&conn);
	
	cout<<"Litar Jefe\n\n\n\n";
	
	error=sqlite3_prepare_v2(conn, "select emp.empno,emp.ename from emp",1000,&res,&tail);
	
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<sqlite3_column_text(res,0)<<", "<<sqlite3_column_text(res,1)<<endl;
	}//While de impresion
	
	cout<<"\n\n\n\n";
	
	//Variable del numero a buscar
	string num_emp;
	
	cout<<"Numero del empleado a listar del empleado a listar: ";
	cin>>num_emp;
	
	string buscar="select * from emp where empno='"+num_emp+"'";
	
	error=sqlite3_prepare_v2(conn, buscar.c_str(),1000,&res,&tail);
	
	cout<<"JEFE:"<<endl<<endl;
	
	while(sqlite3_step(res) == SQLITE_ROW){
		
		cout<<"Numero del empleado: "<<sqlite3_column_text(res,0)<<endl;
		cout<<"Nombre del empleado: "<<sqlite3_column_text(res,1)<<endl;
		cout<<"Trabajo de empleado: "<<sqlite3_column_text(res,3)<<endl;
		cout<<"Mgr del empleado: "<<sqlite3_column_text(res,4)<<endl;
		cout<<"Fecha de contratacion: "<<sqlite3_column_text(res,5)<<endl;
		cout<<"Comimision del empleado: "<<sqlite3_column_text(res,6)<<endl;
		cout<<"Departamento del empleado: "<<sqlite3_column_text(res,7);
		cout<<"\n\n\n\n";
		
	}//While de impresion del jefe
	
	
	buscar="select * from emp where mgr='"+num_emp+"'";
	
	error=sqlite3_prepare_v2(conn, buscar.c_str(),1000,&res,&tail);
	
	cout<<"EMPLEADOS:"<<endl<<endl;
	
	while(sqlite3_step(res) == SQLITE_ROW){
		
		cout<<"Numero del empleado: "<<sqlite3_column_text(res,0)<<endl;
		cout<<"Nombre del empleado: "<<sqlite3_column_text(res,1)<<endl;
		cout<<"Trabajo de empleado: "<<sqlite3_column_text(res,3)<<endl;
		cout<<"Mgr del empleado: "<<sqlite3_column_text(res,4)<<endl;
		cout<<"Fecha de contratacion: "<<sqlite3_column_text(res,5)<<endl;
		cout<<"Comimision del empleado: "<<sqlite3_column_text(res,6)<<endl;
		cout<<"Departamento del empleado: "<<sqlite3_column_text(res,7);
		cout<<"\n\n\n\n";
		
	}//Impresion de los empleados
				
	if (error!= SQLITE_OK){
		cout<<"Ocurrio un error en el listado\n\n\n\n";
		return ;
	}//If que valida el query
				
	sqlite3_close(conn);
	cout<<"\n\n\n\n";
	
}//Fin del metodo para listar los jefes con sus empleados

void salario(){
}

//Listar los empleados del departamento
void emp_dept(){
}
